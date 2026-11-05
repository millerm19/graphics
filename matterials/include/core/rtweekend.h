#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <random>



const float infinity = std:: numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385f;

inline float degrees_to_radians(float degrees) {
    return degrees* pi / 180.f;
}

inline float random_float() {
    return float(std::rand()) / (RAND_MAX + 1.0f);
}

inline float random_float(float min, float max) {
    return min + (max-min)*random_float();
}

using std::make_shared;
using std::shared_ptr;


#endif