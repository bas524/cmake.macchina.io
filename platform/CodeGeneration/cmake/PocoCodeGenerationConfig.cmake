include(CMakeFindDependencyMacro)
find_dependency(PocoFoundation)
find_dependency(CppParser)
include("${CMAKE_CURRENT_LIST_DIR}/PocoCodeGenerationTargets.cmake")
