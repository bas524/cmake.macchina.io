//
// SettingsRequestHandler.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "SettingsRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/OSP/Web/WebSessionManager.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/Auth/AuthService.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/Util/JSONConfiguration.h"
#include "Poco/Util/Application.h"
#include "Poco/StreamCopier.h"
#include "Poco/Format.h"
#include "Poco/AutoPtr.h"
#include "Utility.h"
#include <sstream>


namespace IoT {
namespace Web {
namespace Settings {


Poco::FastMutex SettingsRequestHandler::_mutex;


SettingsRequestHandler::SettingsRequestHandler(Poco::OSP::BundleContext::Ptr pContext):
	_pContext(pContext)
{
}


void SettingsRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Poco::OSP::Web::WebSession::Ptr pSession;
	{
		Poco::OSP::ServiceRef::Ptr pWebSessionManagerRef = context()->registry().findByName(Poco::OSP::Web::WebSessionManager::SERVICE_NAME);
		if (pWebSessionManagerRef)
		{
			Poco::OSP::Web::WebSessionManager::Ptr pWebSessionManager = pWebSessionManagerRef->castedInstance<Poco::OSP::Web::WebSessionManager>();
			pSession = pWebSessionManager->find(context()->thisBundle()->properties().getString("websession.id"), request);
		}
	}
	if (!Utility::isAuthenticated(pSession, request, response)) return;

	std::string username = pSession->getValue<std::string>("username");
	Poco::OSP::Auth::AuthService::Ptr pAuthService = Poco::OSP::ServiceFinder::findByName<Poco::OSP::Auth::AuthService>(context(), "osp.auth");

	if (!pAuthService->authorize(username, "settingsAdmin"))
	{
		response.setContentLength(0);
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_FORBIDDEN);
		response.send();
		return;
	}

	Poco::Path p(request.getURI(), Poco::Path::PATH_UNIX);
	p.makeFile();
	std::string resource = p.getBaseName();

	if (request.getMethod() == "HEAD")
	{
		response.setContentType("application/json");
		response.send();
	}
	else if (request.getMethod() == "GET")
	{
		handleLoad(request, response);
	}
	else if (request.getMethod() == "POST")
	{
		handleSave(request, response);
	}
	else
	{
		response.setContentType("application/json");
		response.setChunkedTransferEncoding(true);
		response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
		response.send()
			<< "{"
			<<   "\"error\":" << Utility::jsonize("Bad request")
			<< "}";
	}
}


void SettingsRequestHandler::handleLoad(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	Poco::Util::Application& app = Poco::Util::Application::instance();

	Poco::Util::JSONConfiguration json;
	std::set<std::string> excludeSet;
	excludeSet.insert("application");
	excludeSet.insert("system");
	Utility::copyProperties(app.config(), json, excludeSet);

	response.setContentType("application/json");
	response.setChunkedTransferEncoding(true);
	std::ostream& ostr = response.send();
	json.save(ostr);
}


void SettingsRequestHandler::handleSave(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	Poco::Util::Application& app = Poco::Util::Application::instance();

	try
	{
		Poco::AutoPtr<Poco::Util::JSONConfiguration> pJSON = new Poco::Util::JSONConfiguration;
		pJSON->load(request.stream());

		std::string settingsPath = app.config().getString("macchina.settings.path", "");
		Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> pSettings;

		if (!settingsPath.empty())
		{
			Poco::AutoPtr<Poco::Util::AbstractConfiguration> pConf = app.config().find("macchina.settings");
			if (pConf)
			{
				pSettings = pConf.cast<Poco::Util::PropertyFileConfiguration>();
			}

			if (!pSettings)
			{
				_pContext->logger().warning("No 'macchina.settings' in application configuration.");
				pSettings = new Poco::Util::PropertyFileConfiguration;
			}
			else
			{
				pSettings->clear();
			}

			std::set<std::string> excludeSet;
			excludeSet.insert("application");
			excludeSet.insert("system");
			Utility::copyDeltaProperties(app.config(), *pJSON, *pSettings, excludeSet);

			pSettings->save(settingsPath);

			_pContext->logger().information("Settings saved to \"%s\".", settingsPath);
		}
		else
		{
			throw Poco::ApplicationException("No \"macchina.settings.path\" property defined. Cannot save settings.");
		}
	}
	catch (Poco::Exception& exc)
	{
		_pContext->logger().log(exc);

		response.setContentType("application/json");
		response.setChunkedTransferEncoding(true);
		response.send()
			<< "{"
			<<   "\"error\":" << Utility::jsonize(exc.displayText())
			<< "}";
		return;
	}

	response.setContentType("application/json");
	response.setChunkedTransferEncoding(true);
	response.send()
		<< "{"
		<< "}";
}


Poco::Net::HTTPRequestHandler* SettingsRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	return new SettingsRequestHandler(context());
}


} } } // namespace IoT::Web::Settings
