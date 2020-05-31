set(POCO_EXENAME "RemoteGenNG")

# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO(SRCS ${SRCS_G})

add_executable(RemoteGenNG ${SRCS})
set_target_properties(RemoteGenNG
	PROPERTIES
	OUTPUT_NAME RemoteGenNG
)

add_custom_command(TARGET RemoteGenNG
									 POST_BUILD
									 COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/RemoteGenNG.xml ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
									 )

target_link_libraries(RemoteGenNG PUBLIC Poco::RemotingNG Poco::CodeGeneration Poco::Net Poco::Util Poco::CppParser Poco::XML Poco::JSON Poco::Foundation)

install(
	TARGETS RemoteGenNG EXPORT RemoteGenNGTargets
	LIBRARY DESTINATION lib${LIB_SUFFIX}
	ARCHIVE DESTINATION lib${LIB_SUFFIX}
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)

install(
	FILES ${CMAKE_CURRENT_LIST_DIR}/RemoteGenNG.xml
	DESTINATION bin
)
