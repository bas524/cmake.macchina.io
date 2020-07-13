#include "EventsRegistryServiceImpl.h"
#include "EventsRegistryEndpointImpl.h"
#include "EventsRegistryCollectionEndpointImpl.h"

#include <EventsRegistry/Constants.h>
#include <EventsRegistry/EventsRegistryServiceServerHelper.h>
#include <EventsRegistry/EventsRegistryEndpointServerHelper.h>
#include <EventsRegistry/EventsRegistryCollectionEndpointServerHelper.h>

#include <Poco/RemotingNG/REST/Listener.h>
#include <Poco/OSP/BundleActivator.h>
#include <Poco/OSP/ServiceRef.h>
#include <Poco/OSP/ServiceRegistry.h>
#include <Poco/ClassLibrary.h>

namespace events_registry
{

class BundleActivator : public Poco::OSP::BundleActivator
{
public:
    typedef Poco::RemotingNG::ServerHelper<events_registry::EventsRegistryService> EventsRegistryServiceServerHelper;
    typedef Poco::RemotingNG::ServerHelper<events_registry::EventsRegistryEndpoint> EventsRegistryEndpointServerHelper;
    typedef Poco::RemotingNG::ServerHelper<events_registry::EventsRegistryCollectionEndpoint>
        EventsRegistryCollectionEndpointServerHelper;

    void start(Poco::OSP::BundleContext::Ptr context)
    {
        EventsRegistryServiceServerHelper::RemoteObjectPtr eventsRegistryServiceRemoteObject =
            EventsRegistryServiceServerHelper::createRemoteObject(
                new EventsRegistryServiceImpl(context), EventsRegistryServiceId);
        m_eventsRegistryService = context->registry().registerService(
            EventsRegistryServiceId, eventsRegistryServiceRemoteObject, Poco::OSP::Properties());


        Poco::RemotingNG::REST::Listener::Ptr listener = new Poco::RemotingNG::REST::Listener("rest", 8080);
        m_listenerId = Poco::RemotingNG::ORB::instance().registerListener(listener);
        m_eventsRegistryEndpointUri = EventsRegistryEndpointServerHelper::registerObject(
            new EventsRegistryEndpointImpl(context), "endpoint", m_listenerId);
        m_eventsRegistryCollectionEndpointUri = EventsRegistryCollectionEndpointServerHelper::registerObject(
            new EventsRegistryCollectionEndpointImpl(context), "endpoint", m_listenerId);
    }

    void stop(Poco::OSP::BundleContext::Ptr context)
    {
        EventsRegistryCollectionEndpointServerHelper::unregisterObject(m_eventsRegistryCollectionEndpointUri);
        EventsRegistryCollectionEndpointServerHelper::shutdown();
        EventsRegistryEndpointServerHelper::unregisterObject(m_eventsRegistryEndpointUri);
        EventsRegistryEndpointServerHelper::shutdown();
        Poco::RemotingNG::ORB::instance().unregisterListener(m_listenerId);

        context->registry().unregisterService(m_eventsRegistryService);
        m_eventsRegistryService = 0;
        EventsRegistryServiceServerHelper::shutdown();
    }

private:
    Poco::OSP::ServiceRef::Ptr m_eventsRegistryService;
    std::string m_listenerId;
    std::string m_eventsRegistryEndpointUri;
    std::string m_eventsRegistryCollectionEndpointUri;
};

}  // namespace events_registry


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
POCO_EXPORT_CLASS(events_registry::BundleActivator)
POCO_END_MANIFEST
