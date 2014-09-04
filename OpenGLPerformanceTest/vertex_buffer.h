#pragma once

#include "opengl.h"

class vertex_buffer {
    GLuint      _vb;

public:
    vertex_buffer();
    ~vertex_buffer();

    void bind( GLenum target_ );
    void bind( GLenum target_, GLuint index_ );
    void bind( GLenum target_, GLuint index_, GLintptr offset_, GLsizeiptr size_ );
};

