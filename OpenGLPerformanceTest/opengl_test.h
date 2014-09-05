#pragma once

#include "shader.h"
#include "vertex_buffer.h"
#include "vertex_array.h"

#include <iterator>
#include <vector>
#include <memory>
#include <tuple>

#define NUMBER_OF_OBJECTS   1024 * 4

struct shared_state {
    vertex_buffer   _geometry;
    int             _vertices_per_object;
};

std::shared_ptr<shared_state> get_shared_state();

template<typename Derived>
class opengl_test {
protected:
    std::shared_ptr<shared_state>   _shared_state;
    vertex_array                    _geometry_bindings;
    shader                          _shader;

    void draw_object( int index_ ) {
        static_cast<Derived*>( this )->pre_draw( index_ );

        glDrawArrays( GL_TRIANGLES, index_ * _shared_state->_vertices_per_object, _shared_state->_vertices_per_object );

        static_cast<Derived*>( this )->post_draw( index_ );
    }

public:
    opengl_test() {
        _shared_state = get_shared_state();

        static_cast<Derived*>( this )->pre_init();

        _geometry_bindings.bind();
        _shared_state->_geometry.bind( GL_ARRAY_BUFFER );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( _shader.get_attribute_index( "in_xyzw" ), 2, GL_FLOAT, GL_FALSE, sizeof( float ) * 2, nullptr );

        static_cast<Derived*>( this )->post_init();
    }

    ~opengl_test() {
    }

    void bind() {
        static_cast<Derived*>( this )->pre_bind();

        _shader.use();
        _geometry_bindings.bind();

        static_cast<Derived*>( this )->post_bind();
    }

    void run() {
        static_cast<Derived*>( this )->pre_run();

        for ( int i = 0; i < NUMBER_OF_OBJECTS; ++i ) {
            draw_object( i );
        }

        static_cast<Derived*>( this )->post_run();
    }
};

