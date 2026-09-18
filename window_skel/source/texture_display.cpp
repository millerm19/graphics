#include "texture_display.hpp"

#include <iostream>
#include <stdexcept>

// Vertex shader
static const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);

    TexCoord = aTexCoord;
}
)";

// Fragment shader
static const char* fragmentShaderSource = R"(
#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D screenTexture;

void main()
{
    FragColor = texture(screenTexture, TexCoord);
}
)";

TextureDisplay::TextureDisplay(int width, int height)
    : width(width),
      height(height),
      texture(0),
      VAO(0),
      VBO(0),
      shaderProgram(0)
{
    createTexture();
    createQuad();

    shaderProgram = createShaderProgram();
}

TextureDisplay::~TextureDisplay()
{
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

void TextureDisplay::createTexture()
{
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_NEAREST
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_NEAREST
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_CLAMP_TO_EDGE
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_CLAMP_TO_EDGE
    );

    // Allocate GPU texture memory
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB8,
        width,
        height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        nullptr
    );

    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureDisplay::createQuad()
{
    // Two triangles forming a rectangle.
    //
    // Position        Texture coordinate
    //
    // (-1, -1)         (0, 1)
    // ( 1, -1)         (1, 1)
    // ( 1,  1)         (1, 0)
    //
    // (-1, -1)         (0, 1)
    // ( 1,  1)         (1, 0)
    // (-1,  1)         (0, 0)

    float vertices[] =
    {
        // Position       Texture coordinates
        -1.0f, -1.0f,      0.0f, 1.0f,
         1.0f, -1.0f,      1.0f, 1.0f,
         1.0f,  1.0f,      1.0f, 0.0f,

        -1.0f, -1.0f,      0.0f, 1.0f,
         1.0f,  1.0f,      1.0f, 0.0f,
        -1.0f,  1.0f,      0.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    // Position attribute
    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),
        (void*)nullptr
    );

    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),
        (void*)(2 * sizeof(float))
    );

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

GLuint TextureDisplay::compileShader(
    GLenum type,
    const char* source
)
{
    GLuint shader = glCreateShader(type);

    glShaderSource(
        shader,
        1,
        &source,
        nullptr
    );

    glCompileShader(shader);

    GLint success = 0;

    glGetShaderiv(
        shader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[512];

        glGetShaderInfoLog(
            shader,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr << "Shader compilation failed:\n"
                  << infoLog
                  << '\n';

        glDeleteShader(shader);

        throw std::runtime_error(
            "Failed to compile shader"
        );
    }

    return shader;
}

GLuint TextureDisplay::createShaderProgram()
{
    GLuint vertexShader = compileShader(
        GL_VERTEX_SHADER,
        vertexShaderSource
    );

    GLuint fragmentShader = compileShader(
        GL_FRAGMENT_SHADER,
        fragmentShaderSource
    );

    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint success = 0;

    glGetProgramiv(
        program,
        GL_LINK_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[512];

        glGetProgramInfoLog(
            program,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr << "Shader linking failed:\n"
                  << infoLog
                  << '\n';

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(program);

        throw std::runtime_error(
            "Failed to link shader program"
        );
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void TextureDisplay::update(
    const std::vector<Color>& pixels
)
{
    glBindTexture(GL_TEXTURE_2D, texture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        0,
        0,
        width,
        height,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        pixels.data()
    );

    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureDisplay::draw()
{
    glUseProgram(shaderProgram);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, texture);

    GLint textureLocation = glGetUniformLocation(
        shaderProgram,
        "screenTexture"
    );

    glUniform1i(textureLocation, 0);

    glBindVertexArray(VAO);

    glDrawArrays(
        GL_TRIANGLES,
        0,
        6
    );

    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
}