#pragma once

#ifdef __gl_h_
#error OpenGL header already included, remove this include, glad already provides it
#endif
#define __gl_h_

#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#define APIENTRY __stdcall
#endif

#ifndef APIENTRY
#define APIENTRY
#endif

#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#ifndef MYGLAPIENTRY
#define MYGLAPIENTRY APIENTRY
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct gladGLversionStruct {
    int major;
    int minor;
};

typedef void* (*MYGLloadproc)(const char* name);

#ifndef GLAPI
#   if defined(MYGL_GLAPI_EXPORT)
#       if defined(_WIN32) || defined(__CYWIN__)
#           if defined(MYGL_GLAPI_EXPORT_BUILD)
#               if defined (__GNUC__)
#                   define GLAPI __attribute__((dllexport)) extern
#               else
#                   define GLAPI __declspec(dllexport) extern
#               endif
#           else
#               if defined (__GNUC__)
#                   define GLAPI __attribute__((dllimport)) extern
#               else
#                   define GLAPI __declspec(dllimport) extern
#               endif
#           endif
#       elif defined(__GNUC__) && defined(MYGL_GLAPI_EXPORT_BUILD)
#           define GLAPI __attribute__((visibility("default"))) extern
#       else
#           define GLAPI extern
#       endif
#   endif
#endif

#ifdef __cplusplus
}
#endif