set(PROJECT_BUNDLE io.macchina.ciss)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_BINARY_DIR}/CISS.bndlspec)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io CISS Sensors"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::CISS::BundleActivator
        #LAZY_START
        RUN_LEVEL 620
        DEPENDENCIES io.macchina.devices:1.0.0-2.0.0 io.macchina.serial:1.0.0-2.0.0
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/Sensor.cpp
                   src/Accelerometer.cpp
                   src/Gyroscope.cpp
                   src/Magnetometer.cpp
                   src/NPIFrame.cpp
                   src/NPIPort.cpp
                   src/Node.cpp
                   src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTDevices
                   Poco::RemotingNG
                   Poco::OSP
                   Poco::Util
                   Poco::XML
                   Poco::Serial
                   Poco::Foundation
                 )