set(POCO_EXENAME "MacchinaServer")
set(SRCS "")

# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO(SRCS ${SRCS_G})

add_executable(MacchinaServer ${SRCS})
set_target_properties(MacchinaServer
                      PROPERTIES
                      OUTPUT_NAME macchina
                      )

add_custom_command(TARGET MacchinaServer
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/macchina.properties ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/macchina.pem ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/rootcert.pem ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                   )

target_link_libraries(MacchinaServer PUBLIC Poco::OSP Poco::Zip Poco::Util Poco::JSON Poco::XML Poco::Foundation)

install(
        TARGETS MacchinaServer EXPORT MacchinaServerTargets
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

# fixme : need to use macchina.properties.install
install(
        FILES ${CMAKE_CURRENT_LIST_DIR}/macchina.properties
        DESTINATION bin
)