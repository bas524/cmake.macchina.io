set(PROJECT_BUNDLE com.kaspersky.services.events_registry)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_BINARY_DIR}/EventsRegistry.bndlspec)

# Sources
set(SRCS
        src/EventsRegistryServiceImpl.cpp
        )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME EventsRegistry
        GENERATE_REMOTING ${CMAKE_CURRENT_BINARY_DIR}/RemoteGen.xml
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        # todo remove unused
        DEPENDENCIES Poco::RemotingNG Poco::OSP Poco::Zip Poco::Util Poco::JSON Poco::XML Poco::Foundation Poco::DataSQLite
        OUTPUT_NAME EventsRegistry
        WRAP_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/EventsRegistry/EventsRegistryService.h
        WRAP_INCLUDE_PATHS
        ${CMAKE_CURRENT_LIST_DIR}/include
        REMGEN_NAMESPACE events_registry
        REMGEN_HEADERS_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/EventsRegistry
        REMGEN_SRC_PATH ${CMAKE_CURRENT_BINARY_DIR}/src
        REMGEN_COPYRIGHT "(c) 2020 Kaspersky"
        REMGEN_SERVER_MODE
        REMGEN_ENABLE_OSP
        REMGEN_INCLUDE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/include
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "kaspersky.com Events Registry service"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Kaspersky"
        COPYRIGHT "(c) 2020 Kaspersky"
        ACTIVATOR events_registry::BundleActivator
        #LAZY_START
        DEPENDENCIES poco.data.sqlite:1.0.0-2.0.0
        RUN_LEVEL 000
        CODES EventsRegistry:HAS_VERSION
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
        BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
        BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
        SOURCES
        src/BundleActivator.cpp
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        # todo remove unused
        DEPENDENCIES
        Poco::OSPEventsRegistry
        Poco::OSP
        Poco::Net
        Poco::Util
        Poco::JSON
        Poco::XML
        Poco::Foundation
        Poco::DataSQLite
        )