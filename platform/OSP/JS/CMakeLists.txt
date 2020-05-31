add_definitions(-DV8_DEPRECATION_WARNINGS=1)
# Sources
set(SRCS
      src/JSExecutor.cpp
      src/JSExtensionPoint.cpp
      src/BundleWrapper.cpp
      src/ServiceRegistryWrapper.cpp
      src/ServiceListenerWrapper.cpp
      src/ServiceRefWrapper.cpp
      src/ModuleFactory.cpp
      src/ModuleExtensionPoint.cpp)

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME JS
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 3
        DEPENDENCIES
          Poco::JSBridge
          Poco::JSCore
          Poco::OSP
          Poco::Util
          Poco::XML
          Poco::Foundation
          js::libv8
          js::libv8_libbase
          js::libv8_libplatform
        OUTPUT_NAME PocoOSPJS
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "OSP JavaScript Integration"
        NAME com.appinf.osp.js
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR Poco::OSP::JS::JSBundleActivator
        #LAZY_START
        RUN_LEVEL 600
        CODES PocoJSCore PocoJSBridge PocoJSNet PocoJSData PocoOSPJS v8 v8_libbase v8_libplatform
        OUT_BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/JS.bndlspec
)

POCO_MAKE_BUNDLE(NAME com.appinf.osp.js
                 BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/JS.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/JSBundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPJS
                   Poco::JSBridge
                   Poco::JSCore
                   Poco::JSNet
                   Poco::OSP
                   Poco::RemotingNG
                   Poco::Util
                   Poco::XML
                   Poco::Foundation
                   js::libv8
                   js::libv8_libbase
                   js::libv8_libplatform)

add_subdirectory(Data)
add_subdirectory(Net)
add_subdirectory(Scheduler)
add_subdirectory(Web)