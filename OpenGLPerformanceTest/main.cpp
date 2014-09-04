#include <SDL_main.h>

#include "app.h"

int SDL_main( int argc_, char *argv_[] ) {
    try {
        app{ argc_, argv_ }();
    } catch ( ... ) {

    }
    return 0;
}