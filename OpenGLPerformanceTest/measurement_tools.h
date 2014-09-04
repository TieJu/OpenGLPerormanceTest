#pragma once

#include <chrono>

template<typename CodeT>
std::chrono::high_resolution_clock::duration measure_code_time( CodeT code_ ) {
    auto start = std::chrono::high_resolution_clock::now();
    code_();
    return std::chrono::high_resolution_clock::now() - start;
}
