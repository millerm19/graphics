#pragma once

#include "color.hpp"

#include <vector>

class Renderer
{
public:
    Renderer(int width, int height);

    void render();

    const std::vector<Color>& getPixels() const;

    int getWidth() const;
    int getHeight() const;

private:
    int width;
    int height;

    std::vector<Color> pixels;
};