#include <stdio.h>
#include <GLFW/glfw3.h>
#include "load_frame.h"
 


int main(int argc, char * argv[])
{
    GLFWwindow* window;

    if (!glfwInit()) {
        printf("Couldn't init GLFW\n");
        return 1;
    }

    window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL);
    if(!window) {
        printf("Couldn't open window\n");
        return 1;
    }

    int frame_width, frame_height;
    unsigned char* frame_data;

    if(!load_frame("/home/ukn/Videos/sample.mp4", &frame_width, &frame_height, &frame_data)) {
        printf("Couldn't load video frame\n");
        return 1;
    }

     glfwMakeContextCurrent(window);

    GLuint tex_handle;
    glGenTextures(1, &tex_handle);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame_width, frame_height, 0, GL_RGB, GL_UNSIGNED_BYTE, frame_data);

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        /* Set up orthographic projection */
        int window_width, window_height;
        glfwGetFramebufferSize(window, &window_width, &window_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, window_width, 0, window_height, -1, 1);
        glMatrixMode(GL_MODELVIEW);

        /* Render whatever you want */
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_handle);
        glBegin(GL_QUADS);
            glTexCoord2d(0,1); glVertex2i (0, frame_height);
            glTexCoord2d(1,0); glVertex2i (frame_width, 0);
            glTexCoord2d(1,1); glVertex2i (frame_width, frame_height);
            glTexCoord2d(0,1); glVertex2i ( 0, frame_height);
        glEnd();
        glDisable(GL_TEXTURE_2D);


        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    return 0;
} 