# MathFunctions/CMakeLists.txt
project(demo7_1)
add_library(${PROJECT_NAME} src/main.cpp)
add_library(lib::demo7_1 ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    lib::glfw
    glm::glm
    lib::stb
    lib::common
)

