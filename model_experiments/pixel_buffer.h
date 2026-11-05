#ifndef PIXEL_BUFFER_H
#define PIXEL_BUFFER_H

#include <vector>
#include "color.h"

class pixel_buffer {
public:
    pixel_buffer() : image_width(0), image_height(0) {}
    
    pixel_buffer(int width, int height) : image_width(width), image_height(height),
          pixels(width * height * 3, 0) {}

    void set_pixel(int x, int y, const color& pixel_color) {
        int index = (y * image_width + x) * 3;

        pixels[index + 0] = static_cast<unsigned char>(255.999 * linear_to_gamma(pixel_color.x()));
        pixels[index + 1] = static_cast<unsigned char>(255.999 * linear_to_gamma(pixel_color.y()));
        pixels[index + 2] = static_cast<unsigned char>(255.999 * linear_to_gamma(pixel_color.z()));
    }

    int width() const { return image_width; }
    int height() const { return image_height; }

    const unsigned char* data() const {
        return pixels.data();
    }

    int bytes_per_row() const {
        return image_width * 3;
    }

private:
    int image_width;
    int image_height;
    std::vector<unsigned char> pixels;
};

#endif