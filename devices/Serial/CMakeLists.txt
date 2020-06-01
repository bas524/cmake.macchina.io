set(PROJECT_BUNDLE io.macchina.serial)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/Serial.bndlspec)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io Serial Port"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::Serial::BundleActivator
        #LAZY_START
        RUN_LEVEL 610
        DEPENDENCIES io.macchina.devices:1.0.0-2.0.0
        CODES PocoSerial
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/SerialDeviceImpl.cpp
                   src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTDevices
                   Poco::Serial
                   Poco::OSP
                   Poco::RemotingNG
                   Poco::Util
                   Poco::XML
                   Poco::Foundation
                 )