find_package(OpenSSL REQUIRED)

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  add_definitions(-DOSX)
  add_compile_options(-Wno-deprecated-declarations)
endif ()

add_definitions(-DOPENSSL)

# Sources
set(SRCS
    src/Clients.c
    src/Heap.c
    src/LinkedList.c
    src/Log.c
    src/MQTTClient.c
    src/MQTTPacket.c
    src/MQTTPacketOut.c
    src/MQTTPersistence.c
    src/MQTTPersistenceDefault.c
    src/MQTTProtocolClient.c
    src/MQTTProtocolOut.c
    src/MQTTVersion.c
    src/Messages.c
    src/SSLSocket.c
    src/Socket.c
    src/SocketBuffer.c
    src/StackTrace.c
    src/Thread.c
    src/Tree.c
    src/utf-8.c
    )

# Headers
file(GLOB_RECURSE HDRS "include/*.h")

POCO_MAKE_BUNDLE_LIBRARY(
        NAME PahoMQTT
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES OpenSSL::SSL OpenSSL::Crypto
        OUTPUT_NAME PahoMQTT
)