POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "POCO Data Library"
        NAME poco.data
        VERSION 1.10.1
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR DataBundleActivator
        #LAZY_START
        RUN_LEVEL 000
        CODES PocoData
        OUT_BUNDLESPEC ${CMAKE_CURRENT_BINARY_DIR}/Data.bndlspec
)

POCO_MAKE_BUNDLE(NAME poco.data
                 BUNDLESPEC ${CMAKE_CURRENT_BINARY_DIR}/Data.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/DataBundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES Poco::OSP Poco::Data Poco::Util Poco::XML Poco::Foundation)

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/SQLite)
  add_subdirectory(SQLite)
endif()

if(POSTGRESQL_FOUND AND ENABLE_DATA_POSTGRESQL)
  message(STATUS "PostgreSQL Bundle Support Enabled")
  add_subdirectory(PostgreSQL)
else()
  message(STATUS "PostgreSQL Bundle Support Disabled")
endif()
