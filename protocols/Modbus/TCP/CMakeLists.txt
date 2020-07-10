set(PROJECT_BUNDLE io.macchina.modbus.tcp)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_BINARY_DIR}/TCP.bndlspec)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io Modbus TCP"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::Modbus::TCP::BundleActivator
        DEPENDENCIES io.macchina.modbus.core:1.0.0-2.0.0 poco.net:1.0.0-2.0.0
        #LAZY_START
        RUN_LEVEL 610
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/TCPPort.cpp
                   src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTModbus
                   Poco::OSP
                   Poco::RemotingNG
                   Poco::Net
                   Poco::Util
                   Poco::XML
                   Poco::Foundation
                 )

