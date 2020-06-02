set(PROJECT_BUNDLE io.macchina.webui.gpio)
set(PROJECT_BUNDLE_SPEC ${CMAKE_CURRENT_LIST_DIR}/GPIO.bndlspec)

POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "macchina.io GPIO Web Interface"
        NAME ${PROJECT_BUNDLE}
        VERSION 1.0.0
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        #LAZY_START
        RUN_LEVEL 900
        FILES bundle/*
        NO_CODES
        OUT_BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
)

POCO_MAKE_BUNDLE(NAME ${PROJECT_BUNDLE}
                 BUNDLESPEC ${PROJECT_BUNDLE_SPEC}
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 PLATFORM_INDEPENDENT
                 )