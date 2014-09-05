#include "no_uniform_block_test.h"


static const char* vertex_shader =
"#version 440 core \n"
"in vec2 in_xyzw; \n"
"uniform mat4 m; \n"
"uniform mat4 v; \n"
"uniform mat4 p; \n"
"void main() { \n"
"  gl_Position = m * v * p * vec4(in_xyzw,-1.0,1.0); \n"
"}";
static const char* fragment_shader =
"#version 440 core \n"
"uniform vec4 r; \n"
"uniform vec4 g; \n"
"uniform vec4 b; \n"
"uniform vec4 a; \n"
"out vec4 o_color; \n"
"void main() { \n"
"  o_color = r + g + b + a; \n"
"}";

void no_uniform_block_test::pre_draw( int index_ ) {
    set_uniform( _m_index, 1, &_per_object_uniforms[index_]._m );
    set_uniform( _v_index, 1, &_per_object_uniforms[index_]._v );
    set_uniform( _p_index, 1, &_per_object_uniforms[index_]._p );
    set_uniform( _r_index, 1, &_per_object_uniforms[index_]._r );
    set_uniform( _g_index, 1, &_per_object_uniforms[index_]._g );
    set_uniform( _b_index, 1, &_per_object_uniforms[index_]._b );
    set_uniform( _a_index, 1, &_per_object_uniforms[index_]._a );
}

void no_uniform_block_test::post_draw( int index_ ) {

}

void no_uniform_block_test::pre_init() {
    _shader.set_code( 1, &vertex_shader, 1, &fragment_shader );
}

void no_uniform_block_test::post_init() {

}

void no_uniform_block_test::pre_bind() {
}

void no_uniform_block_test::post_bind() {
    glDisable( GL_CULL_FACE );
    glDisable( GL_DEPTH_TEST );
    glDepthMask( GL_FALSE );
    glDisable( GL_STENCIL_TEST );
    glDisable( GL_BLEND );
    glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
}

void no_uniform_block_test::pre_run() {
}

void no_uniform_block_test::post_run() {
}

no_uniform_block_test::no_uniform_block_test() {
    _m_index = _shader.get_uniform_index( "m" );
    _v_index = _shader.get_uniform_index( "v" );
    _p_index = _shader.get_uniform_index( "p" );
    _r_index = _shader.get_uniform_index( "r" );
    _g_index = _shader.get_uniform_index( "g" );
    _b_index = _shader.get_uniform_index( "b" );
    _a_index = _shader.get_uniform_index( "a" );

    per_object_uniforms ob;
    ob._r = glm::vec4{ 1.f, 0.f, 0.f, 0.f };
    ob._g = glm::vec4{ 0.f, 1.f, 0.f, 0.f };
    ob._b = glm::vec4{ 0.f, 0.f, 1.f, 0.f };
    ob._a = glm::vec4{ 0.f, 0.f, 0.f, 1.f };
    ob._m = glm::mat4( 1.f );
    ob._v = glm::mat4( 1.f );
    ob._p = glm::mat4( 1.f );
    _per_object_uniforms.resize( NUMBER_OF_OBJECTS, ob );
}

no_uniform_block_test::~no_uniform_block_test() {
}

