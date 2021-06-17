cmake_minimum_required (VERSION 3.13)
project(MpiPutTypeVecTest VERSION "0.0.0")
set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)

add_executable(exe test.cpp)
target_link_libraries(exe MPI::MPI_C)
