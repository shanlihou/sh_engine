cmake_minimum_required(VERSION 3.15)

# set the project name
project(sh_engine VERSION 1.0)
SET(SRC_LIST gl_test.cpp)
SET(CMAKE_CXX_STANDARD 11)


# add the executable
add_subdirectory(lib)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs)
add_executable(${PROJECT_NAME} ${SRC_LIST})


target_include_directories(${PROJECT_NAME}
    PUBLIC ${subprojects_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    glfw3.lib
    lib::glfw
)
