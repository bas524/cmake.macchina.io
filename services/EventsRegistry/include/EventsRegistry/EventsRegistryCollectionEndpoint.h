#ifndef EventsRegistry_EventsRegistryCollectionEndpoint_INCLUDED
#define EventsRegistry_EventsRegistryCollectionEndpoint_INCLUDED

#include "EventsRegistry.h"
#include "Types.h"

#include <string>
#include <vector>

namespace events_registry
{

//@ remote
//@ path="/api/1.0/events_registry"
class EventsRegistry_API EventsRegistryCollectionEndpoint
{
public:
    virtual ~EventsRegistryCollectionEndpoint() = default;

    ///@ breif Create new registry event
    virtual Event post(const Event& event) = 0;

    ///@ breif get registry events with filter
    //@ $nameLike={in=query, mandatory=false}
    //@ $productLike={in=query, mandatory=false}
    //@ $categoryLike={in=query, mandatory=false}
    virtual std::vector<Event> get(
        const std::string& nameLike = std::string(),
        const std::string& productLike = std::string(),
        const std::string& categoryLike = std::string()) = 0;
};
}  // namespace events_registry

#endif  // EventsRegistry_EventsRegistryCollectionEndpoint_INCLUDED
