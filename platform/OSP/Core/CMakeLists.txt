POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "OSP Core"
        NAME osp.core
        VERSION 1.7.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR CoreBundleActivator
        #LAZY_START
        RUN_LEVEL 000
        OUT_BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/Core.bndlspec
)

POCO_MAKE_BUNDLE(NAME osp.core
                 BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/Core.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/CoreBundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES Poco::OSP Poco::Util Poco::XML Poco::Foundation)

