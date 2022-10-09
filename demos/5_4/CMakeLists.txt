# MathFunctions/CMakeLists.txt
project(demo5_4)
add_library(${PROJECT_NAME} src/main.cpp)
add_library(lib::demo5_4 ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    lib::glfw
    glm::glm
    lib::stb
    lib::common
)

