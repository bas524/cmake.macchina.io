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

add_library(RemotingNG ${SRCS})
add_library(Poco::RemotingNG ALIAS RemotingNG)
set_target_properties(RemotingNG
    PROPERTIES
    VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
    OUTPUT_NAME PocoRemotingNG
    DEFINE_SYMBOL RemotingNG_EXPORTS
)

target_link_libraries(RemotingNG PUBLIC Poco::Foundation)
target_include_directories(RemotingNG
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

POCO_INSTALL(RemotingNG)
POCO_GENERATE_PACKAGE(RemotingNG)

if(ENABLE_TESTS)
    add_subdirectory(testsuite)
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/TCP)
    add_subdirectory(TCP)
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/RemoteGen)
    add_subdirectory(RemoteGen)
endif()