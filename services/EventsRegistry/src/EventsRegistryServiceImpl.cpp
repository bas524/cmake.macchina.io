#include "EventsRegistryServiceImpl.h"
#include "EventTypeHandler.h"

using namespace Poco::Data::Keywords;

namespace events_registry
{

EventsRegistryServiceImpl::EventsRegistryServiceImpl(Poco::OSP::BundleContext::Ptr context)
    : m_context(context)
    /// @todo replace with postgresql
    , m_session(new Poco::Data::Session("SQLite", "smc.db"))
{
    /// @todo remove (on replace with postgresql)
    *m_session << "CREATE TABLE IF NOT EXISTS Event (id INTEGER PRIMARY KEY, roleId INTEGER, name TEXT, product TEXT, description TEXT, category TEXT)", now;
}

EventId EventsRegistryServiceImpl::Insert(RoleId roleId, const Event &event)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    *m_session << "INSERT INTO Event(roleId, name, product, description, category) VALUES(?, ?, ?, ?, ?)", use(roleId),
        useRef(event.name), useRef(event.product), useRef(event.description), useRef(event.category), now;
    EventId result{};
    /// @todo rework (on replace with postgresql)
    *m_session << "SELECT last_insert_rowid()", into(result), now;
    return result;
}

Event EventsRegistryServiceImpl::Select(RoleId roleId, EventId id)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    std::vector<Event> events;
    *m_session << "SELECT name, product, description, category  FROM Event WHERE roleId = ? AND id = ?", into(events),
        use(roleId), use(id), now;

    if (events.size() == 0)
    {
        throw Poco::NotFoundException();
    }

    if (events.size() > 1)
    {
        throw Poco::DataException();
    }

    return events[0];
}

std::vector<Event> EventsRegistryServiceImpl::Search(
    RoleId roleId, const std::string &nameLike, const std::string &productLike, const std::string &categoryLike)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    std::vector<Event> events;
    *m_session
        << "SELECT name, product, description, category FROM Event WHERE roleId = ? AND name LIKE ? AND product LIKE ? AND category LIKE ?",
        into(events), use(roleId), useRef(nameLike), useRef(productLike), useRef(categoryLike), now;

    return events;
}

std::vector<EventId> EventsRegistryServiceImpl::SearchIds(
    RoleId roleId, const std::string &nameLike, const std::string &productLike, const std::string &categoryLike)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    std::vector<EventId> eventIds;
    *m_session << "SELECT id FROM Event WHERE roleId = ? AND name LIKE ? AND product LIKE ? AND category LIKE ?",
        into(eventIds), use(roleId), useRef(nameLike), useRef(productLike), useRef(categoryLike), now;

    return eventIds;
}

void EventsRegistryServiceImpl::Update(RoleId roleId, EventId id, const Event &event)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    *m_session << "UPDATE Event Set name = ?, product = ?, description = ?, category = ? WHERE roleId = ? AND id = ?",
        useRef(event.name), useRef(event.product), useRef(event.description), useRef(event.category), use(roleId),
        use(id), now;
}

void EventsRegistryServiceImpl::Delete(RoleId roleId, EventId id)
{
    Poco::FastMutex::ScopedLock lock(m_mutex);
    *m_session << "DELETE FROM Event WHERE roleId = ? AND id = ?", use(roleId), use(id), now;
}

}  // namespace events_registry