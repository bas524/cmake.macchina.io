#include <Poco/OSP/BundleActivator.h>
#include <Poco/OSP/BundleContext.h>

#include <Poco/Data/PostgreSQL/Connector.h>
#include <Poco/ClassLibrary.h>

using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;

class PostgreSQLBundleActivator: public BundleActivator
{
public:
    void start(BundleContext::Ptr context) override
    {
        Poco::Data::PostgreSQL::Connector::registerConnector();
    }

    void stop(BundleContext::Ptr context) override
    {
        Poco::Data::PostgreSQL::Connector::unregisterConnector();
    }
};

POCO_BEGIN_MANIFEST(BundleActivator)
    POCO_EXPORT_CLASS(PostgreSQLBundleActivator)
POCO_END_MANIFEST
