#include <Poco/RemotingNG/REST/HTTPRequestHandlerFactory.h>
#include <Poco/RemotingNG/REST/HTTPRequestHandler.h>


namespace Poco
{
namespace RemotingNG
{
namespace REST
{

HTTPRequestHandlerFactory::HTTPRequestHandlerFactory(Listener& listener) : m_listener(listener) {}

Poco::Net::HTTPRequestHandler* HTTPRequestHandlerFactory::createRequestHandler(
    const Poco::Net::HTTPServerRequest& request)
{
    return new HTTPRequestHandler(m_listener);
}

}  // namespace REST
}  // namespace RemotingNG
}  // namespace Poco
