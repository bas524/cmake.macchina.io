set(SRCS "")

# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO(SRCS ${SRCS_G})

# Headers
file(GLOB_RECURSE HDRS_G "include/*.h")
POCO_HEADERS_AUTO(SRCS ${HDRS_G})

# Version Resource
if(MSVC AND BUILD_SHARED_LIBS)
  source_group("Resources" FILES ${POCO_BASE}/DLLVersion.rc)
  list(APPEND SRCS ${POCO_BASE}/DLLVersion.rc)
endif()

add_library(JSBridge ${SRCS})
add_library(Poco::JSBridge ALIAS JSBridge)
set_target_properties(JSBridge
                      PROPERTIES
                      VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
                      OUTPUT_NAME PocoJSBridge
                      DEFINE_SYMBOL JSBridge_EXPORTS
                      )

target_link_libraries(JSBridge PUBLIC Poco::JSCore Poco::RemotingNG Poco::Util Poco::XML Poco::Foundation)
target_include_directories(JSBridge
                           PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
                           )

POCO_INSTALL(JSBridge)
POCO_GENERATE_PACKAGE(JSBridge)
