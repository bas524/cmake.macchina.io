POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "POCO Data SQLite Connector"
        NAME poco.data.sqlite
        VERSION 1.10.1
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR SQLiteBundleActivator
        #LAZY_START
        DEPENDENCIES poco.data:1.10.1-
        RUN_LEVEL 000
        CODES PocoDataSQLite
        OUT_BUNDLESPEC ${CMAKE_CURRENT_BINARY_DIR}/SQLite.bndlspec
)

POCO_MAKE_BUNDLE(NAME poco.data.sqlite
                 BUNDLESPEC ${CMAKE_CURRENT_BINARY_DIR}/SQLite.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/SQLiteBundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES Poco::OSP Poco::DataSQLite Poco::Data Poco::Util Poco::XML Poco::Foundation)