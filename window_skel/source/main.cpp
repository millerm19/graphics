#include "window.hpp"
#include "renderer.hpp"
#include "texture_display.hpp"

#include <GL/glew.h>

#include <iostream>
#include <exception>

int main()
{
    try
    {
        const int width = 256;
        const int height = 256;

        Window window(
            width,
            height,
            "Ray Tracer"
        );

        Renderer renderer(
            width,
            height
        );

        TextureDisplay display(
            width,
            height
        );

        while (!window.shouldClose())
        {
            // Generate the CPU-side image
            renderer.render();

            // Upload pixels to the GPU
            display.update(
                renderer.getPixels()
            );

            // Draw the texture to the window
            glClearColor(
                0.1f,
                0.1f,
                0.15f,
                1.0f
            );

            glClear(GL_COLOR_BUFFER_BIT);

            display.draw();

            window.update();
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: "
                  << error.what()
                  << '\n';

        return 1;
    }

    return 0;
}