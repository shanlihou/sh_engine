# MathFunctions/CMakeLists.txt
project(common)
add_library(${PROJECT_NAME} src/Texture2D.cpp)
add_library(lib::common ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE lib::stb
    PRIVATE lib::glfw
)
