cmake_minimum_required(VERSION 3.23)

# set the project name
project(MyNumber)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXPORT_COMPILE_COMMANDS ON)

# add the executable
file(GLOB SOURCES "src/*.cpp")
add_executable(MyNumber ${SOURCES})

# set curl path
set(CMAKE_AR gcc-ar)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static-libstdc++ -static-libgcc")

target_compile_options(MyNumber PRIVATE -fdiagnostics-color=always -pedantic)

# add curl
target_include_directories(MyNumber PRIVATE ${CMAKE_SOURCE_DIR}/header)