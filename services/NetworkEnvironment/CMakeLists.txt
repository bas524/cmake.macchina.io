set(PROJECT_BUNDLE io.macchina.services.networkenvironment)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_BINARY_DIR}/NetworkEnvironment.bndlspec)

# Sources
set(SRCS
    src/NetworkEnvironmentService.cpp
    )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME IoTNetworkEnvironment
        GENERATE_REMOTING ${CMAKE_CURRENT_BINARY_DIR}/RemoteGen.xml
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES Poco::RemotingNG Poco::Net Poco::OSP Poco::Zip Poco::Util Poco::JSON Poco::XML Poco::Foundation
        OUTPUT_NAME IoTNetworkEnvironment

        WRAP_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/IoT/NetworkEnvironment/NetworkEnvironmentService.h
        WRAP_INCLUDE_PATHS
        ${CMAKE_CURRENT_LIST_DIR}/include
        REMGEN_NAMESPACE IoT::NetworkEnvironment
        REMGEN_HEADERS_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/IoT/NetworkEnvironment
        REMGEN_SRC_PATH ${CMAKE_CURRENT_BINARY_DIR}/src
        REMGEN_COPYRIGHT "Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.\nAll rights reserved.\nSPDX-License-Identifier: Apache-2.0"
        REMGEN_SERVER_MODE
        REMGEN_ENABLE_OSP
        REMGEN_INCLUDE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/include
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io Network Environment Service"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::NetworkEnvironment::BundleActivator
        #LAZY_START
        RUN_LEVEL 000
        DEPENDENCIES poco.net:1.7.0-2.0.0
        CODES IoTNetworkEnvironment:HAS_VERSION
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/BundleActivator.cpp
                   src/NetworkEnvironmentServiceImpl.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTNetworkEnvironment
                   Poco::OSP
                   Poco::Net
                   Poco::Util
                   Poco::JSON
                   Poco::XML
                   Poco::Foundation
                 )