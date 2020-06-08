#
# CMakefile
#
# CMakefile for v8 JavaScript engine
#
if(CMAKE_VERSION VERSION_LESS "3.13")
  find_package(PythonInterp 2.7 REQUIRED)
else()
  find_package(Python2 COMPONENTS Interpreter REQUIRED)
endif()

include(ProcessorCount)
processorcount(N)
if (N EQUAL 0)
  set(N 2)
endif ()

get_filename_component(PYTHON_DIR "${Python_EXECUTABLE}" DIRECTORY)
set(PATH_SEP ":")
if (WIN32)
  set(PATH_SEP ";")
endif ()

if (NOT MSVC)
  set(GYP_GENERATOR make)
else ()
  set(GYP_GENERATOR ninja)
endif ()

set(GYPFLAGS "-Dcomponent=shared_library"
    "-Dlinux_use_bundled_binutils=0"
    "-Dlinux_use_bundled_gold=0"
    "-Dlinux_use_gold_flags=0"
    "-Dv8_enable_backtrace=0"
    "-Ddcheck_always_on=0"
    "-Dv8_enable_handle_zapping=0"
    "-Dv8_enable_slow_dchecks=0"
    "-Dv8_enable_inspector=0"
    "-Dv8_enable_gdbjit=0"
    "-Dwerror=''"
    "-Dtest_isolation_mode=noop"
    "-Dv8_optimized_debug=0"
    "-Dv8_enable_i18n_support=0"
    "-Dwant_separate_host_toolset=0"
    "-Dv8_use_external_startup_data=0"
    "-Dv8_random_seed=0")

if (V8_ENABLE_SNAPSHOT)
  list(APPEND GYPFLAGS "-Dv8_use_snapshot=true")
else ()
  list(APPEND GYPFLAGS "-Dv8_use_snapshot=false")
endif ()

set(V8ARCH "")

if (MSVC)
  if (CMAKE_CL_64)
    set(V8ARCH "x64")
  else ()
    set(V8ARCH "ia32")
  endif ()
else ()
  if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
    set(V8ARCH "x64")
  endif ()
endif ()

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "i386")
  set(V8ARCH "ia32")
endif ()

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "i686")
  set(V8ARCH "ia32")
endif ()

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "arm") #fixme : may be need to find substring
  set(V8ARCH "arm")
  list(APPEND GYPFLAGS "-Darm_fpu=default")
  list(APPEND GYPFLAGS "-Darm_float_abi=default")
  list(APPEND GYPFLAGS "-Darm_thumb=0")
  list(APPEND GYPFLAGS "-Darm_test_noprobe=on")
endif ()

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7")
  list(APPEND GYPFLAGS "-Darm_version=7")
endif ()

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
  set(V8ARCH "arm64")
endif ()

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "mipsel")
  set(V8ARCH "mipsel")
endif ()

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "mips")
  set(V8ARCH "mips")
endif ()

set(V8HOSTARCH "")

if (MSVC)
  if (CMAKE_CL_64)
    set(V8HOSTARCH "x64")
  else ()
    set(V8HOSTARCH "ia32")
  endif ()
else ()
  if (CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "AMD64")
    set(V8HOSTARCH "x64")
  endif ()
endif ()

if (CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "i386")
  set(V8HOSTARCH "ia32")
endif ()

if (CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "i686")
  set(V8HOSTARCH "ia32")
endif ()

if (CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm") #fixme : maybe error
  set(V8HOSTARCH "arm")
endif ()

if (CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "aarch64")
  set(V8HOSTARCH "arm64")
endif ()

list(APPEND GYPFLAGS "-Dv8_target_arch=${V8ARCH}")
list(APPEND GYPFLAGS "-Dtarget_arch=${V8ARCH}")
list(APPEND GYPFLAGS "-Dhost_arch=${V8HOSTARCH}")

if (V8ARCH STREQUAL "")
  message(FATAL_ERROR "Unknown target architecture ${CMAKE_SYSTEM_PROCESSOR}")
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  list(APPEND GYPFLAGS "-Dclang=1")
endif ()

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  set(v8targetlibdir "lib.target/")
endif ()

# Reduce linker memory usage on ARM systems
if (CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "armv7")
  set($ENV{LINK} "$ENV{LINK} -Xlinker --hash-size=31 -Xlinker --reduce-memory-overhead")
endif ()

add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/include/libplatform
                   PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_LIST_DIR}/include/libplatform
                   COMMENT "create directories ${CMAKE_CURRENT_LIST_DIR}/include/libplatform"
                   )

file(GLOB V8_HEADERS "${CMAKE_CURRENT_LIST_DIR}/v8/include/*.h")
foreach (V8_HDR ${V8_HEADERS})
  get_filename_component(HDR_NAME ${V8_HDR} NAME)
  file(COPY ${CMAKE_CURRENT_LIST_DIR}/v8/include/${HDR_NAME} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/include/)
endforeach ()

file(GLOB V8_PLATFORM_HEADERS "${CMAKE_CURRENT_LIST_DIR}/v8/include/libplatform/*.h")
foreach (V8_HDR ${V8_PLATFORM_HEADERS})
  get_filename_component(HDR_NAME ${V8_HDR} NAME)
  file(COPY ${CMAKE_CURRENT_LIST_DIR}/v8/include/libplatform/${HDR_NAME} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/include/libplatform/)
endforeach ()
if(NOT PYTHON_DIR)
  get_filename_component(PYTHON_DIR "${PYTHON_EXECUTABLE}" DIRECTORY)
endif()

