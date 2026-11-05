#ifndef WINDOW_H
#define WINDOW_H

#include "core/camera.h"
#include <GLFW/glfw3.h>
#include "objects/hittable_list.h"

class window {
public:
    window(camera& cam, hittable_list& world) : cam(cam), world(world) {}
    ~window();

    bool initialize();
    void run();

private:
    void upload_image(const pixel_buffer& image);
    void draw_image();
    hittable_list& world;

    camera& cam;
    GLFWwindow* glfw_window = nullptr;
    unsigned int texture = 0;
};

void framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height);

#endif