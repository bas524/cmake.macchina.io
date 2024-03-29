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

add_library(Net ${SRCS})
add_library(Poco::Net ALIAS Net)
set_target_properties(Net
    PROPERTIES
    VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
    OUTPUT_NAME PocoNet
    DEFINE_SYMBOL Net_EXPORTS
)

target_link_libraries(Net PUBLIC Poco::Foundation)
# Windows and WindowsCE need additional libraries
if(WIN32)
    target_link_libraries(Net PUBLIC "iphlpapi.lib")
    if(WINCE)
        target_link_libraries(Net PUBLIC "ws2.lib")
    else()
        target_link_libraries(Net PUBLIC "ws2_32.lib")
    endif()
endif(WIN32)

target_include_directories(Net
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

POCO_INSTALL(Net)
POCO_GENERATE_PACKAGE(Net)

if(ENABLE_TESTS)
    add_subdirectory(samples)
    add_subdirectory(testsuite)
endif()

