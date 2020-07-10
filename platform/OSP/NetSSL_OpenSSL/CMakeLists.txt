POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "POCO NetSSL Library (OpenSSL)"
        NAME poco.net.ssl
        VERSION 1.10.1
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR NetSSLBundleActivator
        #LAZY_START
        DEPENDENCIES poco.net:1.10.1- poco.crypto:1.10.1-
        RUN_LEVEL 000
        CODES PocoNetSSL
        OUT_BUNDLESPEC ${CMAKE_CURRENT_BINARY_DIR}/NetSSL_OpenSSL.bndlspec
)

POCO_MAKE_BUNDLE(NAME poco.net.ssl
                 BUNDLESPEC ${CMAKE_CURRENT_BINARY_DIR}/NetSSL_OpenSSL.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/NetSSLBundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES Poco::OSP Poco::NetSSL Poco::Net Poco::Util Poco::XML Poco::Foundation)