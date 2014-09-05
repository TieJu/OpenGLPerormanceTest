#include "app.h"

#include "measurement_tools.h"

#include <string>

/*
 * ordering fastest is top
 * persistant mapped buffer indexed
 * no_uniform_block
 * uniform_update
 * uniform_buffer_indexed
 * storage_buffer_indexed
 * uniform_buffer_mapped
 */

void app::on_event( SDL_Event & e_ ) {
    switch ( e_.type ) {
    case SDL_QUIT: _run = false; break;
    case SDL_KEYUP:
        switch ( e_.key.keysym.sym ) {
        case '0': _active_test = test_type::none; break;
        case '1': _active_test = test_type::no_uniform_block; _no_uniform_block.bind(); break;
        case '2': _active_test = test_type::uniform_update; _uniform_update.bind(); break;
        case '3': _active_test = test_type::uniform_buffer_indexed; _uniform_buffer_indexed.bind(); break;
        case '4': _active_test = test_type::storage_buffer_indexed; _storage_buffer_indexed.bind(); break;
        case '5': _active_test = test_type::uniform_buffer_mapped; _uniform_buffer_mapped.bind(); break;
        case '6': _active_test = test_type::uniform_buffer_persistent_mapped_indexed; _uniform_buffer_persistent_mapped_indexed.bind(); break;
        }
    default: break;
    }
}

void app::do_frame() {
    glClear( GL_COLOR_BUFFER_BIT );
    if ( test_type::no_uniform_block == _active_test ) {
        auto took = measure_code_time( [=] { _no_uniform_block.run(); } );
        write( std::to_string( std::chrono::duration_cast<std::chrono::microseconds>( took ).count() ).c_str() );
        write( "us no uniform buffer test\n" );
    } else if ( test_type::uniform_update == _active_test ) {
        auto took = measure_code_time( [=] { _uniform_update.run(); } );
        write( std::to_string( std::chrono::duration_cast<std::chrono::microseconds>( took ).count() ).c_str() );
        write( "us uniform buffer update test\n" );
    } else if ( test_type::uniform_buffer_indexed == _active_test ) {
        auto took = measure_code_time( [=] { _uniform_buffer_indexed.run(); } );
        write( std::to_string( std::chrono::duration_cast<std::chrono::microseconds>( took ).count() ).c_str() );
        write( "us uniform buffer indexed test\n" );
    } else if ( test_type::storage_buffer_indexed == _active_test ) {
        auto took = measure_code_time( [=] { _storage_buffer_indexed.run(); } );
        write( std::to_string( std::chrono::duration_cast<std::chrono::microseconds>( took ).count() ).c_str() );
        write( "us storage buffer indexed test\n" );
    } else if ( test_type::uniform_buffer_mapped == _active_test ) {
        auto took = measure_code_time( [=] { _uniform_buffer_mapped.run(); } );
        write( std::to_string( std::chrono::duration_cast<std::chrono::microseconds>( took ).count() ).c_str() );
        write( "us uniform buffer mapped test\n" );
    } else if ( test_type::uniform_buffer_persistent_mapped_indexed == _active_test ) {
        auto took = measure_code_time( [=] { _uniform_buffer_persistent_mapped_indexed.run(); } );
        write( std::to_string( std::chrono::duration_cast<std::chrono::microseconds>( took ).count() ).c_str() );
        write( "us uniform buffer persistent mapped indexed test\n" );
    }
    _ogl.swap();
}

void app::write( const char* str_ ) {
    WriteFile( _out, str_, static_cast<DWORD>( strlen( str_ ) ), nullptr, nullptr );
}

app::app( int argc_, char * argv_[] ) {
    AllocConsole();
    _out = GetStdHandle( STD_OUTPUT_HANDLE );
    _active_test = test_type::none;
    _run = true;

    SDL_GL_SetSwapInterval( 1 );
}

app::~app() {
}

void app::operator()() {
    SDL_Event e;

    while ( _run ) {
        while ( SDL_PollEvent( &e ) ) {
            on_event( e );
        }

        do_frame();
    }
}