#include "no_uniform_block_test.h"

#include <vector>
#include <iterator>
#include <gtc/matrix_transform.hpp>

static const char* vertex_shader =
"#version 440 core \n"
"in vec2 in_xyzw; \n"
"uniform mat4 mvp; \n"
"void main() { \n"
"  gl_Position = mvp * vec4(in_xyzw,-1.0,1.0); \n"
"}";
static const char* fragment_shader =
"#version 440 core \n"
"uniform vec4 color; \n"
"out vec4 o_color; \n"
"void main() { \n"
"  o_color = color; \n"
"}";

void no_uniform_block_test::pre_draw( int index_ ) {
    set_uniform( _mvp_index, 1, &_per_object_uniforms[index_]._mvp );
    set_uniform( _color_index, 1, &_per_object_uniforms[index_]._color );
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
    _mvp_index = _shader.get_uniform_index( "mvp" );
    _color_index = _shader.get_uniform_index( "color" );

    per_object_uniforms ob;
    ob._color = glm::vec4{ 1.f, 1.f, 1.f, 1.f };
    ob._mvp = glm::mat4( 1.f );
    _per_object_uniforms.resize( NUMBER_OF_OBJECTS, ob );
}

no_uniform_block_test::~no_uniform_block_test() {
}

