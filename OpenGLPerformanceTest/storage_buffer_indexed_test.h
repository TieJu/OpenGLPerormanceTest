#pragma once

#include "opengl_test.h"

class storage_buffer_indexed_test : public opengl_test<storage_buffer_indexed_test> {
    struct per_object_uniforms {
        glm::mat4   _m;
        glm::mat4   _v;
        glm::mat4   _p;
        glm::vec4   _r;
        glm::vec4   _g;
        glm::vec4   _b;
        glm::vec4   _a;
    };

    friend class opengl_test<storage_buffer_indexed_test>;
    std::vector<per_object_uniforms>    _data_buffer;
    int                                 _index_index;
    int                                 _uniform_buffer_index;
    vertex_buffer                       _uniform_buffer;

    void pre_draw( int index_ );
    void post_draw( int index_ );

    void pre_init();
    void post_init();

    void pre_bind();
    void post_bind();

    void pre_run();
    void post_run();

public:
    storage_buffer_indexed_test();
    ~storage_buffer_indexed_test();
};