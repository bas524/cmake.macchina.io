#ifndef EventsRegistry_EventsRegistryCollectionEndpointImpl_INCLUDED
#define EventsRegistry_EventsRegistryCollectionEndpointImpl_INCLUDED

#include <EventsRegistry/EventsRegistryCollectionEndpoint.h>
#include <EventsRegistry/IEventsRegistryService.h>

#include <Poco/OSP/BundleContext.h>

namespace events_registry
{

class EventsRegistry_API EventsRegistryCollectionEndpointImpl : public EventsRegistryCollectionEndpoint
{
public:
    explicit EventsRegistryCollectionEndpointImpl(Poco::OSP::BundleContext::Ptr context);

    Event post(const Event& event) override;

    std::vector<Event> get(
        const std::string& nameLike = std::string(),
        const std::string& productLike = std::string(),
        const std::string& categoryLike = std::string()) override;

private:
    Poco::OSP::BundleContext::Ptr m_context;
    Poco::AutoPtr<IEventsRegistryService> m_eventsRegistryService;
};

}  // namespace events_registry

#endif  // EventsRegistry_EventsRegistryCollectionEndpointImpl_INCLUDED
