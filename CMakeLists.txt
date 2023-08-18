cmake_minimum_required(VERSION 3.13.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project (2d_engine)
set(CMAKE_GENERATOR "Unix Makefiles")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES src/main.cpp src/quadtree/quadtree.cpp src/grid/grid.cpp)
set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/deps/p8g src/ src/quadtree src/grid)

link_directories(${CMAKE_SOURCE_DIR}/deps/p8g)
add_executable(2d_engine ${SOURCES})
target_include_directories(2d_engine PUBLIC ${INCLUDE_DIRS})

target_compile_options(2d_engine PRIVATE -g)
target_link_libraries(2d_engine p8g++)