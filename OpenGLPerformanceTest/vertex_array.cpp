#include "vertex_array.h"



vertex_array::vertex_array() {
    glGenVertexArrays( 1, &_va );
}


vertex_array::~vertex_array() {
    if ( _va ) {
        glDeleteVertexArrays( 1, &_va );
    }
}

void vertex_array::bind() {
    glBindVertexArray( _va );
}
