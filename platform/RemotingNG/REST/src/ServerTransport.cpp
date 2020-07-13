#include <Poco/RemotingNG/REST/ServerTransport.h>
#include <Poco/RemotingNG/REST/Listener.h>
#include <Poco/RemotingNG/ORB.h>
#include <Poco/RemotingNG/Context.h>


namespace Poco
{
namespace RemotingNG
{
namespace REST
{

ServerTransport::ServerTransport(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
    : m_logger(Poco::Logger::get("RemotingNG.REST.ServerTransport"))
    , m_deserializer(request)
    , m_serializer(response)
{
}

bool ServerTransport::authenticate(const std::string& /*method*/)
{
    /// @todo
    return true;
}


bool ServerTransport::authorize(const std::string& method, const std::string& permission)
{
    /// @todo
    return true;
}


Deserializer& ServerTransport::beginRequest()
{
    return m_deserializer;
}

Serializer& ServerTransport::sendReply(SerializerBase::MessageType messageType)
{
    return m_serializer;
}

void ServerTransport::endRequest()
{
}

}  // namespace REST
}  // namespace RemotingNG
}  // namespace Poco
