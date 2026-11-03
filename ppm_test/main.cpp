#include "vec3.h"
#include "color.h"

#include <iostream>

int main() {

    // Image

    float aspect_ratio = 16.f / 9.f;
    float image_width = 400.f;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    float viewport_height = 2.f;
    float viewport_width = viewport_height * (float(image_width)/image_height);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {

            auto pixel_color = color(0, 0, 0);

            if((int((i/24)+(j/24)) % 2) == 1) {
                pixel_color = color(256, 256, 256);
            }

            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.       \n";
}