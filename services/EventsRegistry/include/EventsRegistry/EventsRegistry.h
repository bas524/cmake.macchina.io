#ifndef EventsRegistry_EventsRegistry_INCLUDED
#define EventsRegistry_EventsRegistry_INCLUDED

#include <Poco/Poco.h>

//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the OSPNetEnv_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTMobileConnection_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
#if defined(EventsRegistry_EXPORTS)
#define EventsRegistry_API __declspec(dllexport)
#else
#define EventsRegistry_API __declspec(dllimport)
#endif
#endif


#if !defined(EventsRegistry_API)
#define EventsRegistry_API
#endif


//
// Automatically link IoTMobileConnection library.
//
#if defined(_MSC_VER)
#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(EventsRegistry_EXPORTS)
#pragma comment(lib, "EventsRegistry" POCO_LIB_SUFFIX)
#endif
#endif


#endif  //  EventsRegistry_EventsRegistryImport_INCLUDED
