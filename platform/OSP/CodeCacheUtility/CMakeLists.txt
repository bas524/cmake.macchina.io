set(POCO_EXENAME "CodeCacheUtility")

# Sources
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO(SRCS ${SRCS_G})

add_executable(CodeCacheUtility ${SRCS})
add_executable(Bundle::CodeCacheUtility ALIAS CodeCacheUtility)
set_target_properties(CodeCacheUtility
                      PROPERTIES
                      VERSION 1
                      OUTPUT_NAME ccutil
                      )

target_link_libraries(CodeCacheUtility PUBLIC Poco::OSP Poco::Zip Poco::Util Poco::XML Poco::JSON Poco::Foundation)

install(
        TARGETS CodeCacheUtility EXPORT CodeCacheUtilityTargets
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)