POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "BundleAdmin"
        NAME com.appinf.osp.bundleadmin
        VERSION 1.1.2
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR CryptoBundleActivator
        #LAZY_START
        RUN_LEVEL 100
        DEPENDECIES osp.web:1.0.0-2.0.0
        FILES "bundle/*"
        OUT_BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/BundleAdmin.bndlspec
)

POCO_MAKE_BUNDLE(NAME com.appinf.osp.bundleadmin
                 BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/BundleAdmin.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/BundleAdmin.cpp
                   src/BundleInstallHandler.cpp
                   src/BundleListHandler.cpp
                   src/BundleInfoHandler.cpp
                   src/RequestHandler.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES Poco::OSPWeb Poco::OSP Poco::Net Poco::Util Poco::XML Poco::Foundation)


