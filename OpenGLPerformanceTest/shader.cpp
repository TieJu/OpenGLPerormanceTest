#include "shader.h"



shader::shader() {
    _program = glCreateProgram();
}


shader::~shader() {
    if ( _program ) {
        glDeleteProgram( _program );
    }
}

void shader::set_code( int vertex_count_, const char** vertex_code_, int fragment_count_, const char** fragment__code_ ) {
    auto vs = glCreateShader( GL_VERTEX_SHADER );
    auto fs = glCreateShader( GL_FRAGMENT_SHADER );

    glShaderSource( vs, vertex_count_, vertex_code_, nullptr );
    glShaderSource( fs, fragment_count_, fragment__code_, nullptr );

    glCompileShader( vs );
    glCompileShader( fs );

    glAttachShader( _program, vs );
    glAttachShader( _program, fs );

    glLinkProgram( _program );

    glDetachShader( _program, fs );
    glDetachShader( _program, vs );

    glDeleteShader( fs );
    glDeleteShader( vs );
}

void shader::use() {
    glUseProgram( _program );
}

int shader::get_attribute_index( const char* name_ ) {
    return glGetAttribLocation( _program, name_ );
}

int shader::get_uniform_index( const char* name_ ) {
    return glGetUniformLocation( _program, name_ );
}

int shader::get_uniform_buffer_index( const char* name_ ) {
    return glGetUniformBlockIndex( _program, name_ );
}