add_executable(SIMD main.cpp)

target_link_libraries(SIMD pico_stdlib)

pico_add_extra_outputs(SIMD)