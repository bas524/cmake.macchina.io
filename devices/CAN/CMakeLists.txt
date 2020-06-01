set(PROJECT_BUNDLE io.macchina.can.devices)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/CAN.bndlspec)

# Sources
set(SRCS
    src/Sensor.cpp
    src/BooleanSensor.cpp
    src/Counter.cpp
    src/BitStream.cpp
    src/SignalDecoder.cpp
    src/BusDecoder.cpp
    src/DeviceRegistrar.cpp
    )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME IoTCANDevices
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES
          Poco::OSPIoTDevices
          Poco::OSPIoTCAN
          Poco::RemotingNG
          Poco::OSP
          Poco::Util
          Poco::XML
          Poco::Serial
          Poco::Foundation
        OUTPUT_NAME IoTCANDevices
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io CAN Devices"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        #LAZY_START
        RUN_LEVEL 000
        CODES IoTCANDevices:HAS_VERSION
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 DEPENDENCIES Poco::OSPIoTCANDevices
                 )

