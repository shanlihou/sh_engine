# MathFunctions/CMakeLists.txt
project(glfw)
add_library(${PROJECT_NAME} src/glad.c)
add_library(lib::glfw ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
