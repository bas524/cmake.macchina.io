add_definitions(-DV8_DEPRECATION_WARNINGS=1)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "Remoting NG TCP Transport"
        NAME com.appinf.osp.remotingng.tcp
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        #LAZY_START
        ACTIVATOR Poco::OSP::RemotingNG::TCP::BundleActivator
        DEPENDENCIES poco.net:1.0.0-2.0.0
        RUN_LEVEL 000
        CODES PocoRemotingNGTCP
        OUT_BUNDLESPEC ${CMAKE_CURRENT_BINARY_DIR}/TCP.bndlspec
)

POCO_MAKE_BUNDLE(NAME com.appinf.osp.remotingng.tcp
                 BUNDLESPEC ${CMAKE_CURRENT_BINARY_DIR}/TCP.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/BundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::RemotingNGTCP
                   Poco::RemotingNG
                   Poco::OSP
                   Poco::Net
                   Poco::Util
                   Poco::XML
                   Poco::JSON
                   Poco::Foundation
                 )