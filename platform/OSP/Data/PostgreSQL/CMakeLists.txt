POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "POCO Data PostgreSQL Connector"
        NAME poco.data.postgresql
        VERSION 1.10.1
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR PostgreSQLBundleActivator
        #LAZY_START
        DEPENDENCIES poco.data:1.10.1-
        RUN_LEVEL 000
        CODES PocoDataPostgreSQL
        OUT_BUNDLESPEC ${CMAKE_CURRENT_BINARY_DIR}/PostgreSQL.bndlspec
)

POCO_MAKE_BUNDLE(NAME poco.data.postgresql
        BUNDLESPEC ${CMAKE_CURRENT_BINARY_DIR}/PostgreSQL.bndlspec
        BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
        SOURCES src/PostgreSQLBundleActivator.cpp
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        DEPENDENCIES Poco::OSP Poco::DataPostgreSQL Poco::Data Poco::Util Poco::XML Poco::Foundation)