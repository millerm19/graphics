#include "window.hpp"

#include <GL/glew.h>

#include <stdexcept>

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const char* title) : window(nullptr), width(width), height(height) {
    if (!glfwInit()) {
        throw std::runtime_error(
            "Failed to initialize GLFW"
        );
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(
        width,
        height,
        title,
        nullptr,
        nullptr
    );

    if (!window) {
        glfwTerminate();

        throw std::runtime_error(
            "Failed to create GLFW window"
        );
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        glfwDestroyWindow(window);
        glfwTerminate();

        throw std::runtime_error(
            "Failed to initialize GLEW"
        );
    }

    glfwSetFramebufferSizeCallback(
        window,
        framebufferSizeCallback
    );

    // Set the initial viewport
    glViewport(0, 0, width, height);
}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}