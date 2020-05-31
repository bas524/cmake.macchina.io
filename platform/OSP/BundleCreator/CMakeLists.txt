set(POCO_EXENAME "BundleCreator")

# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO(SRCS ${SRCS_G})

add_executable(BundleCreator ${SRCS})
add_executable(Bundle::Creator ALIAS BundleCreator)
set_target_properties(BundleCreator
                      PROPERTIES
                      VERSION 1
                      OUTPUT_NAME bundle
                      )

target_link_libraries(BundleCreator PUBLIC Poco::Foundation Poco::JSON Poco::XML Poco::Util Poco::OSP Poco::Zip)

install(
        TARGETS BundleCreator EXPORT BundleCreatorTargets
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)