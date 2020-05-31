set(PROJECT_BUNDLE io.macchina.btle.bluez)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/BlueZ.bndlspec)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io Bluetooth LE BlueZ Implementation"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.7.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::BtLE::BlueZ::BundleActivator
        #LAZY_START
        RUN_LEVEL 610
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/BundleActivator.cpp
                   src/BlueZGATTClient.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTBtLE
                   Poco::OSP
                   Poco::RemotingNG
                   Poco::Util
                   Poco::XML
                   Poco::Foundation
                 )

