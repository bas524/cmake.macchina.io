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

add_library(JSCore ${SRCS})
add_library(Poco::JSCore ALIAS JSCore)
set_target_properties(JSCore
                      PROPERTIES
                      VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
                      OUTPUT_NAME PocoJSCore
                      DEFINE_SYMBOL JSCore_EXPORTS
                      )

target_link_libraries(JSCore PUBLIC Poco::Foundation Poco::Util Poco::JSON Poco::XML js::libv8 js::libv8_libbase js::libv8_libplatform)
target_include_directories(JSCore
                           PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
                           )

POCO_INSTALL(JSCore)
POCO_GENERATE_PACKAGE(JSCore)
