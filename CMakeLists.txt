 cmake_minimum_required(VERSION 3.14)
 project (video-app C CXX)
 set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/FFmpeg)
add_subdirectory(lib/glfw)

if(APPLE)
    list(APPEND EXTRA_LIBS
        "-framework OpenGL"
    )
elseif(WIN32)
    list(APPEND EXTRA_LIBS
    "-lglu32 -lopengl32"
    )
    set(CMAKE_EXE_LINKER_FLAGS "-std=gnu99 -static -static-libgcc -static-libstdc++ -mwindows")
else()
    list(APPEND EXTRA_LIBS
    "-lGL -lGLU -lX11 -lavformat -lavcodec -lswscale -lavutil -lz"
    )
endif()

list(APPEND SOURCES
    src/load_frame.cpp
    src/main.cpp
    )

add_executable(video-app src/main.cpp src/load_frame.cpp)
target_link_libraries(video-app FFmpeg glfw ${EXTRA_LIBS})