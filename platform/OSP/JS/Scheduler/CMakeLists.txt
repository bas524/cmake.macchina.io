add_definitions(-DV8_DEPRECATION_WARNINGS=1)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "OSP JavaScript Task Scheduler"
        NAME com.appinf.osp.js.scheduler
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        #LAZY_START
        ACTIVATOR Poco::OSP::JS::Scheduler::BundleActivator
        DEPENDENCIES com.appinf.osp.js:1.0.0-2.0.0
        RUN_LEVEL 600
        OUT_BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/Scheduler.bndlspec
)

POCO_MAKE_BUNDLE(NAME com.appinf.osp.js.scheduler
                 BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/Scheduler.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/BundleActivator.cpp src/SchedulerExtensionPoint.cpp
                 HEADERS src/SchedulerExtensionPoint.h
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES
                   Poco::JSNet
                   Poco::JSData
                   Poco::JSBridge
                   Poco::JSCore
                   Poco::OSPJS
                   Poco::OSP
                   Poco::RemotingNG
                   Poco::Net
                   Poco::Util
                   Poco::XML
                   Poco::Data
                   Poco::Foundation
                   js::libv8
                   js::libv8_libbase
                   js::libv8_libplatform
                 )