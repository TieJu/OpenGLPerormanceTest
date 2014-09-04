#include "uniform_buffer_persistent_mapped_indexed_test.h"

#define MAX_INDEX 512
#define FRAME_LATENCY 4

static const char* vertex_shader =
"#version 450 core \n"
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
"#version 450 core \n"
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

#define FrameOffsetIndex(frame_) ( frame_ % FRAME_LATENCY ) * NUMBER_OF_OBJECTS
#define FrameOffset(frame_) ( FrameOffsetIndex(frame_) * sizeof( per_object_uniforms ) )

void uniform_buffer_persistent_mapped_indexed_test::pre_draw( int index_ ) {
    _data_ptr[FrameOffsetIndex(_frame_index) + index_]._color = glm::vec4( 1.f );
    _data_ptr[FrameOffsetIndex( _frame_index ) + index_]._mvp = glm::mat4( 1.f );
    auto offset = index_ / MAX_INDEX;
    if ( offset != _last_offset ) {
        _last_offset = offset;
        _uniform_buffer.bind( GL_UNIFORM_BUFFER, _uniform_buffer_index, FrameOffset( _frame_index ) + offset * sizeof( per_object_uniforms ) * MAX_INDEX, sizeof( per_object_uniforms ) * MAX_INDEX );
    }
    set_uniform( _index_index, 1, &index_ );
}

void uniform_buffer_persistent_mapped_indexed_test::post_draw( int index_ ) {

}

void uniform_buffer_persistent_mapped_indexed_test::pre_init() {
    _shader.set_code( 1, &vertex_shader, 1, &fragment_shader );
}

void uniform_buffer_persistent_mapped_indexed_test::post_init() {

}

void uniform_buffer_persistent_mapped_indexed_test::pre_bind() {
    glDisable( GL_CULL_FACE );
    glDisable( GL_DEPTH_TEST );
    glDepthMask( GL_FALSE );
    glDisable( GL_STENCIL_TEST );
    glDisable( GL_BLEND );
    glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
}

void uniform_buffer_persistent_mapped_indexed_test::post_bind() {
    _last_offset = 0;
}

void uniform_buffer_persistent_mapped_indexed_test::pre_run() {
    _uniform_buffer.bind( GL_UNIFORM_BUFFER, _uniform_buffer_index, FrameOffset( _frame_index ), sizeof( per_object_uniforms ) * MAX_INDEX );
    ++_frame_index;
}

void uniform_buffer_persistent_mapped_indexed_test::post_run() {
}

uniform_buffer_persistent_mapped_indexed_test::uniform_buffer_persistent_mapped_indexed_test() {
    _frame_index = 0;
    _uniform_buffer_index = _shader.get_uniform_buffer_index( "uniform_buffer" );
    _index_index = _shader.get_uniform_index( "index" );

    _uniform_buffer.bind( GL_UNIFORM_BUFFER );
    //glBufferData( GL_UNIFORM_BUFFER, _data_buffer.size() * sizeof( per_object_uniforms ), nullptr, GL_DYNAMIC_DRAW );
    glBufferStorage( GL_UNIFORM_BUFFER, NUMBER_OF_OBJECTS * sizeof( per_object_uniforms ) * FRAME_LATENCY, nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT );
    _data_ptr = reinterpret_cast<per_object_uniforms*>( glMapBufferRange( GL_UNIFORM_BUFFER, 0, NUMBER_OF_OBJECTS * sizeof( per_object_uniforms ) * FRAME_LATENCY, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT ) );
}

uniform_buffer_persistent_mapped_indexed_test::~uniform_buffer_persistent_mapped_indexed_test() {}
