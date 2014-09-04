#pragma once

#include "opengl.h"

#include <glm.hpp>

class shader {
    GLuint      _program;

public:
    shader();
    ~shader();

    void set_code( int vertex_count_, const char** vertex_code_, int fragment_count_, const char** fragment__code_ );
    void use();

    int get_attribute_index( const char* name_ );
    int get_uniform_index( const char* name_ );
    int get_uniform_buffer_index( const char* name_ );
};

inline void set_uniform( int index_, int count_, const float* vec_ ) {
    glUniform1fv( index_, count_, vec_ );
}

inline void set_uniform( int index_, int count_, const glm::fvec2* vec_ ) {
    glUniform2fv( index_, count_, reinterpret_cast<const GLfloat*>( vec_ ) );
}

inline void set_uniform( int index_, int count_, const glm::fvec3* vec_ ) {
    glUniform3fv( index_, count_, reinterpret_cast<const GLfloat*>( vec_ ) );
}

inline void set_uniform( int index_, int count_, const glm::fvec4* vec_ ) {
    glUniform4fv( index_, count_, reinterpret_cast<const GLfloat*>( vec_ ) );
}

inline void set_uniform( int index_, int count_, const int* vec_ ) {
    glUniform1iv( index_, count_, vec_ );
}

inline void set_uniform( int index_, int count_, const glm::ivec2* vec_ ) {
    glUniform2iv( index_, count_, reinterpret_cast<const GLint*>( vec_ ) );
}

inline void set_uniform( int index_, int count_, const glm::ivec3* vec_ ) {
    glUniform3iv( index_, count_, reinterpret_cast<const GLint*>( vec_ ) );
}

inline void set_uniform( int index_, int count_, const glm::ivec4* vec_ ) {
    glUniform4iv( index_, count_, reinterpret_cast<const GLint*>( vec_ ) );
}

inline void set_uniform( int index_, int count_, glm::mat2* mat_, bool transpose_ = false ) {
    glUniformMatrix2fv( index_, count_, transpose_, reinterpret_cast<const GLfloat*>( mat_ ) );
}

inline void set_uniform( int index_, int count_, glm::mat3* mat_, bool transpose_ = false ) {
    glUniformMatrix3fv( index_, count_, transpose_, reinterpret_cast<const GLfloat*>( mat_ ) );
}

inline void set_uniform( int index_, int count_, glm::mat4* mat_, bool transpose_ = false ) {
    glUniformMatrix4fv( index_, count_, transpose_, reinterpret_cast<const GLfloat*>( mat_ ) );
}

