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

add_library(JSData ${SRCS})
add_library(Poco::JSData ALIAS JSData)
set_target_properties(JSData
                      PROPERTIES
                      VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
                      OUTPUT_NAME PocoJSData
                      DEFINE_SYMBOL JSData_EXPORTS
                      )

target_link_libraries(JSData PUBLIC Poco::JSCore Poco::Data Poco::Foundation)
target_include_directories(JSData
                           PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
                           )

POCO_INSTALL(JSData)
POCO_GENERATE_PACKAGE(JSData)
