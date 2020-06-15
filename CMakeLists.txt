cmake_minimum_required(VERSION 3.5.0)

project(macchina.io)

file(STRINGS "${PROJECT_SOURCE_DIR}/VERSION" PACKAGE_VERSION)
string(REGEX REPLACE "([0-9]+)\\.[0-9]+\\.[0-9]+.*" "\\1" CPACK_PACKAGE_VERSION_MAJOR ${PACKAGE_VERSION})
string(REGEX REPLACE "[0-9]+\\.([0-9]+)\\.[0-9]+.*" "\\1" CPACK_PACKAGE_VERSION_MINOR ${PACKAGE_VERSION})
string(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" CPACK_PACKAGE_VERSION_PATCH ${PACKAGE_VERSION})

set(PROJECT_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
set(RELEASE_NAME "Unstable-trunk")

# Put the libaries and binaries that get built into directories at the
# top of the build tree rather than in hard-to-find leaf
# directories. This simplifies manual testing and the use of the build
# tree rather than installed Boost libraries.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# Windows DLLs are "runtime" for CMake. Output them to "bin" like the Visual Studio projects do.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG  ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO  ${CMAKE_BINARY_DIR}/bin)

set(MACCHINA_BASE ${CMAKE_SOURCE_DIR})
set(POCO_BASE ${CMAKE_SOURCE_DIR}/platform)

option(USE_DELIVERY "Use binary delivery" OFF)

if (USE_DELIVERY)
  find_program(AIR_CLI air-cli)
  set(DELIVERY_ROOT ${CMAKE_CURRENT_LIST_DIR}/.delivery)
  set(DELIVERY_FILE ${CMAKE_CURRENT_LIST_DIR}/delivery.txt.in)
  set(DELIVERY_VERSION "6.0.1520.0")
  set(DELIVERY_EXTENSION "tar.gz")
  set(DELIVERY_TOOLCHAIN_ID ${KL_CM_TOOLCHAIN_ID}_release)

  if(MSVC)
    set(DELIVERY_EXTENSION "zip")
    if(NOT ${CMAKE_BUILD_TYPE} OR ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
      set(DELIVERY_TOOLCHAIN_ID ${KL_CM_TOOLCHAIN_ID}_debug)
    endif()
  endif()

  include(cmake/delivery.cmake)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
endif()

if(MSVC)
  add_definitions(-DNOMINMAX)
  add_definitions(-DPOCO_DLL)
  add_compile_options(/MP)
endif()

add_subdirectory(platform)

set(BUNDLES_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/bundles)

if(TARGET Bundle::Creator)
  include(${POCO_BASE}/OSP/cmake/PocoOSPMacros.cmake)

  if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/protocols)
    add_subdirectory(protocols)
  endif()

  if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/devices)
    add_subdirectory(devices)
  endif()

  if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/services)
    add_subdirectory(services)
  endif()

  if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/webui)
    add_subdirectory(webui)
  endif()

endif()

add_subdirectory(server)