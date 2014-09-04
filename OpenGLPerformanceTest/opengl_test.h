#pragma once

#include "shader.h"
#include "vertex_buffer.h"
#include "vertex_array.h"

#include <iterator>
#include <vector>

#define NUMBER_OF_OBJECTS   1024 * 8

template<typename Derived>
class opengl_test {
protected:
    shader                              _shader;
    vertex_buffer                       _geometry;
    vertex_array                        _geometry_bindings;
    int                                 _vertices_per_object;

    void draw_object( int index_ ) {
        static_cast<Derived*>( this )->pre_draw( index_ );

        glDrawArrays( GL_TRIANGLES, index_ * _vertices_per_object, _vertices_per_object );

        static_cast<Derived*>( this )->post_draw( index_ );
    }

public:
    opengl_test() {
        using namespace std;
        static const float vertices[] = {
            0.0f, 0.5f,
            -0.5f, -0.5f,
            0.5f, -0.5f,

            0.0f + 0.7f, 0.5f,
            -0.5f + 0.7f, -0.5f,
            0.5f + 0.7f, -0.5f,

            0.0f - 0.7f, 0.5f,
            -0.5f - 0.7f, -0.5f,
            0.5f - 0.7f, -0.5f
        };

        _vertices_per_object = static_cast<int>( ( end( vertices ) - begin( vertices ) ) / 2 );

        static_cast<Derived*>( this )->pre_init();

        _geometry_bindings.bind();
        _geometry.bind( GL_ARRAY_BUFFER );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( _shader.get_attribute_index( "in_xyzw" ), 2, GL_FLOAT, GL_FALSE, sizeof( float ) * 2, nullptr );
        
        std::vector<float> buffer;
        buffer.reserve( _vertices_per_object * 2 * NUMBER_OF_OBJECTS );
        for ( int i = 0; i < NUMBER_OF_OBJECTS; ++i ) {
            buffer.insert( buffer.end(), begin( vertices ), end( vertices ) );
        }
        glBufferData( GL_ARRAY_BUFFER, buffer.size() * sizeof( float ), buffer.data(), GL_STATIC_DRAW );

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

