include(CMakeParseArguments)
if (NOT POCO_BASE)
  set(POCO_BASE ${PROJECT_SOURCE_DIR})
endif()
function(POCO_MAKE_BUNDLE)
  cmake_parse_arguments(
          PARSED_ARGS # prefix of output variables
          "PLATFORM_INDEPENDENT" # list of names of the boolean arguments (only defined ones will be true)
          "NAME;BUNDLESPEC;BUNDLES_DIR" # list of names of mono-valued arguments
          "SOURCES;HEADERS;INCLUDES;DEPENDENCIES;BUNDLE_CREATOR_EXT_ATTRS" # list of names of multi-valued arguments (output variables are lists)
          ${ARGN} # arguments of the function to parse, here we take the all original ones
  )
  # note: if it remains unparsed arguments, here, they can be found in variable PARSED_ARGS_UNPARSED_ARGUMENTS
  if(NOT PARSED_ARGS_NAME)
    message(FATAL_ERROR "You must provide a bundle name")
  endif()

  if(NOT PARSED_ARGS_BUNDLESPEC)
    message(FATAL_ERROR "You must provide a bndlspec file")
  endif()

  if(NOT PARSED_ARGS_BUNDLES_DIR)
    message(FATAL_ERROR "You must provide a bundle output dir")
  endif()

  set(TO_REMOVE "")
  set(TO_INCLUDE "")
  if(PARSED_ARGS_SOURCES)
    foreach(SRC ${PARSED_ARGS_SOURCES})
      get_filename_component(SRC_EXT ${SRC} EXT)
      get_filename_component(SRC_BASENAME ${SRC} NAME_WE)
      if (SRC_EXT STREQUAL ".cpsp")
        list(APPEND TO_REMOVE ${SRC})
        list(APPEND TO_INCLUDE ${CMAKE_CURRENT_BINARY_DIR}/src/${SRC_BASENAME}.cpp)
        list(APPEND TO_INCLUDE ${CMAKE_CURRENT_BINARY_DIR}/src/${SRC_BASENAME}.h)
      endif()
    endforeach()

    if (TO_REMOVE)
      add_custom_command(OUTPUT ${TO_INCLUDE}
                         PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/src
                         PRE_BUILD
                         COMMAND $<TARGET_FILE:PageCompiler> -o${CMAKE_CURRENT_BINARY_DIR}/src --osp ${TO_REMOVE}
                         WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                         COMMENT "Compiling pages ${TO_REMOVE}"
                         DEPEND ${CMAKE_CURRENT_BINARY_DIR}/src
                         )
    endif()

    foreach(REM_ITEM ${TO_REMOVE})
      list(REMOVE_ITEM PARSED_ARGS_SOURCES ${REM_ITEM})
    endforeach()

    # Version Resource
    if(MSVC AND BUILD_SHARED_LIBS)
      source_group("Resources" FILES ${POCO_BASE}/DLLVersion.rc)
      list(APPEND PARSED_ARGS_SOURCES ${POCO_BASE}/DLLVersion.rc)
    endif()

    POCO_SOURCES_AUTO(BNDL_SRCS ${PARSED_ARGS_SOURCES})


    if(PARSED_ARGS_HEADERS)
      POCO_HEADERS_AUTO(BNDL_SRCS ${PARSED_ARGS_HEADERS})
    endif()

    foreach(INC_ITEM ${TO_INCLUDE})
      list(APPEND BNDL_SRCS ${INC_ITEM})
    endforeach()

    add_library(${PARSED_ARGS_NAME} ${BNDL_SRCS})
    add_custom_command(TARGET ${PARSED_ARGS_NAME}
                       PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_LIST_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}
                       )

    set_target_properties(${PARSED_ARGS_NAME}
                          PROPERTIES
                          OUTPUT_NAME ${PARSED_ARGS_NAME}
                          PREFIX ""
                          LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}
                          RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}
                          COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}
                          )

    if(PARSED_ARGS_DEPENDENCIES)
      target_link_libraries(${PARSED_ARGS_NAME} PRIVATE ${PARSED_ARGS_DEPENDENCIES})
    endif()

    if(PARSED_ARGS_INCLUDES)
      target_include_directories(${PARSED_ARGS_NAME} PRIVATE ${PARSED_ARGS_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR}/src ${CMAKE_CURRENT_LIST_DIR}/src)
    endif()
  else()
    message(STATUS "bundle ${PARSED_ARGS_NAME} hasn't sources")
  endif()

  set(MAKE_BUNDLE_DEPENDENCIES Bundle::Creator)
  if (TARGET ${PARSED_ARGS_NAME})
    list(APPEND MAKE_BUNDLE_DEPENDENCIES ${PARSED_ARGS_NAME})
  endif()

  if(NOT PARSED_ARGS_PLATFORM_INDEPENDENT)
    add_custom_target(${PARSED_ARGS_NAME}.bundle
                      COMMAND $<TARGET_FILE:BundleCreator> -n${CMAKE_SYSTEM_NAME} -a${CMAKE_SYSTEM_PROCESSOR} ${PARSED_ARGS_BUNDLE_CREATOR_EXT_ATTRS} -o${PARSED_ARGS_BUNDLES_DIR} ${PARSED_ARGS_BUNDLESPEC}
                      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                      COMMENT "Make bundle ${out} into ${PARSED_ARGS_BUNDLES_DIR}"
                      DEPENDS ${MAKE_BUNDLE_DEPENDENCIES}
                      )
  else()
    add_custom_target(${PARSED_ARGS_NAME}.bundle
                      COMMAND $<TARGET_FILE:BundleCreator> ${PARSED_ARGS_BUNDLE_CREATOR_EXT_ATTRS} -o${PARSED_ARGS_BUNDLES_DIR} ${PARSED_ARGS_BUNDLESPEC}
                      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                      COMMENT "Make bundle ${out} into ${PARSED_ARGS_BUNDLES_DIR}"
                      DEPENDS ${MAKE_BUNDLE_DEPENDENCIES}
                      )
  endif()

  if (PARSED_ARGS_DEPENDENCIES)
    add_dependencies(${PARSED_ARGS_NAME}.bundle ${PARSED_ARGS_DEPENDENCIES})
  endif()
