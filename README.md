# Video app in C++ with ffmpeg. 

## Compile on gnu/linux (debian-based)

You need to look up how to properly install gcc, make, cmake and its dependencies.

I've been using VScode with CMake Tools to compile it.

For FFmpeg you need additional `-dev` modules and `pkg-config` to search for it:

`apt get pkg-config ffmpeg libavcodec-dev libavformat-dev libavdevice-dev libavutil-dev libswresample-dev libswscale-dev`