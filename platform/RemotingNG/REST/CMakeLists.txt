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

add_library(RemotingNGREST ${SRCS})
add_library(Poco::RemotingNGREST ALIAS RemotingNGREST)
set_target_properties(RemotingNGREST
        PROPERTIES
        VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
        OUTPUT_NAME PocoRemotingNGREST
        DEFINE_SYMBOL RemotingNGREST_EXPORTS
        )

target_link_libraries(RemotingNGREST PUBLIC Poco::Foundation Poco::RemotingNG Poco::Net Poco::JSON)
target_include_directories(RemotingNGREST
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

POCO_INSTALL(RemotingNGREST)
POCO_GENERATE_PACKAGE(RemotingNGREST)
