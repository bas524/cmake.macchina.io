POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "OSP Secure Web Server"
        NAME osp.web.server.secure
        VERSION 1.1.3
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR SecureWebServerBundleActivator
        #LAZY_START
        DEPENDENCIES osp.web:1.1.0-2.0.0 poco.net.ssl:1.3.0-2.0.0
        RUN_LEVEL 000
        FILES bundle/*
        OUT_BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/SecureWebServer.bndlspec
)

POCO_MAKE_BUNDLE(NAME osp.web.server.secure
                 BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/SecureWebServer.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/SecureWebServerBundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES Poco::OSPWeb Poco::OSP Poco::NetSSL Poco::Net Poco::Util Poco::XML Poco::Foundation)