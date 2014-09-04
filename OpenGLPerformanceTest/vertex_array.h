#pragma once

#include "opengl.h"

class vertex_array {
    GLuint  _va;

public:
    vertex_array();
    ~vertex_array();

    void bind();
};

