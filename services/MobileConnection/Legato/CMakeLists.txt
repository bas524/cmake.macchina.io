set(PROJECT_BUNDLE io.macchina.services.mobileconnection.legato)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/Legato.bndlspec)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io Mobile Connection Service for Legato"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::MobileConnection::Legato::BundleActivator
        #LAZY_START
        RUN_LEVEL 610
        DEPENDENCIES io.macchina.services.mobileconnection:1.0.0-2.0.0
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/MobileConnectionServiceImpl.cpp
                   src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTMobileConnection
                   Poco::OSP
                   Poco::RemotingNG
                   Poco::Util
                   Poco::XML
                   Poco::Foundation
                 )