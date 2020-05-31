POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "OSP Simple Authentication Service"
        NAME com.appinf.osp.simple-auth
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR SimpleAuthBundleActivator
        #LAZY_START
        RUN_LEVEL 000
        OUT_BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/SimpleAuth.bndlspec
)

POCO_MAKE_BUNDLE(NAME com.appinf.osp.simple-auth
                 BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/SimpleAuth.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/SimpleAuth.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES Poco::OSP Poco::Util Poco::JSON Poco::XML Poco::Foundation)