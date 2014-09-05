#include "uniform_buffer_mapped_test.h"

static const char* vertex_shader =
"#version 440 core \n"
"in vec2 in_xyzw; \n"
"layout(std140) uniform uniform_buffer { \n"
"  mat4 m; \n"
"  mat4 v; \n"
"  mat4 p; \n"
"  vec4 color; \n"
"};\n"
"void main() { \n"
"  gl_Position = m * v * p * vec4(in_xyzw,-1.0,1.0); \n"
"}";
static const char* fragment_shader =
"#version 440 core \n"
"layout(std140) uniform uniform_buffer { \n"
"  mat4 m; \n"
"  mat4 v; \n"
"  mat4 p; \n"
"  vec4 color; \n"
"};\n"
"out vec4 o_color; \n"
"void main() { \n"
"  o_color = color; \n"
"}";

void uniform_buffer_mapped_test::pre_draw( int index_ ) {
    per_object_uniforms data;
    data._color = glm::vec4{ 1.f, 1.f, 1.f, 1.f };
    data._m = glm::mat4( 1.f );
    data._v = glm::mat4( 1.f );
    data._p = glm::mat4( 1.f );
    memcpy( glMapBufferRange( GL_UNIFORM_BUFFER, 0, sizeof( data ), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT ), &data, sizeof( data ));
    glUnmapBuffer( GL_UNIFORM_BUFFER );
}

void uniform_buffer_mapped_test::post_draw( int index_ ) {

}

void uniform_buffer_mapped_test::pre_init() {
    _shader.set_code( 1, &vertex_shader, 1, &fragment_shader );
}

void uniform_buffer_mapped_test::post_init() {

}

void uniform_buffer_mapped_test::pre_bind() {
    glDisable( GL_CULL_FACE );
    glDisable( GL_DEPTH_TEST );
    glDepthMask( GL_FALSE );
    glDisable( GL_STENCIL_TEST );
    glDisable( GL_BLEND );
    glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
}

void uniform_buffer_mapped_test::post_bind() {
    _uniform_buffer.bind( GL_UNIFORM_BUFFER );
    _uniform_buffer.bind( GL_UNIFORM_BUFFER, _uniform_buffer_index, 0, sizeof( per_object_uniforms ) );
}

void uniform_buffer_mapped_test::pre_run() {

}

void uniform_buffer_mapped_test::post_run() {

}

uniform_buffer_mapped_test::uniform_buffer_mapped_test() {
    _uniform_buffer_index = _shader.get_uniform_buffer_index( "uniform_buffer" );
    _uniform_buffer.bind( GL_UNIFORM_BUFFER );
    glBufferData( GL_UNIFORM_BUFFER, sizeof( per_object_uniforms ), nullptr, GL_STREAM_DRAW );
}

uniform_buffer_mapped_test::~uniform_buffer_mapped_test() {}
