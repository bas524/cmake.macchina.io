set(POCO_EXENAME "PageCompiler")

# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO(SRCS ${SRCS_G})

add_executable(PageCompiler ${SRCS})
set_target_properties(PageCompiler
	PROPERTIES
	OUTPUT_NAME cpspc
)

add_custom_command(TARGET PageCompiler
									 POST_BUILD
									 COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/cpspc.properties ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
									 )

target_link_libraries(PageCompiler PUBLIC Poco::Net Poco::Util)

install(
	TARGETS PageCompiler EXPORT PageCompilerTargets
	LIBRARY DESTINATION lib${LIB_SUFFIX}
	ARCHIVE DESTINATION lib${LIB_SUFFIX}
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)

install(
				FILES ${CMAKE_CURRENT_LIST_DIR}/cpspc.properties
				DESTINATION bin
)