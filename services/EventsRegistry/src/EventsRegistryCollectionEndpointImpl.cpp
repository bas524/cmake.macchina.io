#include "EventsRegistryCollectionEndpointImpl.h"

#include <EventsRegistry/Constants.h>

#include <Poco/OSP/ServiceRegistry.h>

namespace events_registry
{

EventsRegistryCollectionEndpointImpl::EventsRegistryCollectionEndpointImpl(Poco::OSP::BundleContext::Ptr context)
    : m_context(context)
{
    Poco::OSP::ServiceRef::ConstPtr service = context->registry().findByName(EventsRegistryServiceId);
    poco_check_ptr(service);
    m_eventsRegistryService = service->castedInstance<IEventsRegistryService>();
}

Event EventsRegistryCollectionEndpointImpl::post(const Event& event)
{
    /// @todo roleId
    return m_eventsRegistryService->Insert(0, event);
}

std::vector<Event> EventsRegistryCollectionEndpointImpl::get(
    const std::string& nameLike, const std::string& productLike, const std::string& categoryLike)
{
    /// @todo roleId
    return m_eventsRegistryService->Search(0, nameLike, productLike, categoryLike);
}

}  // namespace events_registry
