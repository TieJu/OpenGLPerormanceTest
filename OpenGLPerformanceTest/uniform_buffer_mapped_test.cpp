#include "uniform_buffer_mapped_test.h"


static const char* shader_defines =
"#define BeginUniformBlock(name_) struct name_##_data_s {\n"
"#define EndUniformBlock(name_) }; layout(std140, binding=0) uniform name_ { name_##_data_s name_##_data ; };\n"
"#define DefineUniform(type_, name_) type_ name_; \n"
"#define GetUniform(block_, name_) block_##_data. name_\n"
"#define DeclareIndex \n";

void uniform_buffer_mapped_test::pre_draw( int index_ ) {
    per_object_uniforms data;
    data._r = glm::vec4{ 1.f, 0.f, 0.f, 0.f };
    data._g = glm::vec4{ 0.f, 1.f, 0.f, 0.f };
    data._b = glm::vec4{ 0.f, 0.f, 1.f, 0.f };
    data._a = glm::vec4{ 0.f, 0.f, 0.f, 1.f };
    data._m = glm::mat4( 1.f );
    data._v = glm::mat4( 1.f );
    data._p = glm::mat4( 1.f );
    memcpy( glMapBufferRange( GL_UNIFORM_BUFFER, 0, sizeof( data ), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT ), &data, sizeof( data ));
    glUnmapBuffer( GL_UNIFORM_BUFFER );
}

void uniform_buffer_mapped_test::post_draw( int index_ ) {

}

void uniform_buffer_mapped_test::pre_init( const char* vertex_shader_, const char* fragment_shader_ ) {
    const char* bufv[] = { shader_defines, vertex_shader_ };
    const char* buff[] = { shader_defines, fragment_shader_ };
    _shader.set_code( 2, bufv, 2, buff );
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
