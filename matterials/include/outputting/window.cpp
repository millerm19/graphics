#include "window.h"

window::~window() {
    if (texture != 0) {
        glDeleteTextures(1, &texture);
    }

    if (glfw_window) {
        glfwDestroyWindow(glfw_window);
    }

    glfwTerminate();
}

bool window::initialize() {

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    // Request an old-style OpenGL context.
    // This lets us use simple immediate-mode drawing for now.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // Render the camera image
    const pixel_buffer& image = cam.render(world);

    // Create window using image dimensions
    glfw_window = glfwCreateWindow(
        image.width(),
        image.height(),
        "Ray Tracer",
        nullptr,
        nullptr
    );

    if (!glfw_window) {
        std::cerr << "Failed to create GLFW window\n";
        return false;
    }

    glfwMakeContextCurrent(glfw_window);

    glfwSetFramebufferSizeCallback(
        glfw_window,
        framebuffer_size_callback
    );

    int width, height;
    glfwGetFramebufferSize(glfw_window, &width, &height);
    glViewport(0, 0, width, height);

    // Create OpenGL texture
    glGenTextures(1, &texture);

    // Upload image to texture
    upload_image(image);

    return true;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void window::upload_image(const pixel_buffer& image) {

    glBindTexture(GL_TEXTURE_2D, texture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        image.width(),
        image.height(),
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        image.data()
    );
}

void window::draw_image() {

    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Draw a fullscreen textured quad
    glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(-1.0f, -1.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(1.0f, -1.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(1.0f, 1.0f);

        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-1.0f, 1.0f);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void window::run() {

    int dir = -1;
    int vfov = 90;

    while (!glfwWindowShouldClose(glfw_window)) {

        if(vfov < 40) {
            dir = 1;
        } else if(vfov > 140) {
            dir = -1;
        }

        vfov += dir;

        cam.vfov = vfov;

        const pixel_buffer& image = cam.render(world);

        upload_image(image);

        draw_image();

        glfwSwapBuffers(glfw_window);
        glfwPollEvents();
    }
}