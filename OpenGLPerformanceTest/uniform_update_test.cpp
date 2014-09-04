#include "uniform_update_test.h"

static const char* vertex_shader =
"#version 440 core \n"
"in vec2 in_xyzw; \n"
"layout(std140) uniform uniform_buffer { \n"
"  mat4 mvp; \n"
"  vec4 color; \n"
"};\n"
"void main() { \n"
"  gl_Position = mvp * vec4(in_xyzw,-1.0,1.0); \n"
"}";
static const char* fragment_shader =
"#version 440 core \n"
"layout(std140) uniform uniform_buffer { \n"
"  mat4 mvp; \n"
"  vec4 color; \n"
"};\n"
"out vec4 o_color; \n"
"void main() { \n"
"  o_color = color; \n"
"}";

void uniform_update_test::pre_draw( int index_ ) {
    per_object_uniforms data;
    data._color = glm::vec4{ 1.f, 1.f, 1.f, 1.f };
    data._mvp = glm::mat4( 1.f );
    //glBufferData( GL_UNIFORM_BUFFER, sizeof( per_object_uniforms ), nullptr, GL_STREAM_DRAW );
    glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeof( data ), &data );
}

void uniform_update_test::post_draw( int index_ ) {

}

void uniform_update_test::pre_init() {
    _shader.set_code( 1, &vertex_shader, 1, &fragment_shader );
}

void uniform_update_test::post_init() {

}

void uniform_update_test::pre_bind() {
    glDisable( GL_CULL_FACE );
    glDisable( GL_DEPTH_TEST );
    glDepthMask( GL_FALSE );
    glDisable( GL_STENCIL_TEST );
    glDisable( GL_BLEND );
    glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
}

void uniform_update_test::post_bind() {
    _uniform_buffer.bind( GL_UNIFORM_BUFFER );
}

void uniform_update_test::pre_run() {
    _uniform_buffer.bind( GL_UNIFORM_BUFFER, _uniform_buffer_index, 0, sizeof( per_object_uniforms ) );
}

void uniform_update_test::post_run() {

}

uniform_update_test::uniform_update_test() {
    _uniform_buffer_index = _shader.get_uniform_buffer_index( "uniform_buffer" );
    _uniform_buffer.bind( GL_UNIFORM_BUFFER );
    glBufferData( GL_UNIFORM_BUFFER, sizeof( per_object_uniforms ), nullptr, GL_STREAM_DRAW );
}

uniform_update_test::~uniform_update_test() {
}