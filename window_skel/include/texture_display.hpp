#pragma once

#include "color.hpp"

#include <GL/glew.h>

#include <vector>

class TextureDisplay
{
public:
    TextureDisplay(int width, int height);
    ~TextureDisplay();

    TextureDisplay(const TextureDisplay&) = delete;
    TextureDisplay& operator=(const TextureDisplay&) = delete;

    void update(const std::vector<Color>& pixels);
    void draw();

private:
    GLuint compileShader(GLenum type, const char* source);
    GLuint createShaderProgram();

    void createTexture();
    void createQuad();

    int width;
    int height;

    GLuint texture;
    GLuint VAO;
    GLuint VBO;
    GLuint shaderProgram;
};