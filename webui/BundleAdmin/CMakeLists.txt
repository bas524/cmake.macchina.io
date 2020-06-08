set(PROJECT_BUNDLE io.macchina.webui.bundleadmin)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/BundleAdmin.bndlspec)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io Bundle Administration Utility"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::Web::BundleAdmin::BundleActivator
        #LAZY_START
        DEPENDENCIES osp.web:1.1.0-2.0.0
        RUN_LEVEL 620
        FILES bundle/*
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/BundleActivator.cpp
                   src/BundleRequestHandler.cpp
                   src/BundleListRequestHandler.cpp
                   src/BundleActionsRequestHandler.cpp
                   src/Utility.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPWeb
                   Poco::OSP
                   Poco::Net
                   Poco::Util
                   Poco::JSON
                   Poco::XML
                   Poco::Foundation
                 BUNDLE_CREATOR_EXT_ATTRS no-deflate=png,gif,jpg
                 )