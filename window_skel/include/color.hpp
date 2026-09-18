#pragma once

struct Color
{
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
};

static_assert(sizeof(Color) == 3);