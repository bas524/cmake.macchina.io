include(CMakeFindDependencyMacro)
find_dependency(PocoFoundation)
find_dependency(PocoData)
if(@POCO_UNBUNDLED@)
    if(CMAKE_VERSION VERSION_LESS "3.14")
        list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/V313")
    endif()
    find_dependency(SQLite3 REQUIRED)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/PocoDataSQLiteTargets.cmake")
