set(POCO_EXENAME "BridgeClientApp")
set(SRCS "")

# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO(SRCS ${SRCS_G})

add_executable(BridgeClientApp ${SRCS})
set_target_properties(BridgeClientApp
                      PROPERTIES
                      OUTPUT_NAME rosclient
                      )

add_custom_command(TARGET BridgeClientApp
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/rosclient.properties ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                   )

target_link_libraries(BridgeClientApp PUBLIC Poco::OSPIoTROS Poco::Net Poco::Util Poco::JSON Poco::XML Poco::Foundation)

install(
        TARGETS BridgeClientApp EXPORT BridgeClientAppTargets
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

# fixme : need to use macchina.properties.install
install(
        FILES ${CMAKE_CURRENT_LIST_DIR}/rosclient.properties
        DESTINATION bin
)