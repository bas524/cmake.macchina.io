set(PROJECT_BUNDLE io.macchina.xbee)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/XBee.bndlspec)

# Sources
set(SRCS
    src/XBeeFrame.cpp
    src/XBeePort.cpp
    src/XBeeNode.cpp
    )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME IoTXBee
        GENERATE_REMOTING ${CMAKE_CURRENT_LIST_DIR}/RemoteGen.xml
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES Poco::OSPIoTDevices Poco::Serial Poco::RemotingNG Poco::OSP Poco::Util Poco::XML Poco::JSON Poco::Foundation
        OUTPUT_NAME IoTXBee

        WRAP_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/IoT/XBee/XBeeNode.h
        WRAP_INCLUDE_PATHS
        ${CMAKE_CURRENT_LIST_DIR}/include
        REMGEN_NAMESPACE IoT::XBee
        REMGEN_HEADERS_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/IoT/XBee
        REMGEN_SRC_PATH ${CMAKE_CURRENT_BINARY_DIR}/src
        REMGEN_COPYRIGHT "Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.\nAll rights reserved.\nSPDX-License-Identifier: Apache-2.0"
        REMGEN_SERVER_MODE
        REMGEN_ENABLE_OSP
        REMGEN_INCLUDE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/include
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io XBee API"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::XBee::BundleActivator
        #LAZY_START
        RUN_LEVEL 610
        CODES IoTXBee:HAS_VERSION
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/BundleActivator.cpp
                   src/XBeeNodeImpl.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTXBee
                   Poco::OSPIoTDevices
                   Poco::Serial
                   Poco::OSP
                   Poco::RemotingNG
                   Poco::Util
                   Poco::XML
                   Poco::Foundation
                 )