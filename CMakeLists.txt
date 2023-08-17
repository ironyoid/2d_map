cmake_minimum_required(VERSION 3.13.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project (2d_engine)
set(CMAKE_GENERATOR "Unix Makefiles")
set(SDL2_DIR C:/SDL2-devel-2.28.2-mingw/SDL2-2.28.2/cmake/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES src/main.cpp src/engine/render/render.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(2d_engine ${SOURCES})
target_link_libraries(2d_engine ${SDL2_LIBRARIES})

target_compile_options(2d_engine PRIVATE -g)
target_include_directories(2d_engine PUBLIC ${PROJECT_SOURCE_DIR}/deps/include)
target_include_directories(2d_engine PUBLIC ${PROJECT_SOURCE_DIR}/src/engine)