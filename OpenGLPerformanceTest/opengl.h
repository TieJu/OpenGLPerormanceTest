#pragma once

#include <SDL.h>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <gl/GL.h>
#include "glext.h"

extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLUNIFORM1FVPROC glUniform1fv;
extern PFNGLUNIFORM2FVPROC glUniform2fv;
extern PFNGLUNIFORM3FVPROC glUniform3fv;
extern PFNGLUNIFORM4FVPROC glUniform4fv;
extern PFNGLUNIFORM1IVPROC glUniform1iv;
extern PFNGLUNIFORM2IVPROC glUniform2iv;
extern PFNGLUNIFORM3IVPROC glUniform3iv;
extern PFNGLUNIFORM4IVPROC glUniform4iv;
extern PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;

extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;

extern PFNGLBINDBUFFERPROC  glBindBuffer;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
extern PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData;
extern PFNGLMAPBUFFERPROC glMapBuffer;
extern PFNGLUNMAPBUFFERPROC glUnmapBuffer;
extern PFNGLBINDBUFFERRANGEPROC glBindBufferRange;
extern PFNGLBINDBUFFERBASEPROC glBindBufferBase;
extern PFNGLBUFFERSTORAGEPROC glBufferStorage;
extern PFNGLMAPBUFFERRANGEPROC glMapBufferRange;
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange;

class opengl {
    SDL_Window*     _wnd{ nullptr };
    SDL_GLContext   _ctx{ nullptr };

public:
    opengl();
    ~opengl();

    void swap();
};

