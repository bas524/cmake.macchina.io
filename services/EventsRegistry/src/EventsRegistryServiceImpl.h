#ifndef EventsRegistry_EventsRegistryServiceImpl_INCLUDED
#define EventsRegistry_EventsRegistryServiceImpl_INCLUDED

#include <EventsRegistry/EventsRegistryService.h>

#include <Poco/OSP/BundleContext.h>
#include <Poco/Data/Session.h>
#include <Poco/Mutex.h>

namespace events_registry
{

/// @see EventsRegistryService
class EventsRegistry_API EventsRegistryServiceImpl : public EventsRegistryService
{
public:
    explicit EventsRegistryServiceImpl(Poco::OSP::BundleContext::Ptr context);
    EventId Insert(RoleId roleId, const Event& event) override;
    Event Select(RoleId roleId, EventId id) override;
    std::vector<Event> Search(
        RoleId roleId,
        const std::string& nameLike,
        const std::string& productLike,
        const std::string& categoryLike) override;
    std::vector<EventId> SearchIds(
        RoleId roleId,
        const std::string& nameLike,
        const std::string& productLike,
        const std::string& categoryLike) override;
    void Update(RoleId roleId, EventId id, const Event& event) override;
    void Delete(RoleId roleId, EventId id) override;

private:
    Poco::OSP::BundleContext::Ptr m_context;
    Poco::SharedPtr<Poco::Data::Session> m_session;
    Poco::FastMutex m_mutex;
};

}  // namespace events_registry

#endif  // EventsRegistry_EventsRegistryServiceImpl_INCLUDED
