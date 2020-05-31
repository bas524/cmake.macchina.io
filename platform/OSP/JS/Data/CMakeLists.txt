add_definitions(-DV8_DEPRECATION_WARNINGS=1)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "OSP JavaScript Data Module"
        NAME com.appinf.osp.js.data
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        #LAZY_START
        DEPENDENCIES com.appinf.osp.js:1.0.0-2.0.0 poco.data:1.0.0-2.0.0
        RUN_LEVEL 600
        CODES PocoJSData
        FILES "bundle/*"
        OUT_BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/Data.bndlspec
)

POCO_MAKE_BUNDLE(NAME com.appinf.osp.js.data
                 BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/Data.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/DataModule.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::JSData
                   Poco::JSCore
                   Poco::OSPJS
                   Poco::OSP
                   Poco::Util
                   Poco::XML
                   Poco::Data
                   Poco::Foundation
                   js::libv8
                   js::libv8_libbase
                   js::libv8_libplatform
                 )