add_custom_target(v8_config
                  COMMAND ${CMAKE_COMMAND} -E env "PATH=${PYTHON_DIR}${PATH_SEP}$ENV{PATH}" "${PYTHON_EXECUTABLE}" ${CMAKE_CURRENT_LIST_DIR}/tools/gyp/gyp_main.py ${GYPFLAGS} --generator-output="${POCO_BASE}/JS/V8/out" -Goutput_dir="${POCO_BASE}/JS/V8/out" -f ${GYP_GENERATOR} -I"${CMAKE_CURRENT_LIST_DIR}/common.gypi" --depth=. "${CMAKE_CURRENT_LIST_DIR}/v8/src/v8.gyp"
                  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                  DEPENDS ${CMAKE_CURRENT_LIST_DIR}/include/v8.h
                  COMMENT "configure V8 with gyp"
                  )


if (MSVC)
  add_custom_target(v8 ALL
                    COMMAND ${GYP_GENERATOR}.exe -j${N} -C ${CMAKE_CURRENT_LIST_DIR}/out/$<CONFIG> v8 v8_libplatform
                    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                    DEPENDS v8_config
                    COMMENT "build V8"
                    )
  add_custom_command(TARGET v8
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/out/$<CONFIG>/${v8targetlibdir}v8.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/v8.dll
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/out/$<CONFIG>/${v8targetlibdir}v8_libbase.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/v8_libbase.dll
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/out/$<CONFIG>/${v8targetlibdir}v8_libplatform.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/v8_libplatform.dll
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/out/$<CONFIG>/${v8targetlibdir}v8.dll.lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/v8.dll.lib
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/out/$<CONFIG>/${v8targetlibdir}v8_libbase.dll.lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/v8_libbase.dll.lib
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/out/$<CONFIG>/${v8targetlibdir}v8_libplatform.dll.lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/v8_libplatform.dll.lib
                     COMMENT "Copy V8 libraries to ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
                     )
  set(LIB_V8_LOCATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/v8.dll.lib)
  set(LIB_V8BASE_LOCATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/v8_libbase.dll.lib)
  set(LIB_V8PLATFORM_LOCATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/v8_libplatform.dll.lib)
else ()
  set(EXT_C_FLAGS -fpic)
  list(APPEND EXT_C_FLAGS "-DV8_DEPRECATION_WARNINGS=1")

  set(EXT_CXX_FLAGS -fpic)
  list(APPEND EXT_CXX_FLAGS "-DV8_DEPRECATION_WARNINGS=1")
  if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
      list(APPEND EXT_CXX_FLAGS -Wno-null-pointer-arithmetic)
      list(APPEND EXT_CXX_FLAGS -Wno-defaulted-function-deleted)
      list(APPEND EXT_CXX_FLAGS -Wno-deprecated-declarations)
  endif ()
  if (CMAKE_COMPILER_IS_GNUCXX)
      list(APPEND EXT_CXX_FLAGS -Wno-maybe-uninitialized)
      list(APPEND EXT_CXX_FLAGS -Wno-implicit-fallthrough)
      list(APPEND EXT_CXX_FLAGS -Wno-deprecated-declarations)
      list(APPEND EXT_CXX_FLAGS -Wno-unused-but-set-parameter)
      list(APPEND EXT_CXX_FLAGS -Wno-unused-function)
  endif()

  set(GYP_BUILD_TYPE ${CMAKE_BUILD_TYPE})
  if (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(GYP_BUILD_TYPE "Release")
  endif()
  if (CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(GYP_BUILD_TYPE "Release")
  endif()
  
  add_custom_target(v8 ALL
                    COMMAND ${GYP_GENERATOR} -j${N} -C ${CMAKE_CURRENT_LIST_DIR}/out BUILDTYPE=${GYP_BUILD_TYPE} CFLAGS="${EXT_C_FLAGS}" CXXFLAGS="${EXT_CXX_FLAGS}" v8 v8_libplatform
                    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                    DEPENDS v8_config
                    COMMENT "build V8"
                    )
  add_custom_command(TARGET v8
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/out/${GYP_BUILD_TYPE}/${v8targetlibdir}libv8${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/out/${GYP_BUILD_TYPE}/${v8targetlibdir}libv8_libbase${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/out/${GYP_BUILD_TYPE}/${v8targetlibdir}libv8_libplatform${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
                     COMMENT "Copy V8 libraries to ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
                     )
  set(LIB_V8_LOCATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libv8${CMAKE_SHARED_LIBRARY_SUFFIX})
  set(LIB_V8BASE_LOCATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libv8_libbase${CMAKE_SHARED_LIBRARY_SUFFIX})
  set(LIB_V8PLATFORM_LOCATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libv8_libplatform${CMAKE_SHARED_LIBRARY_SUFFIX})
endif ()

add_dependencies(v8 v8_config)

add_library(libv8 SHARED IMPORTED GLOBAL)
add_dependencies(libv8 v8)
add_library(js::libv8 ALIAS libv8)
set_target_properties(libv8 PROPERTIES
                      IMPORTED_LOCATION "${LIB_V8_LOCATION}"
                      IMPORTED_IMPLIB "${LIB_V8_LOCATION}"
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include")

add_library(libv8_libbase SHARED IMPORTED GLOBAL)
add_library(js::libv8_libbase ALIAS libv8_libbase)
set_target_properties(libv8_libbase PROPERTIES
                      IMPORTED_LOCATION "${LIB_V8BASE_LOCATION}"
                      IMPORTED_IMPLIB "${LIB_V8BASE_LOCATION}"
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include")

add_library(libv8_libplatform SHARED IMPORTED GLOBAL)
add_library(js::libv8_libplatform ALIAS libv8_libplatform)
set_target_properties(libv8_libplatform PROPERTIES
                      IMPORTED_LOCATION "${LIB_V8PLATFORM_LOCATION}"
                      IMPORTED_IMPLIB "${LIB_V8PLATFORM_LOCATION}"
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include")
