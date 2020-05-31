//
// SessionWrapper.cpp
//
// Library: JS/Data
// Package: Wrappers
// Module:  SessionWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Data/SessionWrapper.h"
#include "Poco/JS/Data/RecordSetWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/Format.h"
#include "Poco/Version.h"
#include "Poco/DateTime.h"
#include "Poco/LocalDateTime.h"


using namespace std::string_literals;
using namespace Poco::Data::Keywords;


namespace Poco {
namespace JS {
namespace Data {


SessionHolder::SessionHolder(const std::string& connector, const std::string& connectionString):
	_connector(connector),
	_connectionString(connectionString),
	_pageSize(256),
	_pSession(new Poco::Data::Session(connector, connectionString))
{
}


SessionHolder::~SessionHolder()
{
}


SessionWrapper::SessionWrapper()
{
}


SessionWrapper::~SessionWrapper()
{
}


v8::Handle<v8::FunctionTemplate> SessionWrapper::constructor(v8::Isolate* pIsolate)
{
	return v8::FunctionTemplate::New(pIsolate, construct);
}


v8::Handle<v8::ObjectTemplate> SessionWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Data.Session"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "connector"), getConnector);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "connectionString"), getConnectionString);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "isConnected"), getIsConnected);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "isTransaction"), getIsTransaction);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "pageSize"), getPageSize, setPageSize);

		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "begin"), v8::FunctionTemplate::New(pIsolate, begin));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "commit"), v8::FunctionTemplate::New(pIsolate, commit));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "rollback"), v8::FunctionTemplate::New(pIsolate, rollback));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "close"), v8::FunctionTemplate::New(pIsolate, close));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "execute"), v8::FunctionTemplate::New(pIsolate, execute));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "executeNonQuery"), v8::FunctionTemplate::New(pIsolate, executeNonQuery));

		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> dateTimeTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(dateTimeTemplate);
}


void SessionWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	std::string connector;
	std::string connectionString;

	if (args.Length() == 2)
	{
		connector = toString(args[0]);
		connectionString = toString(args[1]);
	}
	else
	{
		returnException(args, "bad arguments: connector and connection string required"s);
		return;
	}

	SessionHolder* pSessionHolder = 0;
	try
	{
		pSessionHolder = new SessionHolder(connector, connectionString);
		SessionWrapper wrapper;
		v8::Persistent<v8::Object>& sessionObject(wrapper.wrapNativePersistent(args.GetIsolate(), pSessionHolder));
		args.GetReturnValue().Set(sessionObject);
	}
	catch (Poco::Exception& exc)
	{
		delete pSessionHolder;
		returnException(args, exc);
	}
}


void SessionWrapper::getConnector(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	SessionHolder* pSessionHolder = Wrapper::unwrapNative<SessionHolder>(info);
	returnString(info, pSessionHolder->connector());
}


void SessionWrapper::getConnectionString(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	SessionHolder* pSessionHolder = Wrapper::unwrapNative<SessionHolder>(info);
	returnString(info, pSessionHolder->connectionString());
}


void SessionWrapper::getIsConnected(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	SessionHolder* pSessionHolder = Wrapper::unwrapNative<SessionHolder>(info);
	info.GetReturnValue().Set(pSessionHolder->session()->isConnected());
}


void SessionWrapper::getIsTransaction(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	SessionHolder* pSessionHolder = Wrapper::unwrapNative<SessionHolder>(info);
	info.GetReturnValue().Set(pSessionHolder->session()->isTransaction());
}


void SessionWrapper::getPageSize(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	SessionHolder* pSessionHolder = Wrapper::unwrapNative<SessionHolder>(info);
	info.GetReturnValue().Set(pSessionHolder->getPageSize());
}


void SessionWrapper::setPageSize(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	SessionHolder* pSessionHolder = Wrapper::unwrapNative<SessionHolder>(info);
	if (value->IsNumber())
	{
		pSessionHolder->setPageSize(value->Uint32Value());
	}
	else
	{
		returnException(info, "invalid pageSize argument"s);
	}
}


