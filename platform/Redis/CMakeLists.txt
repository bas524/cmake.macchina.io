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

add_library(Redis ${SRCS})
add_library(Poco::Redis ALIAS Redis)
set_target_properties(Redis
    PROPERTIES
    VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
    OUTPUT_NAME PocoRedis
    DEFINE_SYMBOL Redis_EXPORTS
)

target_link_libraries(Redis PUBLIC Poco::Net)
target_include_directories(Redis
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

POCO_INSTALL(Redis)
POCO_GENERATE_PACKAGE(Redis)

if(ENABLE_TESTS)
    add_subdirectory(testsuite)
#     add_subdirectory(samples)
endif()

