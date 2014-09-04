#include "vertex_buffer.h"



vertex_buffer::vertex_buffer() {
    glGenBuffers( 1, &_vb );
}

vertex_buffer::~vertex_buffer() {
    if ( _vb ) {
        glDeleteBuffers( 1, &_vb );
    }
}

void vertex_buffer::bind( GLenum target_ ) {
    glBindBuffer( target_, _vb );
}

void vertex_buffer::bind( GLenum target_, GLuint index_ ) {
    glBindBufferBase( target_, index_, _vb );
}

void vertex_buffer::bind( GLenum target_, GLuint index_, GLintptr offset_, GLsizeiptr size_ ) {
    glBindBufferRange( target_, index_, _vb, offset_ , size_ );
}