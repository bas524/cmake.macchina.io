POCO_GENERATE_BUNDLESPEC(
        DESCRIPTION "POCO Crypto Library (OpenSSL)"
        NAME poco.crypto
        VERSION 1.10.1
        VENDOR "Applied Informatics"
        COPYRIGHT "(c) 2007-2020, Applied Informatics Software Engineering GmbH"
        ACTIVATOR CryptoBundleActivator
        #LAZY_START
        RUN_LEVEL 000
        CODES PocoCrypto
        OUT_BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/Crypto.bndlspec
)

POCO_MAKE_BUNDLE(NAME poco.crypto
                 BUNDLESPEC ${CMAKE_CURRENT_LIST_DIR}/Crypto.bndlspec
                 BUNDLES_DIR ${BUNDLES_OUTPUT_DIR}
                 SOURCES src/CryptoBundleActivator.cpp
                 INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include
                 DEPENDENCIES Poco::Crypto Poco::OSP Poco::Util Poco::XML Poco::Foundation)

