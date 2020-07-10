POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "POCO Net Library"
        NAME poco.net
        VERSION 1.10.1
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR NetBundleActivator
        #LAZY_START
        RUN_LEVEL 000
        CODES PocoNet
        OUT_BUNDLESPEC ${CMAKE_CURRENT_BINARY_DIR}/Net.bndlspec
        )

POCO_MAKE_BUNDLE(NAME poco.net
                 BUNDLESPEC ${CMAKE_CURRENT_BINARY_DIR}/Net.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/NetBundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES Poco::OSP Poco::Net Poco::Util Poco::XML Poco::Foundation)

