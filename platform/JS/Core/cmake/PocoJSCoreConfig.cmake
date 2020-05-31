include(CMakeFindDependencyMacro)
find_dependency(PocoFoundation)
find_dependency(PocoUtil)
find_dependency(PocoJSON)
find_dependency(PocoXML)

find_dependency(libv8)
find_dependency(libv8_libbase)
find_dependency(libv8_libplatform)

include("${CMAKE_CURRENT_LIST_DIR}/PocoJSCoreTargets.cmake")
