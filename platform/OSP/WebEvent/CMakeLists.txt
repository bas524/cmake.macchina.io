# Sources
set(SRCS
        src/WebEventService.cpp)

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME WebEvent
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 2
        DEPENDENCIES Poco::OSPWeb Poco::OSP Poco::Net Poco::Util Poco::XML Poco::Foundation
        OUTPUT_NAME PocoOSPWebEvent
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "OSP Web Events Service"
        NAME com.appinf.osp.webevent
        VERSION 1.0.1
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR Poco::OSP::WebEvent::WebEventBundleActivator
        #LAZY_START
        RUN_LEVEL 000
        DEPENDENCIES poco.net:1.3.0-2.0.0 osp.web:1.2.0-2.0.0
        CODES PocoOSPWebEvent
        FILES "bundle/*"
        OUT_BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/WebEventBundle.bndlspec
        )

POCO_MAKE_BUNDLE(NAME com.appinf.osp.webevent
                 BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/WebEventBundle.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/WebEventServiceImpl.cpp
                   src/WebEventRequestHandler.cpp
                   src/WebEventBundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPWebEvent
                   Poco::OSPWeb
                   Poco::OSP
                   Poco::Net
                   Poco::Util
                   Poco::XML
                   Poco::Foundation)

