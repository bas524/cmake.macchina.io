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

if(NOT WIN32)
  execute_process(
          COMMAND uname -r
          OUTPUT_VARIABLE KERNEL_VER
  )
  message(STATUS "Check bone kernel..")
  string(FIND "${KERNEL_VER}" "bone" BONE_FOUND)
  if(BONE_FOUND GREATER -1)
    message(STATUS "Check bone kernel.. ok")
    add_compile_definitions(-DPOCO_SERIAL_ENABLE_BEAGLEBONE_RS485_HACK)
  else()
    message(STATUS "Check bone kernel.. not found")
  endif()
endif()

add_library(Serial ${SRCS})
add_library(Poco::Serial ALIAS Serial)
set_target_properties(Serial
                      PROPERTIES
                      VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
                      OUTPUT_NAME PocoSerial
                      DEFINE_SYMBOL Serial_EXPORTS
                      )

target_link_libraries(Serial PUBLIC Poco::Foundation)
target_include_directories(Serial
                           PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
                           )

POCO_INSTALL(Serial)
POCO_GENERATE_PACKAGE(Serial)