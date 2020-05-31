//
// SandboxRequestHandler.h
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef Playground_SandboxRequestHandler_INCLUDED
#define Playground_SandboxRequestHandler_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/Mutex.h"


namespace IoT {
namespace Web {
namespace Playground {


class SandboxRequestHandler: public Poco::Net::HTTPRequestHandler
{
public:
	SandboxRequestHandler(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the SandboxRequestHandler using the given bundle context.

	// Poco::Net::HTTPRequestHandler
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

	static const std::string SANDBOX_BUNDLE;
	static const std::string SANDBOX_SCRIPT;
	static const std::string SANDBOX_PROPERTIES;

protected:
	void handleInfo(Poco::OSP::Bundle::Ptr pBundle, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
	void handleExport(Poco::OSP::Bundle::Ptr pBundle, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

	Poco::OSP::BundleContext::Ptr context() const
	{
		return _pContext;
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	
	static Poco::FastMutex _mutex;
};


class SandboxRequestHandlerFactory: public Poco::OSP::Web::WebRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};


} } } // namespace IoT::Web::Playground


#endif // Playground_SandboxRequestHandler_INCLUDED
