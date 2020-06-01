set(PROJECT_BUNDLE io.macchina.modbus.core)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/Modbus.bndlspec)

# Sources
set(SRCS
    src/ModbusMaster.cpp
    src/ModbusException.cpp
    src/PDUWriter.cpp
    src/PDUReader.cpp
    )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME IoTModbus
        GENERATE_REMOTING ${CMAKE_CURRENT_LIST_DIR}/RemoteGen.xml
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES Poco::RemotingNG Poco::OSP Poco::Util Poco::XML Poco::JSON Poco::Foundation
        OUTPUT_NAME IoTModbus

        WRAP_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/include/IoT/Modbus/ModbusMaster.h
        WRAP_INCLUDE_PATHS
        ${CMAKE_CURRENT_LIST_DIR}/include
        REMGEN_NAMESPACE IoT::Modbus
        REMGEN_HEADERS_PATH ${CMAKE_CURRENT_BINARY_DIR}/include/IoT/Modbus
        REMGEN_SRC_PATH ${CMAKE_CURRENT_BINARY_DIR}/src
        REMGEN_COPYRIGHT "Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.\nAll rights reserved.\nSPDX-License-Identifier: Apache-2.0"
        REMGEN_SERVER_MODE
        REMGEN_ENABLE_OSP
        REMGEN_INCLUDE_ROOT ${CMAKE_CURRENT_BINARY_DIR}/include
)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io Modbus Core Libraries"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        #LAZY_START
        RUN_LEVEL 610
        CODES IoTModbus:HAS_VERSION
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 DEPENDENCIES Poco::OSPIoTModbus)

add_subdirectory(TCP)
add_subdirectory(RTU)