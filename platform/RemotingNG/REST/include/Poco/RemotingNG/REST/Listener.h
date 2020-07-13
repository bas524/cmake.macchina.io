#ifndef RemotingNG_REST_Listener_INCLUDED
#define RemotingNG_REST_Listener_INCLUDED

#include "REST.h"

#include <Poco/RemotingNG/Listener.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/BasicEvent.h>
#include <Poco/SharedPtr.h>
#include <Poco/Mutex.h>
#include <Poco/AtomicCounter.h>

#include <map>

namespace Poco
{
namespace RemotingNG
{
namespace REST
{

/// @brief The RemotingNG Listener implementation for the REST transport.
class RemotingNGREST_API Listener : public Poco::RemotingNG::Listener
{
public:
    using Ptr = Poco::AutoPtr<Listener>;

    /// @brief Create a Listener
    /// @param portNumber http server listen port
    /// @remark This method will create a Poco::Net::HTTPServer on the given listen port
    explicit Listener(const std::string& endPoint, Poco::UInt16 portNumber);

    /// @see Poco::RemotingNG::Listener
    void start();

    /// @see Poco::RemotingNG::Listener
    void stop();

    /// @see Poco::RemotingNG::Listener
    const std::string& protocol() const;

    /// @see Poco::RemotingNG::Listener
    std::string createURI(
        const Poco::RemotingNG::Identifiable::TypeId& typeId, const Poco::RemotingNG::Identifiable::ObjectId& objectId);

    /// @see Poco::RemotingNG::Listener
    bool handlesURI(const std::string& uri);

    /// @see Poco::RemotingNG::Listener
    void registerObject(Poco::RemotingNG::RemoteObject::Ptr remoteObject, Poco::RemotingNG::Skeleton::Ptr skeleton);

    /// @see Poco::RemotingNG::Listener
    void unregisterObject(Poco::RemotingNG::RemoteObject::Ptr remoteObject);

private:
    Poco::UInt16 m_portNumber;
    const std::string m_protocol;
    Poco::SharedPtr<Poco::Net::HTTPServer> m_httpServer;
};


}  // namespace REST
}  // namespace RemotingNG
}  // namespace Poco


#endif  // RemotingNG_TCP_Listener_INCLUDED
