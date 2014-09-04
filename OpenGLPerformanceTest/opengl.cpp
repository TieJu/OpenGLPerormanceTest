#include "opengl.h"

PFNGLATTACHSHADERPROC glAttachShader;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLUNIFORM1FVPROC glUniform1fv;
PFNGLUNIFORM2FVPROC glUniform2fv;
PFNGLUNIFORM3FVPROC glUniform3fv;
PFNGLUNIFORM4FVPROC glUniform4fv;
PFNGLUNIFORM1IVPROC glUniform1iv;
PFNGLUNIFORM2IVPROC glUniform2iv;
PFNGLUNIFORM3IVPROC glUniform3iv;
PFNGLUNIFORM4IVPROC glUniform4iv;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;

PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;

PFNGLBINDBUFFERPROC  glBindBuffer;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLBUFFERSUBDATAPROC glBufferSubData;
PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData;
PFNGLMAPBUFFERPROC glMapBuffer;
PFNGLUNMAPBUFFERPROC glUnmapBuffer;
PFNGLBINDBUFFERRANGEPROC glBindBufferRange;
PFNGLBINDBUFFERBASEPROC glBindBufferBase;
PFNGLBUFFERSTORAGEPROC glBufferStorage;
PFNGLMAPBUFFERRANGEPROC glMapBufferRange;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange;

#define LoadEntry(name_) name_ = reinterpret_cast<decltype(name_)>( SDL_GL_GetProcAddress(#name_) )

opengl::opengl() {
    SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, SDL_TRUE );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_STEREO, SDL_FALSE );
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, SDL_TRUE );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 5 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, /*SDL_GL_CONTEXT_PROFILE_CORE*/SDL_GL_CONTEXT_PROFILE_COMPATIBILITY );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG );

    _wnd = SDL_CreateWindow( "OpenGL Performance Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    _ctx = SDL_GL_CreateContext( _wnd );

    LoadEntry( glAttachShader );
    LoadEntry( glCompileShader );
    LoadEntry( glCreateProgram );
    LoadEntry( glCreateShader );
    LoadEntry( glDeleteProgram );
    LoadEntry( glDeleteShader );
    LoadEntry( glDetachShader );
    LoadEntry( glLinkProgram );
    LoadEntry( glShaderSource );
    LoadEntry( glUseProgram );
    LoadEntry( glGetAttribLocation );
    LoadEntry( glGetUniformLocation );
    LoadEntry( glVertexAttribPointer );
    LoadEntry( glUniform1fv );
    LoadEntry( glUniform2fv );
    LoadEntry( glUniform3fv );
    LoadEntry( glUniform4fv );
    LoadEntry( glUniform1iv );
    LoadEntry( glUniform2iv );
    LoadEntry( glUniform3iv );
    LoadEntry( glUniform4iv );
    LoadEntry( glUniformMatrix2fv );
    LoadEntry( glUniformMatrix3fv );
    LoadEntry( glUniformMatrix4fv );
    LoadEntry( glEnableVertexAttribArray );
    LoadEntry( glGetUniformBlockIndex );
    
    LoadEntry( glBindVertexArray );
    LoadEntry( glDeleteVertexArrays );
    LoadEntry( glGenVertexArrays );
    
    LoadEntry( glBindBuffer );
    LoadEntry( glDeleteBuffers );
    LoadEntry( glGenBuffers );
    LoadEntry( glBufferData );
    LoadEntry( glBufferSubData );
    LoadEntry( glGetBufferSubData );
    LoadEntry( glMapBuffer );
    LoadEntry( glUnmapBuffer );
    LoadEntry( glBindBufferRange );
    LoadEntry( glBindBufferBase );
    LoadEntry( glBufferStorage );
    LoadEntry( glMapBufferRange );
    LoadEntry( glFlushMappedBufferRange );
}

#undef LoadEntry

opengl::~opengl() {
    if ( _ctx ) {
        SDL_GL_MakeCurrent( _wnd, nullptr );
        SDL_GL_DeleteContext( _ctx );
    }
    if ( _wnd ) {
        SDL_DestroyWindow( _wnd );
    }
}

void opengl::swap() {
    SDL_GL_SwapWindow( _wnd );
}
