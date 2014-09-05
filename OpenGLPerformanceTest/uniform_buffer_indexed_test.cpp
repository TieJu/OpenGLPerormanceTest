#include "uniform_buffer_indexed_test.h"

// limited to about 512 per batch, increasing this will generate errors on shader compilation/linking on nvidia GF GTX 660 
#define MAX_INDEX 512

static const char* vertex_shader =
"#version 440 core \n"
"in vec2 in_xyzw; \n"
"uniform int index;\n"
"struct buffer_data {\n"
"  mat4 mvp; \n"
"  vec4 color; \n"
"};\n"
"layout(std140) uniform uniform_buffer { \n"
"  buffer_data data[512]; \n"
"};\n"
"void main() { \n"
"  gl_Position = data[index].mvp * vec4(in_xyzw,-1.0,1.0); \n"
"}";
static const char* fragment_shader =
"#version 440 core \n"
"uniform int index;\n"
"struct buffer_data {\n"
"  mat4 mvp; \n"
"  vec4 color; \n"
"};\n"
"layout(std140) uniform uniform_buffer { \n"
"  buffer_data data[512]; \n"
"};\n"
"out vec4 o_color; \n"
"void main() { \n"
"  o_color = data[index].color; \n"
"}";

void uniform_buffer_indexed_test::pre_draw( int index_ ) {
    auto offset = index_ / MAX_INDEX;
    if ( offset != _last_offset ) {
        _last_offset = offset;
        _uniform_buffer.bind( GL_UNIFORM_BUFFER, _uniform_buffer_index, offset * sizeof( per_object_uniforms ) * MAX_INDEX, sizeof( per_object_uniforms ) * MAX_INDEX );
    }
    index_ %= MAX_INDEX;
    set_uniform( _index_index, 1, &index_ );
}

void uniform_buffer_indexed_test::post_draw( int index_ ) {

}

void uniform_buffer_indexed_test::pre_init() {
    _shader.set_code( 1, &vertex_shader, 1, &fragment_shader );
}

void uniform_buffer_indexed_test::post_init() {

}

void uniform_buffer_indexed_test::pre_bind() {
    glDisable( GL_CULL_FACE );
    glDisable( GL_DEPTH_TEST );
    glDepthMask( GL_FALSE );
    glDisable( GL_STENCIL_TEST );
    glDisable( GL_BLEND );
    glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
}

void uniform_buffer_indexed_test::post_bind() {
    _uniform_buffer.bind( GL_UNIFORM_BUFFER, _uniform_buffer_index, 0, sizeof( per_object_uniforms ) * MAX_INDEX );
    _last_offset = 0;
}

void uniform_buffer_indexed_test::pre_run() {
    glBufferSubData( GL_UNIFORM_BUFFER, 0, _data_buffer.size() * sizeof( per_object_uniforms ), _data_buffer.data() );
}

void uniform_buffer_indexed_test::post_run() {

}

uniform_buffer_indexed_test::uniform_buffer_indexed_test() {
    _uniform_buffer_index = _shader.get_uniform_buffer_index( "uniform_buffer" );
    _index_index = _shader.get_uniform_index( "index" );
    _uniform_buffer.bind( GL_UNIFORM_BUFFER );

    per_object_uniforms ud;
    ud._color = glm::vec4{ 1.f, 1.f, 1.f, 1.f };
    ud._mvp = glm::mat4( 1.f );
    _data_buffer.resize( NUMBER_OF_OBJECTS, ud );

    glBufferData( GL_UNIFORM_BUFFER, _data_buffer.size() * sizeof( per_object_uniforms ), nullptr, GL_DYNAMIC_DRAW );
}

uniform_buffer_indexed_test::~uniform_buffer_indexed_test() {
}
