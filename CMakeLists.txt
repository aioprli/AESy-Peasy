cmake_minimum_required(VERSION 3.10)
project(AESPRO)

file(GLOB SOURCES "./*.cpp" "./libs/*.cpp")

add_executable(aes ${SOURCES})

include_directories(../ ./libs)


# mkdir build
# cd build
# cmake -G"MinGW Makefiles" ..
# cmake --build .
# xor.exe