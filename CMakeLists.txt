cmake_minimum_required(VERSION 3.15)

# set the project name
project(sh_engine VERSION 1.0)
SET(SRC_LIST gl_test.cpp)
SET(CMAKE_CXX_STANDARD 11)

# add the executable
#add_subdirectory(lib)
add_executable(${PROJECT_NAME} ${SRC_LIST})
