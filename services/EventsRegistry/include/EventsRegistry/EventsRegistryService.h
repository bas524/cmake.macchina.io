#ifndef EventsRegistry_EventsRegistryService_INCLUDED
#define EventsRegistry_EventsRegistryService_INCLUDED

#include "EventsRegistry.h"

#include <string>
#include <vector>

namespace events_registry
{

/*
 * @brief functions play ground test script

var eventsRegistryRef = serviceRegistry.findByName('com.kaspersky.services.events_registry');
if (eventsRegistryRef !== null)
{
    var eventsRegistry = eventsRegistryRef.instance();

    var roleId = 0;

    logger.information('all events = ' + JSON.stringify(eventsRegistry.Search(roleId, '%', '%', '%')));

    /// insert1
    var event1Id = eventsRegistry.Insert(roleId, {
        name: "event1",
        product: "product1",
        description: "description1",
        category: "category1"
    });

    logger.information('event1 id = ' + event1Id);

    /// insert2
    var event2Id = eventsRegistry.Insert(roleId, {
        name: "event2",
        product: "product2",
        description: "description2",
        category: "category2"
    });
    logger.information('event2 id = ' + event2Id);

    logger.information('all events = ' + JSON.stringify(eventsRegistry.Search(roleId, '%', '%', '%')));

    {
        /// select
        var searchIds = eventsRegistry.SearchIds(roleId, 'event%', '%', '%');
        logger.information('search ids = ' + JSON.stringify(searchIds));
        for (var id of searchIds)
        {
            var event = eventsRegistry.Select(roleId, id);
            logger.information('select event id = ' + id + ' event = ' + JSON.stringify(event));
        }
    }

    {
        /// update
        logger.information('update event id = ' + event1Id);
        var event = eventsRegistry.Select(roleId, event1Id);
        event.description = 'description_updated'
        eventsRegistry.Update(roleId, event1Id, event);
        logger.information('all events = ' + JSON.stringify(eventsRegistry.Search(roleId, '%', '%', '%')));
    }

    {
        /// delete
        logger.information('delete event id = ' + event2Id);
        eventsRegistry.Delete(roleId, event2Id);
        logger.information('all events = ' + JSON.stringify(eventsRegistry.Search(roleId, '%', '%', '%')));
    }
}
else
{
    logger.error("Failed to get events registry service");
}

 */

//@ serialize
using EventId = Poco::Int64;

/// @brief Authorized role identifier
//@ serialize
using RoleId = Poco::Int64;

//@ serialize
struct Event
{
    std::string name;
    std::string product;  /// @remark name + product is unique
    /// @todo possibly add product version
    std::string description;
    std::string category;
};

/// @brief Data layer of events registry
//@ remote
class EventsRegistry_API EventsRegistryService
{
public:
    virtual ~EventsRegistryService() = default;

    /// @brief Insert event and return inserted event id
    virtual EventId Insert(RoleId roleId, const Event& event) = 0;

    /// @brief Select event by roleId and id
    virtual Event Select(RoleId roleId, EventId id) = 0;

    /// @brief Search (like) events by event name, product or category
    /// @param roleId role identifier
    /// @param nameLike name field like operand
    /// @param productLike product field like operand
    /// @param categoryLike category field like operand
    virtual std::vector<Event> Search(
        RoleId roleId,
        const std::string& nameLike,
        const std::string& productLike,
        const std::string& categoryLike) = 0;

    /// @brief Search (like) event ids by event name, product or category
    /// @param roleId role identifier
    /// @param nameLike name field like operand
    /// @param productLike product field like operand
    /// @param categoryLike category field like operand
    virtual std::vector<EventId> SearchIds(
        RoleId roleId,
        const std::string& nameLike,
        const std::string& productLike,
        const std::string& categoryLike) = 0;

    /// @brief Update event fields
    virtual void Update(RoleId roleId, EventId id, const Event& event) = 0;

    /// @brief Delete event
    virtual void Delete(RoleId roleId, EventId id) = 0;
};

}  // namespace events_registry

#endif  // EventsRegistry_EventsRegistryService_INCLUDED