endfunction()

function(POCO_MAKE_BUNDLE_LIBRARY)
  cmake_parse_arguments(
          PARSED_ARGS # prefix of output variables
          "REMGEN_ENABLE_OSP;REMGEN_ENABLE_TIMESTAMPS;REMGEN_ENABLE_FLAT_INCLUDES;REMGEN_CLIENT_MODE;REMGEN_SERVER_MODE;REMGEN_BOTH_MODE;REMGEN_INTERFACE_MODE" # list of names of the boolean arguments (only defined ones will be true)
          "NAME;VERSION;OUTPUT_NAME;GENERATE_REMOTING;REMGEN_NAMESPACE;REMGEN_HEADERS_PATH;REMGEN_SRC_PATH;REMGEN_COPYRIGHT;REMGEN_INCLUDE_ROOT" # list of names of mono-valued arguments
          "SOURCES;HEADERS;INCLUDES;DEPENDENCIES;WRAP_HEADERS;WRAP_INCLUDE_PATHS" # list of names of multi-valued arguments (output variables are lists)
          ${ARGN} # arguments of the function to parse, here we take the all original ones
  )
  if(NOT PARSED_ARGS_NAME)
    message(FATAL_ERROR "You must provide a bundle library name")
  endif()

  if(NOT PARSED_ARGS_SOURCES)
    message(FATAL_ERROR "You must provide a bundle library sources")
  endif()

  # Version Resource
  if(MSVC AND BUILD_SHARED_LIBS)
    source_group("Resources" FILES ${POCO_BASE}/DLLVersion.rc)
    list(APPEND BNDL_SRCS ${POCO_BASE}/DLLVersion.rc)
  endif()
  if (PARSED_ARGS_GENERATE_REMOTING)
    if (MSVC)
      set(COMPILER_ID msvc)
    elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
      set(COMPILER_ID clang)
    else ()
      set(COMPILER_ID gcc)
    endif ()

    set(GENERATED_SOURCES "")
    if(NOT PARSED_ARGS_WRAP_HEADERS)
      message(FATAL_ERROR "You must provide a headers list for wrapping")
    else()
      foreach(HDR ${PARSED_ARGS_WRAP_HEADERS})
        set(_headers_list "${_headers_list}\n${HDR}")
        get_filename_component(HDR_NAME ${HDR} NAME_WE)
        #TODO : for not server mode source list should be extend
        set(HAS_REMOTE "")
        file(STRINGS ${HDR} HAS_REMOTE REGEX "\\/\\/\\s*@\\s* remote\\s*")
        file(STRINGS ${HDR} HAS_BASIC_EVENT REGEX "Poco\\:\\:BasicEvent\\<.*\\>\\s*")
        if (HAS_REMOTE)
          list(APPEND GENERATED_SOURCES ${PARSED_ARGS_REMGEN_SRC_PATH}/I${HDR_NAME}.cpp)
          list(APPEND GENERATED_SOURCES ${PARSED_ARGS_REMGEN_SRC_PATH}/${HDR_NAME}RemoteObject.cpp)
          list(APPEND GENERATED_SOURCES ${PARSED_ARGS_REMGEN_SRC_PATH}/${HDR_NAME}ServerHelper.cpp)
          list(APPEND GENERATED_SOURCES ${PARSED_ARGS_REMGEN_SRC_PATH}/${HDR_NAME}Skeleton.cpp)
          if (HAS_BASIC_EVENT)
            list(APPEND GENERATED_SOURCES ${PARSED_ARGS_REMGEN_SRC_PATH}/${HDR_NAME}EventDispatcher.cpp)
          endif()
        endif()
      endforeach()
    endif()

    set(_include_paths "")
    foreach(INC_PATH ${PARSED_ARGS_WRAP_INCLUDE_PATHS})
      set(_include_paths "${_include_paths}\n${INC_PATH}")
    endforeach()

    set(_out_namespace ${PARSED_ARGS_REMGEN_NAMESPACE})

    set(_out_include_path ${PARSED_ARGS_REMGEN_HEADERS_PATH})

    set(_out_src_path ${PARSED_ARGS_REMGEN_SRC_PATH})

    set(_out_include_root_path ${PARSED_ARGS_REMGEN_INCLUDE_ROOT})

    if(NOT PARSED_ARGS_REMGEN_COPYRIGHT)
      message(FATAL_ERROR "You must provide a copyright")
    else()
      set(_out_copyright ${PARSED_ARGS_REMGEN_COPYRIGHT})
    endif()

    if(PARSED_ARGS_REMGEN_CLIENT_MODE)
      set(MODE client)
    endif()

    if(PARSED_ARGS_REMGEN_SERVER_MODE)
      if(NOT MODE)
        set(MODE server)
      else()
        set(MODE both)
      endif()
    endif()

    if(PARSED_ARGS_REMGEN_BOTH_MODE)
      if(NOT MODE)
        set(MODE both)
      else()
        message(WARNING "Please set only one mode client, server or both")
      endif()
    endif()

    if(PARSED_ARGS_REMGEN_INTERFACE_MODE)
      if(NOT MODE)
        set(MODE interface)
      else()
        message(FATAL_ERROR "Please set only one mode client, server, both or interface")
      endif()
    endif()

    if(NOT MODE)
      message(FATAL_ERROR "Please set mode : client, server, both or interface")
    else()
      set(_out_mode ${MODE})
    endif()

    if(PARSED_ARGS_REMGEN_ENABLE_OSP)
      set(_out_osp_enable "true")
    else()
      set(_out_osp_enable "false")
    endif()

    if(PARSED_ARGS_REMGEN_ENABLE_TIMESTAMPS)
      set(_out_timestamps_enable "true")
    else()
      set(_out_timestamps_enable "false")
    endif()

    if(PARSED_ARGS_REMGEN_ENABLE_FLAT_INCLUDES)
      set(_out_flat_include_enable "true")
    else()
      set(_out_flat_include_enable "false")
    endif()

    configure_file(${POCO_BASE}/OSP/cmake/RemoteGen.xml.in ${PARSED_ARGS_GENERATE_REMOTING})

    add_custom_command(OUTPUT ${GENERATED_SOURCES}
                       BYPRODUCTS ${GENERATED_SOURCES}
                       COMMAND $<TARGET_FILE:RemoteGenNG> -C${COMPILER_ID} -DPOCO_BASE=${POCO_BASE} ${PARSED_ARGS_GENERATE_REMOTING}
                       COMMENT "Generate proxy-stubs for ${PARSED_ARGS_NAME}"
                       WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                       DEPENDS RemoteGenNG
                      )
  endif()

  POCO_SOURCES_AUTO(BNDL_SRCS ${PARSED_ARGS_SOURCES})

  if(PARSED_ARGS_HEADERS)
    POCO_HEADERS_AUTO(BNDL_SRCS ${PARSED_ARGS_HEADERS})
  endif()

  add_library(${PARSED_ARGS_NAME} ${BNDL_SRCS} ${GENERATED_SOURCES})
  add_library(Poco::OSP${PARSED_ARGS_NAME} ALIAS ${PARSED_ARGS_NAME})
  set_target_properties(${PARSED_ARGS_NAME}
                        PROPERTIES
                        SOVERSION ${PARSED_ARGS_VERSION}
                        OUTPUT_NAME ${PARSED_ARGS_OUTPUT_NAME}
                        )

  target_link_libraries(${PARSED_ARGS_NAME} PUBLIC ${PARSED_ARGS_DEPENDENCIES})
  target_include_directories(${PARSED_ARGS_NAME}
                             PUBLIC
                             $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                             $<BUILD_INTERFACE:${PARSED_ARGS_REMGEN_INCLUDE_ROOT}>
                             $<INSTALL_INTERFACE:include>
                             PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
                             )

