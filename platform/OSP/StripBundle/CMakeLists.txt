set(POCO_EXENAME "StripBundle")
set(SRCS "")

# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO(SRCS ${SRCS_G})

add_executable(StripBundle ${SRCS})
add_executable(Bundle::Strip ALIAS StripBundle)
set_target_properties(StripBundle
                      PROPERTIES
                      VERSION 1
                      OUTPUT_NAME strip-bundle
                      )

target_link_libraries(StripBundle PUBLIC Poco::Zip Poco::Util Poco::XML Poco::JSON Poco::Foundation Poco::OSP)

install(
        TARGETS StripBundle EXPORT StripBundleTargets
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)