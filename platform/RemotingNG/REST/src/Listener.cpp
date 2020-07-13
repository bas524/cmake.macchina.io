#include <Poco/RemotingNG/REST/Listener.h>
#include <Poco/RemotingNG/REST/ServerTransport.h>
#include <Poco/RemotingNG/REST/HTTPRequestHandlerFactory.h>

namespace Poco
{
namespace RemotingNG
{
namespace REST
{

Listener::Listener(const std::string& endPoint, Poco::UInt16 portNumber)
    : Poco::RemotingNG::Listener(endPoint)
    , m_portNumber(portNumber)
    , m_protocol("rest")
    , m_httpServer(new Poco::Net::HTTPServer(new HTTPRequestHandlerFactory(*this), m_portNumber))
{}

void Listener::start()
{
    m_httpServer->start();
}

void Listener::stop()
{
    m_httpServer->stopAll();
}

const std::string& Listener::protocol() const
{
    return m_protocol;
}

std::string Listener::createURI(
    const Poco::RemotingNG::Identifiable::TypeId& typeId, const Poco::RemotingNG::Identifiable::ObjectId& objectId)
{
    std::string uri;
    std::string endP = endPoint();
    uri = "remoting.rest://";
    uri += endP;
    uri += '/';
    uri += protocol();
    uri += '/';
    uri += typeId;
    uri += '/';
    uri += objectId;
    return uri;
}

bool Listener::handlesURI(const std::string& /*uri*/)
{
    return false;
}

void Listener::registerObject(
    Poco::RemotingNG::RemoteObject::Ptr /*pRemoteObject*/, Poco::RemotingNG::Skeleton::Ptr /*pSkeleton*/)
{}

void Listener::unregisterObject(Poco::RemotingNG::RemoteObject::Ptr /*pRemoteObject*/) {}

}  // namespace REST
}  // namespace RemotingNG
}  // namespace Poco
