# Sources
set(SRCS
        src/MediaTypeMapper.cpp
        src/WebServerDispatcher.cpp
        src/WebServerRequestHandlerFactory.cpp
        src/WebServerExtensionPoint.cpp
        src/WebSession.cpp
        src/WebRequestHandlerFactory.cpp
        src/WebServerRequestHandler.cpp
        src/WebSessionManager.cpp
        src/WebSessionStore.cpp
        src/WebServerService.cpp
        src/TokenValidator.cpp
        src/WebFilter.cpp
        src/WebFilterFactory.cpp
        src/WebFilterExtensionPoint.cpp)

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME Web
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 3
        DEPENDENCIES Poco::OSP Poco::Net Poco::Util Poco::XML Poco::Foundation
        OUTPUT_NAME PocoOSPWeb
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "OSP Web Server Foundation"
        NAME osp.web
        VERSION 1.7.2
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR WebBundleActivator
        #LAZY_START
        RUN_LEVEL 100
        DEPENDENCIES poco.net:1.3.0-2.0.0
        CODES PocoOSPWeb
        FILES "bundle/*"
        OUT_BUNDLESPEC ${CMAKE_CURRENT_BINARY_DIR}/WebBundle.bndlspec
        )

POCO_MAKE_BUNDLE(NAME osp.web
                 BUNDLESPEC ${CMAKE_CURRENT_BINARY_DIR}/WebBundle.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/WebBundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES Poco::OSPWeb)