endfunction()

function(POCO_GENERATE_BUNDLESPEC)
  cmake_parse_arguments(
          PARSED_ARGS # prefix of output variables
          "LAZY_START;NO_CODES" # list of names of the boolean arguments (only defined ones will be true)
          "DESCRIPTION;NAME;VERSION;VENDOR;COPYRIGHT;ACTIVATOR;RUN_LEVEL;OUT_BUNDLESPEC" # list of names of mono-valued arguments
          "DEPENDENCIES;CODES;FILES" # list of names of multi-valued arguments (output variables are lists)
          ${ARGN} # arguments of the function to parse, here we take the all original ones
  )

  if(NOT PARSED_ARGS_OUT_BUNDLESPEC)
    message(FATAL_ERROR "You must provide a bundle-spec file")
  endif()

  if(NOT PARSED_ARGS_DESCRIPTION)
    message(FATAL_ERROR "You must provide a bundle description")
  else()
    set(_bundle_description ${PARSED_ARGS_DESCRIPTION})
  endif()

  if(NOT PARSED_ARGS_NAME)
    message(FATAL_ERROR "You must provide a bundle symbolic name")
  else()
    set(_bundle_simbolic_name ${PARSED_ARGS_NAME})
  endif()

  if(NOT PARSED_ARGS_VERSION)
    message(FATAL_ERROR "You must provide a bundle version")
  else()
    set(_bundle_version ${PARSED_ARGS_VERSION})
  endif()

  if(PARSED_ARGS_ACTIVATOR)
    set(_bundle_activator
        "\n    <activator>
        <class>${PARSED_ARGS_ACTIVATOR}</class>
        <library>${PARSED_ARGS_NAME}</library>
    </activator>")
  endif()

  if(PARSED_ARGS_VENDOR)
    set(_bundle_vendor ${PARSED_ARGS_VENDOR})
  endif()

  if(PARSED_ARGS_COPYRIGHT)
    set(_bundle_copyright ${PARSED_ARGS_COPYRIGHT})
  endif()

  if(PARSED_ARGS_LAZY_START)
    set(_bundle_lazy_start "true")
  else()
    set(_bundle_lazy_start "false")
  endif()

  if(PARSED_ARGS_RUN_LEVEL)
    set(_bundle_run_level ${PARSED_ARGS_RUN_LEVEL})
  endif()

  foreach(DEP ${PARSED_ARGS_DEPENDENCIES})
    string(FIND "${DEP}" ":" NEED_TO_CHECK_DEPS)
    if (NEED_TO_CHECK_DEPS)
      string(REPLACE ":" ";" LDEP ${DEP})
      list(GET LDEP 0 SYMBOLIC)
      list(GET LDEP 1 VER_INTERVAL)
    else()
      set(SYMBOLIC ${DEP})
      set(VER_INTERVAL "")
    endif()

    if (VER_INTERVAL)
      string(REPLACE "-" ";" VERS ${VER_INTERVAL})
      list(GET VERS 0 MINOR)
      list(GET VERS 1 MAJOR)
    else()
      set(MINOR "")
      set(MAJOR "")
    endif()

    if(MINOR AND MAJOR)
      set(VERSION_TAG "[${MINOR}, ${MAJOR})")
    elseif(MINOR AND NOT MAJOR)
      set(VERSION_TAG "${MINOR}")
    endif()

    if(SYMBOLIC AND VER_INTERVAL)
      set(_bundle_dependencies "${_bundle_dependencies}\n    <dependency>
        <symbolicName>${SYMBOLIC}</symbolicName>
        <version>${VERSION_TAG}</version>
    </dependency>")
    endif()
  endforeach()

  if(WIN32)
    set(WILD_PREF "\${64}")
    set(WILD_POST "")
    set(BASE_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
  elseif(APPLE)
    set(WILD_PREF ".*")
    set(WILD_POST "")
    set(BASE_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  else()
    set(WILD_PREF "")
    set(WILD_POST ".*")
    set(BASE_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  endif()

  set(FIST_SCODE false)
  set(SEP_SCODE "")
  if (NOT PARSED_ARGS_NO_CODES)
    foreach(LIB ${PARSED_ARGS_CODES})

      string(FIND "${LIB}" ":" NEED_TO_CHECK)
      if (NEED_TO_CHECK EQUAL -1)
        set(CODE ${LIB})
        set(CHECK_VER "NO_VERSION")
      else()
        string(REPLACE ":" ";" LDEP ${LIB})
        list(GET LDEP 0 CODE)
        list(GET LDEP 1 CHECK_VER)
      endif()

      set(_bundle_binary_files "${_bundle_binary_files}${SEP_SCODE} \n      ${BASE_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${CODE}${WILD_PREF}${CMAKE_SHARED_LIBRARY_SUFFIX}${WILD_POST}")
      if(NOT FIST_SCODE)
        set(SEP_SCODE ",\n")
        set(FIST_SCODE true)
      endif()
      set(_bundle_binary_files "${_bundle_binary_files}${SEP_SCODE}      ${BASE_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${CODE}d${WILD_PREF}${CMAKE_SHARED_LIBRARY_SUFFIX}${WILD_POST}")

      string(FIND "${CODE}" "Poco" POCO_LIBPRFIX_FOUND)

      string(COMPARE NOTEQUAL ${CHECK_VER} "HAS_VERSION" HAS_NOT_VERSION)
      if (POCO_LIBPRFIX_FOUND GREATER -1)
        set(HAS_NOT_VERSION false)
      endif ()

      if(HAS_NOT_VERSION)
        set(_bundle_binary_files "${_bundle_binary_files}${SEP_SCODE}      ${BASE_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${CODE}${CMAKE_SHARED_LIBRARY_SUFFIX}")
        set(_bundle_binary_files "${_bundle_binary_files}${SEP_SCODE}      ${BASE_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${CODE}d${CMAKE_SHARED_LIBRARY_SUFFIX}")
      endif()

    endforeach()
    set(_bundle_binary_files "${_bundle_binary_files}${SEP_SCODE}      bin/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}/*${CMAKE_SHARED_LIBRARY_SUFFIX}" )
  endif()

  set(FIST_SCODE false)
  set(SEP_SCODE "")
  foreach(FILE ${PARSED_ARGS_FILES})
    set(_bundle_files "${_bundle_files}${SEP_SCODE}  ${FILE}")
    if(NOT FIST_SCODE)
      set(SEP_SCODE ",\n")
      set(FIST_SCODE true)
    endif()
  endforeach()

  configure_file(${POCO_BASE}/OSP/cmake/PocoBundle.bndlspec.in ${PARSED_ARGS_OUT_BUNDLESPEC})

endfunction()