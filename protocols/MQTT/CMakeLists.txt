set(PROJECT_BUNDLE io.macchina.mqtt.client)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/MQTT.bndlspec)

# Sources
set(SRCS
    src/MQTTClient.cpp
    )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME IoTMQTT
        GENERATE_REMOTING ${CMAKE_CURRENT_LIST_DIR}/RemoteGen.xml
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES Poco::RemotingNG Poco::OSP Poco::Util Poco::XML Poco::JSON Poco::Foundation
        OUTPUT_NAME IoTMQTT

        WRAP_HEADERS
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/MQTT/MQTTClient.h
        WRAP_INCLUDE_PATHS
          ${CMAKE_CURRENT_LIST_DIR}/include
        REMGEN_NAMESPACE IoT::MQTT
        REMGEN_HEADERS_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/IoT/MQTT
        REMGEN_SRC_PATH ${CMAKE_CURRENT_BINARY_DIR}/src
        REMGEN_COPYRIGHT "Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.\nAll rights reserved.\nSPDX-License-Identifier: Apache-2.0"
        REMGEN_SERVER_MODE
        REMGEN_ENABLE_OSP
        REMGEN_INCLUDE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/include
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io MQTT Client"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::MQTT::BundleActivator
        #LAZY_START
        RUN_LEVEL 610
        CODES IoTMQTT:HAS_VERSION PahoMQTT:HAS_VERSION
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/MQTTClientImpl.cpp
                   src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTMQTT
                   Poco::OSP
                   Poco::RemotingNG
                   Poco::Util
                   Poco::XML
                   Poco::Foundation
                   Poco::OSPPahoMQTT
                 )

add_subdirectory(Paho)