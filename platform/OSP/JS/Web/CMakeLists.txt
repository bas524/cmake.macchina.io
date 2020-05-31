add_definitions(-DV8_DEPRECATION_WARNINGS=1)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "OSP JavaScript Web Server Integration"
        NAME com.appinf.osp.js.web
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        #LAZY_START
        ACTIVATOR Poco::OSP::JS::Web::JSWebBundleActivator
        DEPENDENCIES com.appinf.osp.js:1.0.0-2.0.0 osp.web:1.0.0-2.0.0
        RUN_LEVEL 600
        FILES "bundle/*"
        OUT_BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/Web.bndlspec
)

POCO_MAKE_BUNDLE(NAME com.appinf.osp.js.web
                 BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/Web.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/JSServletExecutor.cpp
                   src/JSServletExecutorCache.cpp
                   src/JSServletFilter.cpp
                   src/JSServerPageFilter.cpp
                   src/JSSPage.cpp
                   src/JSSPageReader.cpp
                   src/SessionWrapper.cpp
                   src/JSWebBundleActivator.cpp
                 HEADERS
                   src/JSServletExecutor.h
                   src/JSServletExecutorCache.h
                   src/JSServletFilter.h
                   src/JSServerPageFilter.h
                   src/JSSPage.h
                   src/JSSPageReader.h
                   src/SessionWrapper.h
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPJS
                   Poco::JSNet
                   Poco::JSData
                   Poco::JSBridge
                   Poco::JSCore
                   Poco::OSPWeb
                   Poco::OSP
                   Poco::RemotingNG
                   Poco::Net
                   Poco::Util
                   Poco::XML
                   Poco::Data
                   Poco::Foundation
                 )