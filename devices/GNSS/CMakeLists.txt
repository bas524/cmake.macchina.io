set(PROJECT_BUNDLE io.macchina.gnss.nmea)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_BINARY_DIR}/GNSS.bndlspec)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io GNSS Sensor (NMEA-0183)"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::GNSS::BundleActivator
        #LAZY_START
        CODES IoTGNSSNMEA:HAS_VERSION
        RUN_LEVEL 610
        DEPENDENCIES io.macchina.devices:1.0.0-2.0.0 io.macchina.serial:1.0.0-2.0.0
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/GNSSSensorImpl.cpp
                   src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTGNSSNMEA
                   Poco::OSPIoTDevices
                   Poco::Serial
                   Poco::Geo
                   Poco::OSP
                   Poco::Util
                   Poco::XML
                   Poco::JSON
                   Poco::Foundation
                 )

add_subdirectory(NMEA)