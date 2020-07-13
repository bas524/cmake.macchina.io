#ifndef EventsRegistry_Types_INCLUDED
#define EventsRegistry_Types_INCLUDED

#include <Poco/Poco.h>

namespace events_registry
{

//@ serialize
using EventId = Poco::Int64;

/// @brief Authorized role identifier
//@ serialize
using RoleId = Poco::Int64;

//@ serialize
struct Event
{
    EventId id;
    std::string name;
    std::string product;  /// @remark name + product is unique
    /// @todo possibly add product version
    std::string description;
    std::string category;
};

}  // namespace events_registry

#endif  // EventsRegistry_Types_INCLUDED
