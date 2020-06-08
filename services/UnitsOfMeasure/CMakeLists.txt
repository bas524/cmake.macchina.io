set(PROJECT_BUNDLE io.macchina.services.unitsofmeasure)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/UnitsOfMeasure.bndlspec)

# Sources
set(SRCS
    src/UnitsOfMeasureService.cpp
    src/UnitsOfMeasureServiceImpl.cpp
    src/UCUMEssenceParser.cpp
    )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME IoTUnitsOfMeasure
        GENERATE_REMOTING ${CMAKE_CURRENT_LIST_DIR}/RemoteGen.xml
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES Poco::RemotingNG Poco::OSP Poco::Zip Poco::Util Poco::JSON Poco::XML Poco::Foundation
        OUTPUT_NAME IoTUnitsOfMeasure

        WRAP_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/IoT/UnitsOfMeasure/UnitsOfMeasureService.h
        WRAP_INCLUDE_PATHS
        ${CMAKE_CURRENT_LIST_DIR}/include
        REMGEN_NAMESPACE IoT::UnitsOfMeasure
        REMGEN_HEADERS_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/IoT/UnitsOfMeasure
        REMGEN_SRC_PATH ${CMAKE_CURRENT_BINARY_DIR}/src
        REMGEN_COPYRIGHT "Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.\nAll rights reserved.\nSPDX-License-Identifier: Apache-2.0"
        REMGEN_SERVER_MODE
        REMGEN_ENABLE_OSP
        REMGEN_INCLUDE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/include
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io Units of Measure Service"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR IoT::UnitsOfMeasure::BundleActivator
        #LAZY_START
        RUN_LEVEL 000
        CODES IoTUnitsOfMeasure:HAS_VERSION
        FILES bundle/*
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES
                   src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::OSPIoTUnitsOfMeasure
                   Poco::OSP
                   Poco::Net
                   Poco::Util
                   Poco::JSON
                   Poco::XML
                   Poco::Foundation
                 )

if (ENABLE_TESTS)
#  add_subdirectory(testsuite)
endif()