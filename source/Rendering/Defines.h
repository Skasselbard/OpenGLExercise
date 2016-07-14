#pragma once

//API
#ifndef RENDERING_API
  #ifdef __PRECOMPILED_H__
#define RENDERING_API __declspec(dllexport)
  #else
#define RENDERING_API __declspec(dllimport)
  #endif
#endif

#define GLUTILS_API //empty api
#define UTILS_API //empty api

//#define USELEAKDETECTION
#ifdef USELEAKDETECTION
#if defined (DEBUG) || defined(_DEBUG)
#include <vld.h>  //memory leak detection
#endif
#endif

#ifndef RtlZeroMemory
#include <memory.h>
#define RtlZeroMemory(Destination,Length) memset((Destination),0,(Length))
#endif

#ifndef ZeroMemory
#define ZeroMemory RtlZeroMemory
#endif

//windows typedef
typedef unsigned long DWORD, *PDWORD, *LPDWORD; 
