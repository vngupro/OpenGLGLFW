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

// Vertex Array Objects
using PFNGLGENVERTEXARRAYSPROC = void (*)(GLsizei n, GLuint* arrays);
using PFNGLBINDVERTEXARRAYPROC = void (*)(GLuint array);
using PFNGLDELETEVERTEXARRAYSPROC = void (*)(GLsizei n, const GLuint* arrays);

inline PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
inline PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
inline PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = nullptr;


// Vertex Attributes
using PFNGLENABLEVERTEXATTRIBARRAYPROC = void (*)(GLuint index);
using PFNGLVERTEXATTRIBPOINTERPROC = void (*)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
using PFNGLDISABLEVERTEXATTRIBARRAYPROC = void (*)(GLuint index);

inline PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
inline PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
inline PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;


// Shaders
using PFNGLCREATESHADERPROC = GLuint(*)(GLenum type);
using PFNGLSHADERSOURCEPROC = void (*)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
using PFNGLCOMPILESHADERPROC = void (*)(GLuint shader);
using PFNGLGETSHADERIVPROC = void (*)(GLuint shader, GLenum pname, GLint* params);
using PFNGLGETSHADERINFOLOGPROC = void (*)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
using PFNGLDELETESHADERPROC = void (*)(GLuint shader);

inline PFNGLCREATESHADERPROC glCreateShader = nullptr;
inline PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
inline PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
inline PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
inline PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
inline PFNGLDELETESHADERPROC glDeleteShader = nullptr;


// Shader Program
using PFNGLCREATEPROGRAMPROC = GLuint(*)();
using PFNGLATTACHSHADERPROC = void (*)(GLuint program, GLuint shader);
using PFNGLLINKPROGRAMPROC = void (*)(GLuint program);
using PFNGLUSEPROGRAMPROC = void (*)(GLuint program);
using PFNGLGETPROGRAMIVPROC = void (*)(GLuint program, GLenum pname, GLint* params);
using PFNGLGETPROGRAMINFOLOGPROC = void (*)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
using PFNGLDELETEPROGRAMPROC = void (*)(GLuint program);

inline PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
inline PFNGLATTACHSHADERPROC glAttachShader = nullptr;
inline PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
inline PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
inline PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
inline PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
inline PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;


// Uniforms
using PFNGLGETUNIFORMLOCATIONPROC = GLint(*)(GLuint program, const GLchar* name);
using PFNGLUNIFORM1IPROC = void (*)(GLint location, GLint v0);
using PFNGLUNIFORM1FPROC = void (*)(GLint location, GLfloat v0);
using PFNGLUNIFORMMATRIX4FVPROC = void (*)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

inline PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
inline PFNGLUNIFORM1IPROC glUniform1i = nullptr;
inline PFNGLUNIFORM1FPROC glUniform1f = nullptr;
inline PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;


// Textures
using PFNGLGENTEXTURESPROC = void (*)(GLsizei n, GLuint* textures);
using PFNGLBINDTEXTUREPROC = void (*)(GLenum target, GLuint texture);
using PFNGLTEXPARAMETERIPROC = void (*)(GLenum target, GLenum pname, GLint param);
using PFNGLTEXIMAGE2DPROC = void (*)(GLenum target, GLint level, GLint internalFormat,
    GLsizei width, GLsizei height, GLint border,
    GLenum format, GLenum type, const void* data);
using PFNGLDELETETEXTURESPROC = void (*)(GLsizei n, const GLuint* textures);

inline PFNGLGENTEXTURESPROC glGenTextures = nullptr;
inline PFNGLBINDTEXTUREPROC glBindTexture = nullptr;
inline PFNGLTEXPARAMETERIPROC glTexParameteri = nullptr;
inline PFNGLTEXIMAGE2DPROC glTexImage2D = nullptr;
inline PFNGLDELETETEXTURESPROC glDeleteTextures = nullptr;
// To do : Add more OpenGL function declarations here as needed