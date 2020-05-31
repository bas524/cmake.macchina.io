//
// ServiceListenerWrapper.cpp
//
// Copyright (c) 2013-2018, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/JS/ServiceListenerWrapper.h"
#include "Poco/OSP/JS/ServiceRefWrapper.h"
#include "Poco/OSP/ServiceListener.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/Delegate.h"


namespace Poco {
namespace OSP {
namespace JS {


//
// NotifyCallbackTask
//


class NotifyCallbackTask: public Poco::Util::TimerTask
{
public:
	typedef Poco::AutoPtr<NotifyCallbackTask> Ptr;

	NotifyCallbackTask(
		v8::Isolate* pIsolate,
		Poco::JS::Core::JSExecutor::Ptr pExecutor,
		v8::Persistent<v8::Function>& callback,
		Poco::OSP::ServiceRef::Ptr pServiceRef):
		_pIsolate(pIsolate),
		_pExecutor(pExecutor),
		_function(pIsolate, callback),
		_pServiceRef(pServiceRef)
	{
	}

	~NotifyCallbackTask()
	{
		_function.Reset();
	}

	void run()
	{
		poco_assert (_pIsolate == _pExecutor->isolate());

		v8::Locker locker(_pIsolate);
		v8::Isolate::Scope isoScope(_pIsolate);
		v8::HandleScope handleScope(_pIsolate);

		v8::Local<v8::Context> context(v8::Local<v8::Context>::New(_pIsolate, _pExecutor->scriptContext()));
		v8::Context::Scope contextScope(context);

		ServiceRefWrapper wrapper;
		v8::Persistent<v8::Object>& serviceRefWrapper(wrapper.wrapNativePersistent(_pIsolate, _pServiceRef));

		v8::Local<v8::Function> localFunction(v8::Local<v8::Function>::New(_pIsolate, _function));
		v8::Local<v8::Value> receiver(v8::Null(_pIsolate));
		v8::Local<v8::Value> args[] =
		{
			v8::Local<v8::Object>::New(_pIsolate, serviceRefWrapper)
		};
		_pExecutor->callInContext(localFunction, receiver, 1, args);
	}

private:
	v8::Isolate* _pIsolate;
	Poco::JS::Core::JSExecutor::Ptr _pExecutor;
	v8::Persistent<v8::Function> _function;
	Poco::OSP::ServiceRef::Ptr _pServiceRef;
};


//
// ServiceListenerHolder
//


ServiceListenerHolder::ServiceListenerHolder(
	v8::Isolate* pIsolate,
	Poco::JS::Core::JSExecutor::Ptr pExecutor,
	Poco::OSP::ServiceRegistry& registry,
	const std::string& query,
	v8::Local<v8::Function> registeredCallback,
	v8::Local<v8::Function> unregisteredCallback):
	_pIsolate(pIsolate),
	_pExecutor(pExecutor),
	_registeredCallback(pIsolate, registeredCallback),
	_unregisteredCallback(pIsolate, unregisteredCallback),
	_pListener(registry.createListener(query, Poco::delegate(this, &ServiceListenerHolder::onServiceRegistered), Poco::delegate(this, &ServiceListenerHolder::onServiceUnregistered)))
{
}


ServiceListenerHolder::~ServiceListenerHolder()
{
	_registeredCallback.Reset();
	_unregisteredCallback.Reset();
}


void ServiceListenerHolder::dispose()
{
	_pListener = 0;
}


void ServiceListenerHolder::onServiceRegistered(const Poco::OSP::ServiceRef::Ptr& pServiceRef)
{
	Poco::JS::Core::TimedJSExecutor::Ptr pTimedJSExecutor = _pExecutor.cast<Poco::JS::Core::TimedJSExecutor>();
	if (pTimedJSExecutor)
	{
		NotifyCallbackTask::Ptr pTask = new NotifyCallbackTask(_pIsolate, _pExecutor, _registeredCallback, pServiceRef);
		pTimedJSExecutor->schedule(pTask);
	}
}


void ServiceListenerHolder::onServiceUnregistered(const Poco::OSP::ServiceRef::Ptr& pServiceRef)
{
	Poco::JS::Core::TimedJSExecutor::Ptr pTimedJSExecutor = _pExecutor.cast<Poco::JS::Core::TimedJSExecutor>();
	if (pTimedJSExecutor)
	{
		NotifyCallbackTask::Ptr pTask = new NotifyCallbackTask(_pIsolate, _pExecutor, _unregisteredCallback, pServiceRef);
		pTimedJSExecutor->schedule(pTask);
	}
}


//
// ServiceListenerWrapper
//


ServiceListenerWrapper::ServiceListenerWrapper()
{
}


ServiceListenerWrapper::~ServiceListenerWrapper()
{
}


v8::Handle<v8::ObjectTemplate> ServiceListenerWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("OSP.ServiceListener"));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "dispose"), v8::FunctionTemplate::New(pIsolate, dispose));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> serviceListenerTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(serviceListenerTemplate);
}


void ServiceListenerWrapper::dispose(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	ServiceListenerHolder* pHolder = Poco::JS::Core::Wrapper::unwrapNative<ServiceListenerHolder>(args);
	pHolder->dispose();
}


} } } // namespace Poco::OSP::JS
