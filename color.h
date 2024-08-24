#ifndef COLOR_H
#define COLOR_H

#include "raytracer.h"
#include "vec3.h"
#include "interval.h"

using color = vec3; // alias for RGB color

void write_color(std::ostream &out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // translate from [0,1] to [0,255]

    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));
    
    // write the translated values to the output stream

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif