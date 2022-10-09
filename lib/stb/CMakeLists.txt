# MathFunctions/CMakeLists.txt
project(stb)
add_library(${PROJECT_NAME} stb_vorbis.c)
add_library(lib::stb ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)
