#include "uniform_buffer_persistent_mapped_indexed_test.h"

// limited to about 256 per batch, increasing this will generate errors on shader compilation/linking on nvidia GF GTX 660 
#define MAX_INDEX 256

// add a fixed 4 frame latency w/o any sync stuff
#define FRAME_LATENCY 4

static const char* shader_defines =
"#define BeginUniformBlock(name_) struct name_##_data_s {\n"
"#define EndUniformBlock(name_) }; layout(std140, binding=0) uniform name_ { name_##_data_s name_##_data [256] ; };\n"
"#define DefineUniform(type_, name_) type_ name_; \n"
"#define GetUniform(block_, name_) block_##_data[index]. name_\n"
"#define DeclareIndex uniform int index;\n";

#define FrameOffsetIndex(frame_) ( frame_ % FRAME_LATENCY ) * NUMBER_OF_OBJECTS
#define FrameOffset(frame_) ( FrameOffsetIndex(frame_) * sizeof( per_object_uniforms ) )

void uniform_buffer_persistent_mapped_indexed_test::pre_draw( int index_ ) {
    _data_ptr[FrameOffsetIndex( _frame_index ) + index_]._r = glm::vec4{ 1.f, 0.f, 0.f, 0.f };
    _data_ptr[FrameOffsetIndex( _frame_index ) + index_]._g = glm::vec4{ 0.f, 1.f, 0.f, 0.f };
    _data_ptr[FrameOffsetIndex( _frame_index ) + index_]._b = glm::vec4{ 0.f, 0.f, 1.f, 0.f };
    _data_ptr[FrameOffsetIndex( _frame_index ) + index_]._a = glm::vec4{ 0.f, 0.f, 0.f, 1.f };
    _data_ptr[FrameOffsetIndex( _frame_index ) + index_]._m = glm::mat4( 1.f );
    _data_ptr[FrameOffsetIndex( _frame_index ) + index_]._v = glm::mat4( 1.f );
    _data_ptr[FrameOffsetIndex( _frame_index ) + index_]._p = glm::mat4( 1.f );
    auto offset = index_ / MAX_INDEX;
    if ( offset != _last_offset ) {
        _last_offset = offset;
        _uniform_buffer.bind( GL_UNIFORM_BUFFER, _uniform_buffer_index, FrameOffset( _frame_index ) + offset * sizeof( per_object_uniforms ) * MAX_INDEX, sizeof( per_object_uniforms ) * MAX_INDEX );
    }
    index_ %= MAX_INDEX;
    set_uniform( _index_index, 1, &index_ );
}

void uniform_buffer_persistent_mapped_indexed_test::post_draw( int index_ ) {

}

void uniform_buffer_persistent_mapped_indexed_test::pre_init( const char* vertex_shader_, const char* fragment_shader_ ) {
    const char* bufv[] = { shader_defines, vertex_shader_ };
    const char* buff[] = { shader_defines, fragment_shader_ };
    _shader.set_code( 2, bufv, 2, buff );
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
    glBufferStorage( GL_UNIFORM_BUFFER, NUMBER_OF_OBJECTS * sizeof( per_object_uniforms ) * FRAME_LATENCY, nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT );
    _data_ptr = reinterpret_cast<per_object_uniforms*>( glMapBufferRange( GL_UNIFORM_BUFFER, 0, NUMBER_OF_OBJECTS * sizeof( per_object_uniforms ) * FRAME_LATENCY, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT ) );
}

uniform_buffer_persistent_mapped_indexed_test::~uniform_buffer_persistent_mapped_indexed_test() {}
