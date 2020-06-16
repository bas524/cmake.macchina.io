set(OPENSSL_PDK_DIR "${DELIVERY_ROOT}")

list(APPEND CMAKE_FIND_ROOT_PATH ${OPENSSL_PDK_DIR})
list(APPEND CMAKE_FIND_ROOT_PATH ${OPENSSL_PDK_DIR}/include)
list(APPEND CMAKE_FIND_ROOT_PATH ${OPENSSL_PDK_DIR}/lib)

find_path(OPENSSL_PDK_INCLUDE_DIRS
          NAMES openssl/ssl.h
          PATHS ${OPENSSL_PDK_DIR}/include
          )

if(WIN32)
  set(LIBRARY_PREFIX "lib")
endif()

find_library(OPENSSL_PDK_LIBRARY_CRYPTO_STATIC
        crypto
        ${LIBRARY_PREFIX}crypto
        PATHS
        ${OPENSSL_PDK_DIR}/lib
        )

find_library(OPENSSL_PDK_LIBRARY_SSL_STATIC
        ssl
        ${LIBRARY_PREFIX}ssl
        PATHS
        ${OPENSSL_PDK_DIR}/lib
        )

set(OPENSSL_PDK_LIBRARIES
        ${OPENSSL_PDK_LIBRARY_CRYPTO_STATIC}
        ${OPENSSL_PDK_LIBRARY_SSL_STATIC})

message(STATUS "OPENSSL_PDK_LIBRARIES: ")
foreach(OPENSSL_PDK_LIBRARY ${OPENSSL_PDK_LIBRARIES})
  message(STATUS "openssl_pdk + ${OPENSSL_PDK_LIBRARY}")
endforeach()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OpenSSL_PDK DEFAULT_MSG OPENSSL_PDK_INCLUDE_DIRS
                                  OPENSSL_PDK_LIBRARY_CRYPTO_STATIC
                                  OPENSSL_PDK_LIBRARY_SSL_STATIC)

mark_as_advanced(OPENSSL_PDK_INCLUDE_DIRS OPENSSL_PDK_LIBRARIES)

if(OPENSSL_PDK_FOUND)
  if(NOT TARGET openssl_pdk::crypto_static)
    add_library(openssl_pdk::crypto_static UNKNOWN IMPORTED)
    set_target_properties(openssl_pdk::crypto_static PROPERTIES
                          IMPORTED_LOCATION "${OPENSSL_PDK_LIBRARY_CRYPTO_STATIC}"
                          INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_PDK_INCLUDE_DIRS}")
    if(WIN32)
      target_link_libraries(openssl_pdk::crypto_static INTERFACE ws2_32)

      if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        target_link_options(openssl_pdk::crypto_static INTERFACE "/NODEFAULTLIB:libcmtd.lib")
      else()
        target_link_options(openssl_pdk::crypto_static INTERFACE "/NODEFAULTLIB:libcmt.lib")
      endif()
    endif()
  endif()
  if(NOT TARGET openssl_pdk::ssl_static)
    add_library(openssl_pdk::ssl_static UNKNOWN IMPORTED)
    set_target_properties(openssl_pdk::ssl_static PROPERTIES
                          IMPORTED_LOCATION "${OPENSSL_PDK_LIBRARY_SSL_STATIC}"
                          INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_PDK_INCLUDE_DIRS}")
    if(WIN32)
      target_link_libraries(openssl_pdk::ssl_static INTERFACE ws2_32)

      if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        target_link_options(openssl_pdk::ssl_static INTERFACE "/NODEFAULTLIB:libcmtd.lib")
      else()
        target_link_options(openssl_pdk::ssl_static INTERFACE "/NODEFAULTLIB:libcmt.lib")
      endif()
    endif()
  endif()
endif()
