cmake_minimum_required(VERSION 3.10)
project(xor_pro)
add_executable(xor main.cpp key.cpp)
include_directories(../ ./libs)

# mkdir build
# cd build
# cmake -G"MinGW Makefiles" ..
# cmake --build .
# xor.exe