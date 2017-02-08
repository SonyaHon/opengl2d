cmake_minimum_required(VERSION 3.5)
project(2ds)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.2 REQUIRED)

set(CMAKE_CXX_FLAGS -std=c++11)

include_directories(/usr/local/include/freetype2 /usr/local/include)

set(ALL_LIBS
        GLEW
        ${OPENGL_LIBRARY}
        GL
        glfw
        png
        freetype
        )

set(SOURCES main.cpp Utils/Display.cpp Utils/Display.h Utils/Renderer.cpp Utils/Renderer.h Sprites/Sprite.cpp Sprites/Sprite.h Sprites/Image.cpp Sprites/Image.h Shaders/ShaderProgram.cpp Shaders/ShaderProgram.h Utils/Camera.cpp Utils/Camera.h Utils/Enums.h Utils/Timer.cpp Utils/Timer.h Utils/Utils.h Collisions/Collider.cpp Collisions/Collider.h Utils/FBO.cpp Utils/FBO.h)

add_executable(2ds ${SOURCES})
target_link_libraries(2ds
        ${ALL_LIBS}
        )