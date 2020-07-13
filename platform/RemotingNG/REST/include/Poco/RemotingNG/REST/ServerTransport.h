#ifndef RemotingNG_REST_ServerTransport_INCLUDED
#define RemotingNG_REST_ServerTransport_INCLUDED

#include "REST.h"
#include "HTTPResponseSerializer.h"
#include "HTTPRequestDeserializer.h"

#include <Poco/RemotingNG/ServerTransport.h>
#include <Poco/RefCountedObject.h>
#include <Poco/AutoPtr.h>
#include <Poco/SharedPtr.h>
#include <Poco/Event.h>
#include <Poco/Logger.h>

namespace Poco
{
namespace RemotingNG
{
namespace REST
{

class Listener;

/// @brief ServerTransport for RemotingNG REST transport
/// @remark server transport is instantiated on each HTTP request
class RemotingNGREST_API ServerTransport
    : public Poco::RemotingNG::ServerTransport
    , public Poco::RefCountedObject
{
public:
    using Ptr = Poco::AutoPtr<ServerTransport>;

    /// @brief Create ServerTransport
    ServerTransport(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

    /// @see  Poco::RemotingNG::ServerTransport
    bool authenticate(const std::string& method);

    /// @see  Poco::RemotingNG::ServerTransport
    bool authorize(const std::string& method, const std::string& permission);

    /// @see  Poco::RemotingNG::ServerTransport
    Deserializer& beginRequest();

    /// @see  Poco::RemotingNG::ServerTransport
    Serializer& sendReply(SerializerBase::MessageType messageType);

    /// @see  Poco::RemotingNG::ServerTransport
    void endRequest();

private:
    Poco::RemotingNG::REST::HTTPRequestDeserializer m_deserializer;
    Poco::RemotingNG::REST::HTTPResponseSerializer m_serializer;
    Poco::Logger& m_logger;
};

}  // namespace REST
}  // namespace RemotingNG
}  // namespace Poco


#endif  // RemotingNG_REST_ServerTransport_INCLUDED
