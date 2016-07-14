cmake_minimum_required(VERSION 3.5)
project(Aufgabe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
        externals/glm
        #/usr/include/GL
)

set(SOURCE_FILES
    media/shader/FragmentShader.glsl
    media/shader/VertexShader.glsl
    source/Rendering/Defines.h
    source/Rendering/Helper.cpp
    source/Rendering/Helper.h
    source/Rendering/Precompiled.cpp
    source/Rendering/Precompiled.h
    source/Rendering/Rendering.cpp
    source/Rendering/Rendering.h
        source/Rendering/Cube.h
        source/Rendering/Cube.cpp
        source/Rendering/Drawable.cpp
        source/Rendering/Drawable.h
        source/Rendering/Sphere.cpp
        source/Rendering/Sphere.h)



add_executable(Aufgabe ${SOURCE_FILES})

target_link_libraries(Aufgabe
        GL
        glut
        GLEW
        GLU
)

