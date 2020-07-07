#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>

bool hit_spehre(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center; 
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    return (b*b - 4*a*c > 0);
}

/*
The ray_color(ray) function linearly blends white and blue depending on 
the height of the y coordinate after scaling the ray direction to unit length (so −1.0<y<1.0). 
Because we're looking at the y height after normalizing the vector, 
you'll notice a horizontal gradient to the color in addition to the vertical gradient.
*/
color ray_color(const ray&r) {
    if( hit_spehre(point3(0, 0, -1), 0.5, r) ) {
        return color(1, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 384;
    const int image_height = static_cast<int>(image_width/aspect_ratio);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    auto viewport_height = 2.0;
    auto viewport_weight = aspect_ratio*viewport_height;
    auto focal_length = 1.0;
    
    auto origin = point3(0, 0, 0); 
    auto horizontal = vec3(viewport_weight, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    for( int j = image_height-1; j >=0; --j ) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i<image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            point3 pixel = lower_left_corner + u*horizontal + v*vertical;//屏幕上的点的二维坐标转换为三维坐标;
            vec3 direction = pixel - origin;//原点(视点)连到屏幕上一点，即是该点的光线方向;
            ray r(origin, direction);
            write_color(std::cout, ray_color(r) );
        }
    }
    std::cerr << "\nDone.\n";
    return 0;
}