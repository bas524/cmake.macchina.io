set(PROJECT_BUNDLE io.macchina.devices)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/Devices.bndlspec)

# Sources
set(SRCS 
    src/Device.cpp
    src/DeviceException.cpp
    src/Sensor.cpp
    src/BooleanSensor.cpp
    src/Counter.cpp
    src/RotaryEncoder.cpp
    src/Trigger.cpp
    src/SerialDevice.cpp
    src/GNSSSensor.cpp
    src/Accelerometer.cpp
    src/Gyroscope.cpp
    src/Magnetometer.cpp
    src/Camera.cpp
    src/IO.cpp
    src/LED.cpp
    src/BarcodeReader.cpp
    src/Switch.cpp
    )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME IoTDevices
        GENERATE_REMOTING ${CMAKE_CURRENT_LIST_DIR}/RemoteGen.xml
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES Poco::RemotingNG Poco::OSP Poco::Foundation
        OUTPUT_NAME IoTDevices

        WRAP_HEADERS
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/Device.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/Sensor.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/BooleanSensor.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/Counter.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/RotaryEncoder.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/Trigger.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/SerialDevice.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/GNSSSensor.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/Accelerometer.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/Gyroscope.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/Magnetometer.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/IO.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/LED.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/BarcodeReader.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/Switch.h
          ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Devices/Camera.h
        WRAP_INCLUDE_PATHS
          ${CMAKE_CURRENT_LIST_DIR}/include
        REMGEN_NAMESPACE IoT::Devices
        REMGEN_HEADERS_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/IoT/Devices
        REMGEN_SRC_PATH ${CMAKE_CURRENT_BINARY_DIR}/src
        REMGEN_COPYRIGHT "Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.\nAll rights reserved.\nSPDX-License-Identifier: Apache-2.0"
        REMGEN_SERVER_MODE
        REMGEN_ENABLE_OSP
        REMGEN_INCLUDE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/include
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io Sensor and Device Interfaces"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::Devices::BundleActivator
        #LAZY_START
        RUN_LEVEL 610
        CODES IoTDevices:HAS_VERSION
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTDevices # ATTENTION NOTE: dependency alias-name for bundle library always has prefix Poco::OSP
                   Poco::OSP
                   Poco::RemotingNG
                   Poco::Util
                   Poco::XML
                   Poco::Foundation)

