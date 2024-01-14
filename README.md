# Video app in C++ with ffmpeg and glfw

## Compile on gnu/linux (debian-based)

You need to look up how to properly install `gcc, make, cmake` and its dependencies.

I've been using `VScode` with `CMake Tools plugin` to compile it.

For FFmpeg you need additional `-dev` modules and `pkg-config` so that cmake could properly link it:

`sudo apt get pkg-config ffmpeg libavcodec-dev libavformat-dev libavdevice-dev libavutil-dev libswresample-dev libswscale-dev`

This project is roughly based on [bartjoyce streams](https://youtu.be/MEMzo59CPr8) so you could consult his videos for further information.