#ifndef RemotingNG_REST_HTTPRequestHandlerFactory_INCLUDED
#define RemotingNG_REST_HTTPRequestHandlerFactory_INCLUDED

#include "REST.h"

#include <Poco/Net/Net.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>

namespace Poco
{
namespace RemotingNG
{
namespace REST
{

class Listener;

/// @brief A factory for HTTPRequestHandler objects
class RemotingNGREST_API HTTPRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    using Ptr = Poco::SharedPtr<HTTPRequestHandlerFactory>;

    /// @brief Creates the HTTPRequestHandlerFactory.
    HTTPRequestHandlerFactory(Listener& listener);

    /// @brief Creates a new request handler for the given HTTP request.
    /// @remark The method should inspect the given HTTPServerRequest object (e.g., method
    /// and URI) and create an appropriate HTTPRequestHandler object to handle the
    /// request.
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;

private:
    Listener& m_listener;
};


} // namespace REST
} // namespace RemotingNG
} // namespace Poco

#endif  // RemotingNG_REST_HTTPRequestHandlerFactory_INCLUDED
