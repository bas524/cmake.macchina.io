include(CMakeFindDependencyMacro)
find_dependency(PocoFoundation)
find_dependency(PocoJSCore)
find_dependency(PocoRemotingNG)
find_dependency(PocoUtil)
find_dependency(PocoXML)
include("${CMAKE_CURRENT_LIST_DIR}/PocoJSBridgeTargets.cmake")
