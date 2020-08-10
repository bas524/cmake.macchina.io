set(PROJECT_BUNDLE io.macchina.ros.client)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_BINARY_DIR}/ROS.bndlspec)

# Sources
set(SRCS
    src/BridgeClient.cpp
    )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME IoTROS
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES Poco::OSP Poco::Net Poco::Util Poco::XML Poco::JSON Poco::Foundation
        OUTPUT_NAME IoTROS
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io ROS Endpoint"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::ROS::BundleActivator
        #LAZY_START
        RUN_LEVEL 610
        CODES IoTROS:HAS_VERSION
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                 src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                 Poco::OSPIoTROS
                 Poco::OSP
                 Poco::Net
                 Poco::Util
                 Poco::XML
                 Poco::JSON
                 Poco::Foundation
                 )

add_subdirectory(App)