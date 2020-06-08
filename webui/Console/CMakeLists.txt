set(PROJECT_BUNDLE io.macchina.webui.console)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/Console.bndlspec)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io Web Console"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::Web::Console::BundleActivator
        #LAZY_START
        DEPENDENCIES osp.web:1.1.0-2.0.0
        RUN_LEVEL 660
        FILES bundle/*
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/BundleActivator.cpp
                   src/ConsoleRequestHandler.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPWeb
                   Poco::OSP
                   Poco::Net
                   Poco::Util
                   Poco::XML
                   Poco::Foundation
                 BUNDLE_CREATOR_EXT_ATTRS no-deflate=png,gif,jpg
                 )