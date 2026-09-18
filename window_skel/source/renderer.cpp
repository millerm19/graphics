#include "renderer.hpp"

Renderer::Renderer(int width, int height)
    : width(width),
      height(height),
      pixels(width * height)
{
}

void Renderer::render() {
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = y * width + x;

            pixels[index].r =
                static_cast<unsigned char>(
                    255.0f * x / (width - 1)
                );

            pixels[index].g =
                static_cast<unsigned char>(
                    255.0f * y / (height - 1)
                );

            pixels[index].b = 100;


            if(x > 64 && x<192 && y>64 && y<192) {
                pixels[index].r = 0;
                pixels[index].g = 0;
                pixels[index].b = 0;
            }
        }
    }
}

const std::vector<Color>& Renderer::getPixels() const
{
    return pixels;
}

int Renderer::getWidth() const
{
    return width;
}

int Renderer::getHeight() const
{
    return height;
}