cmake_minimum_required(VERSION 3.10)
project(AESPRO)

file(GLOB SOURCES "./*.cpp" "./libs/*.cpp" "./AES_mode/*.cpp")

add_executable(aes ${SOURCES})

include_directories(../ ./libs ./AES_mode)


# mkdir build
# cd build
# cmake -G"MinGW Makefiles" ..
# cmake --build .
# xor.exe