void SessionWrapper::begin(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	SessionHolder* pSessionHolder = Wrapper::unwrapNative<SessionHolder>(args);
	try
	{
		pSessionHolder->session()->begin();
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void SessionWrapper::commit(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	SessionHolder* pSessionHolder = Wrapper::unwrapNative<SessionHolder>(args);
	try
	{
		pSessionHolder->session()->commit();
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void SessionWrapper::rollback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	SessionHolder* pSessionHolder = Wrapper::unwrapNative<SessionHolder>(args);
	try
	{
		pSessionHolder->session()->rollback();
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void SessionWrapper::close(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	SessionHolder* pSessionHolder = Wrapper::unwrapNative<SessionHolder>(args);
	try
	{
		pSessionHolder->session()->close();
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


static void bindStatementArgs(Poco::Data::Statement& statement, const v8::FunctionCallbackInfo<v8::Value>& args)
{
	using Poco::JS::Core::Wrapper;

	for (int i = 1; i < args.Length(); i++)
	{
		if (args[i]->IsString())
		{
			statement.bind(Wrapper::toString(args[i]));
		}
		else if (args[i]->IsBoolean())
		{
			statement.bind(args[i]->BooleanValue());
		}
		else if (args[i]->IsInt32())
		{
			statement.bind(args[i]->Int32Value());
		}
		else if (args[i]->IsUint32())
		{
			statement.bind(args[i]->Uint32Value());
		}
		else if (args[i]->IsNumber())
		{
			statement.bind(args[i]->NumberValue());
		}
		else if (args[i]->IsDate())
		{
			v8::Local<v8::Date> jsDate = v8::Local<v8::Date>::Cast(args[i]);
			double millis = jsDate->ValueOf();
			Poco::Timestamp ts(static_cast<Poco::Timestamp::TimeVal>(millis*1000));
			Poco::DateTime dateTime(ts);
			statement.bind(dateTime);
		}
		else if (args[i]->IsObject() && Poco::JS::Core::Wrapper::isWrapper<Poco::DateTime>(args.GetIsolate(), args[i]))
		{
			Poco::DateTime* pDateTime = Wrapper::unwrapNativeObject<Poco::DateTime>(args[i]);
			if (pDateTime)
			{
				statement.bind(*pDateTime);
			}
			else throw Poco::InvalidArgumentException(Poco::format("Cannot convert argument %d to Poco::DateTime"s, i));
		}
		else if (args[i]->IsObject() && Poco::JS::Core::Wrapper::isWrapper<Poco::LocalDateTime>(args.GetIsolate(), args[i]))
		{
			Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNativeObject<Poco::LocalDateTime>(args[i]);
			if (pLocalDateTime)
			{
				statement.bind(pLocalDateTime->utc());
			}
			else throw Poco::InvalidArgumentException(Poco::format("Cannot convert argument %d to Poco::LocalDateTime"s, i));
		}
		else
		{
			throw Poco::InvalidArgumentException(Poco::format("Cannot convert argument %d to native type"s, i));
		}
	}
}


void SessionWrapper::execute(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	SessionHolder* pSessionHolder = Wrapper::unwrapNative<SessionHolder>(args);
	Poco::SharedPtr<Poco::Data::Session> pSession = pSessionHolder->session();
	if (args.Length() > 0)
	{
		RecordSetHolder* pRecordSetHolder = new RecordSetHolder(pSession);
		try
		{
			Poco::Data::Statement statement = (*pSession << toString(args[0]));
			bindStatementArgs(statement, args);
			if (pSessionHolder->getPageSize() > 0)
			{
				statement , limit(pSessionHolder->getPageSize());
			}
			statement.execute();
			pRecordSetHolder->assignStatement(statement);
			pRecordSetHolder->updateRecordSet();
			RecordSetWrapper wrapper;
			v8::Persistent<v8::Object>& recordSetObject(wrapper.wrapNativePersistent(args.GetIsolate(), pRecordSetHolder));
			args.GetReturnValue().Set(recordSetObject);
		}
		catch (Poco::Exception& exc)
		{
			delete pRecordSetHolder;
			returnException(args, exc);
		}
	}
}


void SessionWrapper::executeNonQuery(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	SessionHolder* pSessionHolder = Wrapper::unwrapNative<SessionHolder>(args);
	Poco::SharedPtr<Poco::Data::Session> pSession = pSessionHolder->session();
	if (args.Length() > 0)
	{
		try
		{
			Poco::Data::Statement statement = (*pSession << toString(args[0]));
			bindStatementArgs(statement, args);
			std::size_t n = statement.execute();
			args.GetReturnValue().Set(static_cast<Poco::UInt32>(n));
		}
		catch (Poco::Exception& exc)
		{
			returnException(args, exc);
		}
	}
}


} } } // namespace Poco::JS::Data
