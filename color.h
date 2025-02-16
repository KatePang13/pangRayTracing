#ifndef COLOR_H
#define COLOR_H

#include "rtweekend.h"

#include <iostream>

void write_color( std::ostream& out, color pixel_color ) {
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
    << static_cast<int>(255.999 * pixel_color.y()) << ' '
    << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

void write_color( std::ostream& out, color pixel_color, int samples_per_pixel ) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color total by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>(255.999 * clamp(r, 0.0, 0.999) ) << ' '
        << static_cast<int>(255.999 * clamp(g, 0.0, 0.999) ) << ' '
        << static_cast<int>(255.999 * clamp(b, 0.0, 0.999) ) << '\n';
}

#endif