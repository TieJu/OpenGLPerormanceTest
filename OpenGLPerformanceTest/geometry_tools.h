#pragma once

#include <glm.hpp>

template<typename Target>
inline void gen_rect_vertices( glm::vec2 from_, glm::vec2 to_, Target target_ ) {
    target_( from_ );
    target_( glm::vec2{ to_.x, from_.y } );
    target_( to_ );
    target_( to_ );
    target_( glm::vec2{ from_.x, to_.y } );
    target_( from_ );
}

template<typename Target>
inline void gen_rect_vertices_n( int count_, glm::vec2 from_, glm::vec2 to_, Target target_ ) {
    for ( int i = 0; i < count_; ++i ) {
        gen_rect_vertices( from_, to_, target_ );
    }
}