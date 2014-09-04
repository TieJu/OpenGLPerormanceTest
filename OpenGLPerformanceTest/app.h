#pragma once

#include "sdl.h"
#include "opengl.h"

#include "no_uniform_block_test.h"
#include "uniform_update_test.h"
#include "uniform_buffer_indexed_test.h"
#include "storage_buffer_indexed_test.h"
#include "uniform_buffer_mapped_test.h"
#include "uniform_buffer_persistent_mapped_indexed_test.h"

class app {
    bool                                            _run;
    sdl                                             _sdl;
    opengl                                          _ogl;
    no_uniform_block_test                           _no_uniform_block;
    uniform_update_test                             _uniform_update;
    uniform_buffer_indexed_test                     _uniform_buffer_indexed;
    storage_buffer_indexed_test                     _storage_buffer_indexed;
    uniform_buffer_mapped_test                      _uniform_buffer_mapped;
    uniform_buffer_persistent_mapped_indexed_test   _uniform_buffer_persistent_mapped_indexed;
    HANDLE                                          _out;
    enum class test_type {
        none,
        no_uniform_block,
        uniform_update,
        uniform_buffer_indexed,
        storage_buffer_indexed,
        uniform_buffer_mapped,
        uniform_buffer_persistent_mapped_indexed
    }                       _active_test;

    void on_event( SDL_Event& e_ );
    void do_frame();
    void write( const char* str_ );

public:
    app( int argc_, char *argv_[] );
    ~app();
    void operator()();
};

