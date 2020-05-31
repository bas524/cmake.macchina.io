set(PROJECT_BUNDLE io.macchina.can.core)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/CAN.bndlspec)

# Sources
set(SRCS
    src/CANFrame.cpp
    src/CANFDFrame.cpp
    src/CANEndpoint.cpp
    )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME IoTCAN
        GENERATE_REMOTING ${CMAKE_CURRENT_LIST_DIR}/RemoteGen.xml
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES Poco::RemotingNG Poco::OSP Poco::Zip Poco::Util Poco::JSON Poco::XML Poco::Foundation
        OUTPUT_NAME IoTCAN

        WRAP_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/IoT/CAN/CANEndpoint.h
        ${CMAKE_CURRENT_LIST_DIR}/include/IoT/CAN/CANFrame.h
        ${CMAKE_CURRENT_LIST_DIR}/include/IoT/CAN/CANFDFrame.h
        WRAP_INCLUDE_PATHS
        ${CMAKE_CURRENT_LIST_DIR}/include
        REMGEN_NAMESPACE IoT::CAN
        REMGEN_HEADERS_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/IoT/CAN
        REMGEN_SRC_PATH ${CMAKE_CURRENT_BINARY_DIR}/src
        REMGEN_COPYRIGHT "Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.\nAll rights reserved.\nSPDX-License-Identifier: Apache-2.0"
        REMGEN_SERVER_MODE
        REMGEN_ENABLE_OSP
        REMGEN_INCLUDE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/include
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io CAN Core Libraries"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        #LAZY_START
        RUN_LEVEL 000
        CODES IoTCAN:HAS_VERSION
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 DEPENDENCIES Poco::OSPIoTCAN)

add_subdirectory(SocketCAN)