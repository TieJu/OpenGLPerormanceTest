#pragma once

#include <SDL.h>

struct sdl {
    sdl( Uint32 flags_ = SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER ) { SDL_Init( flags_ ); }
    ~sdl() { SDL_Quit(); }
};

