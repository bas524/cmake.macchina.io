#ifndef EventsRegistry_EventsRegistryEndpointImpl_INCLUDED
#define EventsRegistry_EventsRegistryEndpointImpl_INCLUDED

#include <EventsRegistry/EventsRegistryEndpoint.h>
#include <EventsRegistry/IEventsRegistryService.h>

#include <Poco/OSP/BundleContext.h>
#include <Poco/SharedPtr.h>

namespace events_registry
{

class EventsRegistry_API EventsRegistryEndpointImpl : public EventsRegistryEndpoint
{
public:
    explicit EventsRegistryEndpointImpl(Poco::OSP::BundleContext::Ptr context);

    Event put(EventId id, const Event& event) override;

    Event patch(EventId id, const Event& event) override;

    Event get(EventId id) override;

    void delete_(EventId id) override;
private:
    Poco::OSP::BundleContext::Ptr m_context;
    Poco::AutoPtr<IEventsRegistryService> m_eventsRegistryService;
};

}  // namespace events_registry

#endif  // EventsRegistry_EventsRegistryEndpointImpl_INCLUDED
