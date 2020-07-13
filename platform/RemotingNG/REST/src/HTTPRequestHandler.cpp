#include <Poco/RemotingNG/REST/HTTPRequestHandler.h>
#include <Poco/RemotingNG/REST/ServerTransport.h>
#include <Poco/RemotingNG/REST/Listener.h>
#include <Poco/RemotingNG/Context.h>
#include <Poco/RemotingNG/ORB.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

namespace Poco
{
namespace RemotingNG
{
namespace REST
{

HTTPRequestHandler::HTTPRequestHandler(Listener& listener)
    : m_listener(listener), m_logger(Poco::Logger::get("RemotingNG.REST.HTTPRequestHandler"))
{}

void HTTPRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
    ServerTransport::Ptr serverTransport = new ServerTransport(request, response);

    Poco::RemotingNG::ScopedContext scopedContext;
    Context::Ptr context = scopedContext.context();
    context->setValue("transport", "rest");
    context->setValue("remoteAddress", request.clientAddress());
    context->setValue("localAddress", request.serverAddress());
    context->setValue("uri", request.getURI());
    context->clearCredentials();

    Poco::RemotingNG::ORB& orb = Poco::RemotingNG::ORB::instance();
    m_logger.debug("Dispatching request to service object: %s", request.getURI());

    bool serviceFound = orb.invoke(m_listener, request.getURI(), *serverTransport);
    if (!serviceFound)
    {
        m_logger.error("Unknown service object: %s", request.getURI());
        UnknownObjectException exception(request.getURI());
        serverTransport->sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT).serializeFaultMessage("fault", exception);
        serverTransport->endRequest();
    }
}

}  // namespace REST
}  // namespace RemotingNG
}  // namespace Poco
