add_definitions(-DV8_DEPRECATION_WARNINGS=1)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "OSP JavaScript Net Module"
        NAME com.appinf.osp.js.net
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        #LAZY_START
        DEPENDENCIES com.appinf.osp.js:1.0.0-2.0.0 poco.net:1.0.0-2.0.0
        RUN_LEVEL 600
        CODES PocoJSNet
        FILES "bundle/*"
        OUT_BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/Net.bndlspec
)

POCO_MAKE_BUNDLE(NAME com.appinf.osp.js.net
                 BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/Net.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/NetModule.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::JSNet
                   Poco::JSCore
                   Poco::OSPJS
                   Poco::OSP
                   Poco::Util
                   Poco::XML
                   Poco::Net
                   Poco::Foundation
                   js::libv8
                   js::libv8_libbase
                   js::libv8_libplatform
                 )