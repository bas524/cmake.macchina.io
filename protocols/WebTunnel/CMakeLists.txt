set(PROJECT_BUNDLE io.macchina.protocols.webtunnel)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/WebTunnel.bndlspec)

# Sources
set(SRCS
    src/WebTunnelService.cpp
    )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME IoTWebTunnel
        GENERATE_REMOTING ${CMAKE_CURRENT_LIST_DIR}/RemoteGen.xml
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES Poco::RemotingNG Poco::OSP Poco::Util Poco::XML Poco::JSON Poco::Foundation
        OUTPUT_NAME IoTWebTunnel

        WRAP_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/IoT/WebTunnel/WebTunnelService.h
        WRAP_INCLUDE_PATHS
        ${CMAKE_CURRENT_LIST_DIR}/include
        REMGEN_NAMESPACE IoT::WebTunnel
        REMGEN_HEADERS_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/IoT/WebTunnel
        REMGEN_SRC_PATH ${CMAKE_CURRENT_BINARY_DIR}/src
        REMGEN_COPYRIGHT "Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.\nAll rights reserved.\nSPDX-License-Identifier: Apache-2.0"
        REMGEN_SERVER_MODE
        REMGEN_ENABLE_OSP
        REMGEN_INCLUDE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/include
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io WebTunnel Agent"
        NAME ${PROJECT_BUNDLE}
        VERSION 2.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::WebTunnel::BundleActivator
        #LAZY_START
        RUN_LEVEL 610
        CODES IoTWebTunnel:HAS_VERSION PocoWebTunnel
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTWebTunnel
                   Poco::WebTunnel
                   Poco::OSP
                   Poco::Net
                   Poco::Util
                   Poco::XML
                   Poco::JSON
                   Poco::Foundation
                 )