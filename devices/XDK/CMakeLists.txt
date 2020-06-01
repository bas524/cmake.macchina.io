set(PROJECT_BUNDLE io.macchina.xdk)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/XDK.bndlspec)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io XDK Sensors"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::XDK::BundleActivator
        #LAZY_START
        RUN_LEVEL 620
        DEPENDENCIES io.macchina.devices:1.0.0-2.0.0 io.macchina.btle:1.0.0-2.0.0
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/XDKSensor.cpp
                   src/HighRateSensor.cpp
                   src/HighRateAccelerometer.cpp
                   src/HighRateGyroscope.cpp
                   src/HighRateMagnetometer.cpp
                   src/HighRateButton.cpp
                   src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTBtLE
                   Poco::OSPIoTDevices
                   Poco::RemotingNG
                   Poco::OSP
                   Poco::Util
                   Poco::XML
                   Poco::Foundation
                 )