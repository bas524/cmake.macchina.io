//
// Geo.h
//
// Library: Geo
// Package: Geo
// Module:  Geo
//
// Basic definitions for the Poco Geo library.
// This file must be the first file included by every other Geo
// header file.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Geo_Geo_INCLUDED
#define Geo_Geo_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the Geo_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// Geo_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(Geo_EXPORTS)
		#define Geo_API __declspec(dllexport)
	#else
		#define Geo_API __declspec(dllimport)
	#endif
#endif


#if !defined(Geo_API)
	#define Geo_API
#endif


//
// Automatically link Geo library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(Geo_EXPORTS)
		#pragma comment(lib, "PocoGeo" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // Geo_Geo_INCLUDED
