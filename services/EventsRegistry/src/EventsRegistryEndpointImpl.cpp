#include "EventsRegistryEndpointImpl.h"

#include <EventsRegistry/Constants.h>

#include <Poco/OSP/ServiceRegistry.h>

namespace events_registry
{

EventsRegistryEndpointImpl::EventsRegistryEndpointImpl(Poco::OSP::BundleContext::Ptr context) : m_context(context)
{
    Poco::OSP::ServiceRef::ConstPtr service = context->registry().findByName(EventsRegistryServiceId);
    poco_check_ptr(service);
    m_eventsRegistryService = service->castedInstance<IEventsRegistryService>();
}

Event EventsRegistryEndpointImpl::put(EventId id, const Event& event)
{
    ///@todo roleid
    m_eventsRegistryService->Update(0, id, event);
    return event;
}

Event EventsRegistryEndpointImpl::patch(EventId id, const Event& event)
{
    ///@todo roleid
    m_eventsRegistryService->Update(0, id, event);
    return event;
}

Event EventsRegistryEndpointImpl::get(EventId id)
{
    ///@todo roleid
    return m_eventsRegistryService->Select(0, id);
}

void EventsRegistryEndpointImpl::delete_(EventId id)
{
    ///@todo roleid
    m_eventsRegistryService->Delete(0, id);
}

}  // namespace events_registry