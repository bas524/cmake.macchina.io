if (USE_DELIVERY)
  find_package(OpenSSL_PDK REQUIRED)
else()
  find_package(OpenSSL REQUIRED)
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  add_definitions(-DOSX)
  add_compile_options(-Wno-deprecated-declarations)
endif ()
if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-DWIN32_LEAN_AND_MEAN)
  add_definitions(-DNOMINMAX)
endif()
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

if(USE_DELIVERY)
  set (DEPENDENCIES openssl_pdk::ssl_static openssl_pdk::crypto_static)
else()
  set (DEPENDENCIES OpenSSL::SSL OpenSSL::Crypto)
endif()

POCO_MAKE_BUNDLE_LIBRARY(
        NAME PahoMQTT
        SOURCES ${SRCS}
        HEADERS ${HDRS}
        INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
        VERSION 1
        DEPENDENCIES ${DEPENDENCIES}
        OUTPUT_NAME PahoMQTT
)

if (MSVC)
  target_link_libraries(PahoMQTT PUBLIC ws2_32.lib Crypt32.lib)
endif()