set(PROJECT_BUNDLE io.macchina.services.webevent)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/WebEvent.bndlspec)

# Sources
set(SRCS
    src/WebEventNotifier.cpp
    src/WebEventNotifierImpl.cpp
    )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME IoTWebEvent
        GENERATE_REMOTING ${CMAKE_CURRENT_LIST_DIR}/RemoteGen.xml
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES Poco::RemotingNG Poco::OSPWebEvent Poco::OSPWeb Poco::OSP Poco::Net Poco::Foundation
        OUTPUT_NAME IoTWebEvent

        WRAP_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/IoT/WebEvent/WebEventNotifier.h
        WRAP_INCLUDE_PATHS
        ${CMAKE_CURRENT_LIST_DIR}/include
        REMGEN_NAMESPACE IoT::WebEvent
        REMGEN_HEADERS_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/IoT/WebEvent
        REMGEN_SRC_PATH ${CMAKE_CURRENT_BINARY_DIR}/src
        REMGEN_COPYRIGHT "Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.\nAll rights reserved.\nSPDX-License-Identifier: Apache-2.0"
        REMGEN_SERVER_MODE
        REMGEN_ENABLE_OSP
        REMGEN_INCLUDE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/include
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io WebEvent Service"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::WebEvent::BundleActivator
        #LAZY_START
        RUN_LEVEL 610
        DEPENDENCIES com.appinf.osp.webevent:1.0.0-2.0.0
        CODES IoTWebEvent:HAS_VERSION
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTWebEvent
                   Poco::OSPWebEvent
                   Poco::OSPWeb
                   Poco::OSP
                   Poco::RemotingNG
                   Poco::Util
                   Poco::XML
                   Poco::Net
                   Poco::Foundation
                 )
