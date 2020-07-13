#ifndef RemotingNG_REST_HTTPRequestHandler_INCLUDED
#define RemotingNG_REST_HTTPRequestHandler_INCLUDED

#include "REST.h"

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Logger.h>

namespace Poco
{
namespace RemotingNG
{
namespace REST
{

class Listener;

/// @brief Handler for HTTP request
class RemotingNGREST_API HTTPRequestHandler : public Poco::Net::HTTPRequestHandler

{
public:
    HTTPRequestHandler(Listener& listener);

    /// @see HTTPRequestHandler
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;

private:
    const Listener& m_listener;
    Poco::Logger& m_logger;
};


}  // namespace REST
}  // namespace RemotingNG
}  // namespace Poco


#endif  // OSP_Web_WebServerRequestHandler_INCLUDED
