#include "EventsRegistryServiceImpl.h"

#include <EventsRegistry/EventsRegistryServiceServerHelper.h>

#include <Poco/OSP/BundleActivator.h>
#include <Poco/OSP/BundleContext.h>
#include <Poco/OSP/ServiceRef.h>
#include <Poco/OSP/ServiceRegistry.h>
#include <Poco/ClassLibrary.h>

namespace events_registry
{

class BundleActivator : public Poco::OSP::BundleActivator
{
public:
    typedef Poco::RemotingNG::ServerHelper<events_registry::EventsRegistryService> ServerHelper;

    void start(Poco::OSP::BundleContext::Ptr context)
    {
        Poco::SharedPtr<EventsRegistryServiceImpl> eventsRegistryServiceImpl = new EventsRegistryServiceImpl(context);
        const std::string Id = "com.kaspersky.services.events_registry";
        ServerHelper::RemoteObjectPtr eventsRegistryServiceRemoteObject =
            ServerHelper::createRemoteObject(eventsRegistryServiceImpl, Id);
        m_service = context->registry().registerService(Id, eventsRegistryServiceRemoteObject, Poco::OSP::Properties());
    }

    void stop(Poco::OSP::BundleContext::Ptr context)
    {
        context->registry().unregisterService(m_service);
        m_service = 0;
        ServerHelper::shutdown();
    }

private:
    Poco::OSP::ServiceRef::Ptr m_service;
};

}  // namespace events_registry


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
    POCO_EXPORT_CLASS(events_registry::BundleActivator)
POCO_END_MANIFEST
