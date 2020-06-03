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

add_library(JSNet ${SRCS})
add_library(Poco::JSNet ALIAS JSNet)
set_target_properties(JSNet
                      PROPERTIES
                      VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
                      OUTPUT_NAME PocoJSNet
                      DEFINE_SYMBOL JSNet_EXPORTS
                      )

target_link_libraries(JSNet PUBLIC Poco::JSCore Poco::Util Poco::XML Poco::Net Poco::Foundation)
target_include_directories(JSNet
                           PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
                           )

POCO_INSTALL(JSNet)
POCO_GENERATE_PACKAGE(JSNet)
