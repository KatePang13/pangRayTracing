cmake_minimum_required(VERSION 3.10)
project(pangRayRracing)

set(CMAKE_CXX_STANDARED 17)

add_executable(pangRayRracing main.cpp hittable.h hittable_list.h vec3.h color.h ray.h sphere.h )
target_compile_options(pangRayRracing PUBLIC -Wall -Wextra -pedantic -Wshadow -Wreturn-type -fsanitize=undefined)
target_compile_features(pangRayRracing PUBLIC cxx_std_17)
target_link_libraries(pangRayRracing PUBLIC -fsanitize=undefined)