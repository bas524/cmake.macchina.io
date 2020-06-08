# Sources
set(SRCS
    src/Sentence.cpp
    src/SentenceDecoder.cpp
    src/RMCProcessor.cpp
    src/GGAProcessor.cpp
    )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME IoTGNSSNMEA
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES Poco::Geo Poco::Foundation
        OUTPUT_NAME IoTGNSSNMEA
        DEFINITIONS NMEA_EXPORTS
)