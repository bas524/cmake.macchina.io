include(CMakeFindDependencyMacro)
find_dependency(PocoFoundation)
find_dependency(PocoJSCore)
find_dependency(PocoUtil)
find_dependency(PocoXML)
find_dependency(PocoNet)
include("${CMAKE_CURRENT_LIST_DIR}/PocoJSNetTargets.cmake")
