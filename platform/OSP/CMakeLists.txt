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

add_library(OSP ${SRCS})
add_library(Poco::OSP ALIAS OSP)
set_target_properties(OSP
                      PROPERTIES
                      SOVERSION 2
                      OUTPUT_NAME PocoOSP
                      DEFINE_SYMBOL OSP_EXPORTS
                      )

target_link_libraries(OSP PUBLIC Poco::Foundation Poco::Zip Poco::Util Poco::XML)
target_include_directories(OSP
                           PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
                           )

POCO_INSTALL(OSP)
POCO_GENERATE_PACKAGE(OSP)

if(ENABLE_TESTS)
# FIXME : add Unit subdir
#  add_subdirectory(samples)
#  add_subdirectory(testsuite)
endif()

if(NOT BUNDLES_OUTPUT_DIR)
  set(BUNDLES_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/bundles)
endif()

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/BundleCreator)
  include(${CMAKE_CURRENT_LIST_DIR}/cmake/PocoOSPMacros.cmake)
  add_subdirectory(BundleCreator)
  add_subdirectory(CodeCacheUtility)
  add_subdirectory(StripBundle)
  add_subdirectory(Core)
  if(TARGET Poco::Net)
    add_subdirectory(Net)
  endif()
  if(TARGET Poco::Data)
    add_subdirectory(Data)
  endif()

  if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/RemotingNG/TCP AND TARGET Poco::RemotingNGTCP)
    add_subdirectory(RemotingNG/TCP)
  endif()

  if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/NetSSL_OpenSSL AND TARGET Poco::NetSSL)
    add_subdirectory(NetSSL_OpenSSL)
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/Crypto)
      add_subdirectory(Crypto)
    endif()
  endif()

  if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/Web)
    add_subdirectory(Web)
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/BundleAdmin)
      add_subdirectory(BundleAdmin)
    endif()
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/WebEvent)
      add_subdirectory(WebEvent)
    endif()
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/WebServer)
      add_subdirectory(WebServer)
    endif()
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/SecureWebServer)
      add_subdirectory(SecureWebServer)
    endif()
  endif()

  if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/JS AND TARGET Poco::JSBridge)
    add_subdirectory(JS)
  endif()

  if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/SimpleAuth)
    add_subdirectory(SimpleAuth)
  endif()

endif()