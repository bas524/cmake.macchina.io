set(PROJECT_BUNDLE io.macchina.protocols.udp)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_BINARY_DIR}/UDP.bndlspec)

# Sources
set(SRCS
    src/UDPEndpoint.cpp
    )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME IoTUDP
        GENERATE_REMOTING ${CMAKE_CURRENT_BINARY_DIR}/RemoteGen.xml
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES Poco::RemotingNG Poco::Net Poco::OSP Poco::Zip Poco::Util Poco::JSON Poco::XML Poco::Foundation
        OUTPUT_NAME IoTUDP

        WRAP_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/IoT/UDP/UDPEndpoint.h
        WRAP_INCLUDE_PATHS
        ${CMAKE_CURRENT_LIST_DIR}/include
        REMGEN_NAMESPACE IoT::UDP
        REMGEN_HEADERS_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/IoT/UDP
        REMGEN_SRC_PATH ${CMAKE_CURRENT_BINARY_DIR}/src
        REMGEN_COPYRIGHT "Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.\nAll rights reserved.\nSPDX-License-Identifier: Apache-2.0"
        REMGEN_SERVER_MODE
        REMGEN_ENABLE_OSP
        REMGEN_INCLUDE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/include
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io UDP Endpoint"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::UDP::BundleActivator
        #LAZY_START
        RUN_LEVEL 000
        DEPENDENCIES poco.net:1.7.0-2.0.0
        CODES IoTUDP:HAS_VERSION
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/UDPEndpointImpl.cpp
                   src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTUDP
                   Poco::OSP
                   Poco::Net
                   Poco::Util
                   Poco::JSON
                   Poco::XML
                   Poco::Foundation
                 DEFINITIONS IoTUDP_EXPORTS
                 )