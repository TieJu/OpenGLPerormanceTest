#pragma once

#include "opengl_test.h"

class no_uniform_block_test : public opengl_test<no_uniform_block_test> {
    struct per_object_uniforms {
        glm::mat4   _m;
        glm::mat4   _v;
        glm::mat4   _p;
        glm::vec4   _r;
        glm::vec4   _g;
        glm::vec4   _b;
        glm::vec4   _a;
    };

    friend class opengl_test<no_uniform_block_test>;
    std::vector<per_object_uniforms>    _per_object_uniforms;
    int                                 _m_index;
    int                                 _v_index;
    int                                 _p_index;
    int                                 _r_index;
    int                                 _g_index;
    int                                 _b_index;
    int                                 _a_index;

    void pre_draw( int index_ );
    void post_draw( int index_ );

    void pre_init( const char* vertex_shader_, const char* fragment_shader_ );
    void post_init();

    void pre_bind();
    void post_bind();

    void pre_run();
    void post_run();

public:
    no_uniform_block_test();
    ~no_uniform_block_test();
};

