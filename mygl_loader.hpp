#pragma once

#ifdef _GL_H_  // system <GL/gl.h> on Windows defines this
#error "Do not include <GL/gl.h>. Include mygl_loader first"
#endif

#define APIENTRY __stdcall

struct myGLversionStruct{
    int major;
    int minor;
};

typedef void* (*MYGLloadproc)(const char* name);

#define GLAPI extern

GLAPI struct myGLversionStruct GLVersion;

GLAPI int gladLoadGL(void);
GLAPI int gladLoadGLLoader(MYGLloadproc);

#include <cstdint>

using GLint = std::int32_t;
using GLuint = std::uint32_t;
using GLfloat = float;
using GLdouble = double;
using GLboolean = std::uint8_t;
using GLsizeiptr = std::intptr_t;
using GLchar = char;

using GLenum = std::uint32_t;
using GLbitfield = std::uint32_t;
using GLbyte = std::int8_t;
using GLshort = std::int16_t;
using GLsizei = std::int32_t;
using GLubyte = std::uint8_t;
using GLushort = std::uint16_t;
using GLulong = std::uint32_t;
using GLintptr = std::intptr_t;
using GLclampf = float;
using GLclampd = double;

using PFNGLGENBUFFERSPROC = void (*)(GLsizei n, GLuint* buffers);
using PFNGLBINDBUFFERPROC = void (*)(GLenum target, GLuint buffer);
using PFNGLBUFFERDATAPROC = void (*)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
using PFNGLDELETEBUFFERSPROC = void (*)(GLsizei n, const GLuint* buffers);

inline PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
inline PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
inline PFNGLBUFFERDATAPROC glBufferData = nullptr;
inline PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
// To do : Add more OpenGL function declarations here as needed