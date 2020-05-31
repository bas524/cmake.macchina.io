POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "OSP Web Server"
        NAME osp.web.server
        VERSION 1.1.3
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR WebServerBundleActivator
        #LAZY_START
        DEPENDENCIES osp.web:1.1.0-2.0.0
        RUN_LEVEL 000
        FILES bundle/*
        OUT_BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/WebServer.bndlspec
)

POCO_MAKE_BUNDLE(NAME osp.web.server
                 BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/WebServer.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/WebServerBundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES Poco::OSPWeb Poco::OSP Poco::Net Poco::Util Poco::XML Poco::Foundation)