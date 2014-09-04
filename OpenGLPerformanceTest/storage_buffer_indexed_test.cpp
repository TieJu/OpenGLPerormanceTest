#include "storage_buffer_indexed_test.h"

static const char* vertex_shader =
"#version 440 core \n"
"in vec2 in_xyzw; \n"
"uniform int index;\n"
"struct buffer_data {\n"
"  mat4 mvp; \n"
"  vec4 color; \n"
"};\n"
"layout(std140, binding=0) buffer uniform_buffer { \n"
"  buffer_data data[]; \n"
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
"layout(std140, binding=0) buffer uniform_buffer { \n"
"  buffer_data data[]; \n"
"};\n"
"out vec4 o_color; \n"
"void main() { \n"
"  o_color = data[index].color; \n"
"}";

void storage_buffer_indexed_test::pre_draw( int index_ ) {
    set_uniform( _index_index, 1, &index_ );
}

void storage_buffer_indexed_test::post_draw( int index_ ) {

}

void storage_buffer_indexed_test::pre_init() {
    _shader.set_code( 1, &vertex_shader, 1, &fragment_shader );
}

void storage_buffer_indexed_test::post_init() {

}

void storage_buffer_indexed_test::pre_bind() {
    glDisable( GL_CULL_FACE );
    glDisable( GL_DEPTH_TEST );
    glDepthMask( GL_FALSE );
    glDisable( GL_STENCIL_TEST );
    glDisable( GL_BLEND );
    glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
}

void storage_buffer_indexed_test::post_bind() {
    _uniform_buffer.bind( GL_SHADER_STORAGE_BUFFER, _uniform_buffer_index, 0, _data_buffer.size() * sizeof( per_object_uniforms ) );
}

void storage_buffer_indexed_test::pre_run() {
    glBufferSubData( GL_SHADER_STORAGE_BUFFER, 0, _data_buffer.size() * sizeof( per_object_uniforms ), _data_buffer.data() );
}

void storage_buffer_indexed_test::post_run() {

}

storage_buffer_indexed_test::storage_buffer_indexed_test() {
    _uniform_buffer_index = 0;// _shader.get_uniform_buffer_index( "uniform_buffer" );
    _index_index = _shader.get_uniform_index( "index" );
    _uniform_buffer.bind( GL_SHADER_STORAGE_BUFFER );

    per_object_uniforms ud;
    ud._color = glm::vec4{ 1.f, 1.f, 1.f, 1.f };
    ud._mvp = glm::mat4( 1.f );
    _data_buffer.resize( NUMBER_OF_OBJECTS, ud );

    glBufferData( GL_SHADER_STORAGE_BUFFER, _data_buffer.size() * sizeof( per_object_uniforms ), nullptr, GL_DYNAMIC_DRAW );
}

storage_buffer_indexed_test::~storage_buffer_indexed_test() {}
