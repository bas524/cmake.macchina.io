#ifndef EventsRegistry_EventsRegistryEndpoint_INCLUDED
#define EventsRegistry_EventsRegistryEndpoint_INCLUDED

#include "EventsRegistry.h"
#include "Types.h"

#include <string>
#include <vector>

namespace events_registry
{

/*
 * @brief events registry REST API integration test example

 curl "127.0.0.1:8080/api/1.0/events_registry?productLike=%25&categoryLike=%25&nameLike=%25"
 curl -X POST 127.0.0.1:8080/api/1.0/events_registry -d '{"id": 0, "name": "virus_detected", "product":"kes","category":"critical", "description":""}'
 curl -X POST 127.0.0.1:8080/api/1.0/events_registry -d '{"id": 0, "name": "network_attack_detected", "product":"ngfw","category":"critical", "description":""}'
 curl "127.0.0.1:8080/api/1.0/events_registry?productLike=%25&categoryLike=%25&nameLike=%25"
 curl -X PUT 127.0.0.1:8080/api/1.0/events_registry/2 -d '{"id": 0, "name": "attack_detected", "product":"ngfw","category":"critical", "description":"my decription"}'
 curl "127.0.0.1:8080/api/1.0/events_registry?productLike=%25&categoryLike=%25&nameLike=%25"
 curl -X PATCH 127.0.0.1:8080/api/1.0/events_registry/2 -d '{"id": 0, "name": "attack_detected", "product":"ngfw","category":"critical", "description":""}'
 curl "127.0.0.1:8080/api/1.0/events_registry?productLike=%25&categoryLike=%25&nameLike=%25"
 curl -X DELETE 127.0.0.1:8080/api/1.0/events_registry/2
 curl "127.0.0.1:8080/api/1.0/events_registry?productLike=%25&categoryLike=%25&nameLike=%25"

 */

//@ remote
//@ path="/api/1.0/events_registry/{id}"
class EventsRegistry_API EventsRegistryEndpoint
{
public:
    virtual ~EventsRegistryEndpoint() = default;

    /// @brief Update a event (calls patch()).
    //@ $id={in=path}
    virtual Event put(EventId id, const Event& event) = 0;

    /// @brief Update a event.
    //@ $id={in=path}
    virtual Event patch(EventId id, const Event& event) = 0;

    /// @brief Retrieve a event by id.
    //@ $id={in=path}
    virtual Event get(EventId id) = 0;

    /// @brief Delete a event.
    //@ $id={in=path}
    virtual void delete_(EventId id) = 0;
};

}  // namespace events_registry

#endif  // EventsRegistry_EventsRegistryEndpoint_INCLUDED
