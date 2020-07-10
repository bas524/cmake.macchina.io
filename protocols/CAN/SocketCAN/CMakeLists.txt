set(PROJECT_BUNDLE io.macchina.can.socketcan)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_BINARY_DIR}/SocketCAN.bndlspec)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  if (CMAKE_SYSTEM_VERSION VERSION_GREATER_EQUAL "3.7.0")
    add_definitions(-DMACCHINA_HAVE_SOCKETCAN)
  endif()
endif ()

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io CAN SocketCAN Implementation"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.7.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::CAN::SocketCAN::BundleActivator
        DEPENDENCIES io.macchina.can.core:1.0.0-2.0.0 poco.net:1.0.0-2.0.0
        #LAZY_START
        RUN_LEVEL 610
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/CANSocket.cpp
                   src/CANEndpointImpl.cpp
                   src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTCAN
                   Poco::OSP
                   Poco::RemotingNG
                   Poco::Net
                   Poco::Util
                   Poco::XML
                   Poco::Foundation
                 DEFINITIONS IoTCAN_EXPORTS
                 )

