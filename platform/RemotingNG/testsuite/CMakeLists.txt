# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO(TEST_SRCS ${SRCS_G})

# Headers
file(GLOB_RECURSE HDRS_G "src/*.h")
POCO_HEADERS_AUTO(TEST_SRCS ${HDRS_G})

POCO_SOURCES_AUTO_PLAT(TEST_SRCS OFF
                       src/WinDriver.cpp
                       )

add_executable(RemotingNG-testrunner ${TEST_SRCS})
if (ANDROID)
  add_test(
          NAME RemotingNG
          WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
          COMMAND ${CMAKE_COMMAND} -DANDROID_NDK=${ANDROID_NDK} -DLIBRARY_DIR=${CMAKE_BINARY_DIR}/lib -DUNITTEST=${CMAKE_BINARY_DIR}/bin/RemotingNG-testrunner -DTEST_PARAMETER=-all -P ${CMAKE_SOURCE_DIR}/cmake/ExecuteOnAndroid.cmake
  )
else ()
  add_test(
          NAME RemotingNG
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMAND RemotingNG-testrunner -ignore ${CMAKE_SOURCE_DIR}/cppignore.lnx -all
  )
  if (NOT POCO_BASE)
    set(POCO_BASE ${CMAKE_SOURCE_DIR})
  endif ()
  set_tests_properties(RemotingNG PROPERTIES ENVIRONMENT POCO_BASE=${POCO_BASE})
endif ()
target_link_libraries(RemotingNG-testrunner PUBLIC Poco::RemotingNG Poco::Util Poco::XML Poco::CppUnit)
