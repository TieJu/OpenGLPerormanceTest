#include "opengl_test.h"

std::shared_ptr<shared_state> get_shared_state() {
    static std::weak_ptr<shared_state> state;

    auto s = state.lock();
    if ( !s ) {
        s = std::make_shared<shared_state>();
        state = s;

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

        s->_vertices_per_object = static_cast<int>( ( end( vertices ) - begin( vertices ) ) / 2 );

        s->_geometry.bind( GL_ARRAY_BUFFER );
        std::vector<float> buffer;
        buffer.reserve( s->_vertices_per_object * 2 * NUMBER_OF_OBJECTS );
        for ( int i = 0; i < NUMBER_OF_OBJECTS; ++i ) {
            buffer.insert( buffer.end(), begin( vertices ), end( vertices ) );
        }
        glBufferData( GL_ARRAY_BUFFER, buffer.size() * sizeof( float ), buffer.data(), GL_STATIC_DRAW );
    }

    return s;
}