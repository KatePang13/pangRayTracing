#include "vec3.h"
#include "color.h"
#include "ray.h"

#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>

color ray_color(const ray&r, const hittable& world) {
    hit_record rec;
    if( world.hit(r, 0, infinity, rec) ) {
        return 0.5* ( rec.normal + color(1,1,1));
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

    hittable_list world;
    world.add( make_shared<sphere>(point3(0,0,-1), 0.5) );
    world.add( make_shared<sphere>(point3(0,-100.5,-1), 100) );

    for( int j = image_height-1; j >=0; --j ) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i<image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            point3 pixel = lower_left_corner + u*horizontal + v*vertical;//屏幕上的点的二维坐标转换为三维坐标;
            vec3 direction = pixel - origin;//原点(视点)连到屏幕上一点，即是该点的光线方向;
            ray r(origin, direction);
            write_color(std::cout, ray_color(r, world) );
        }
    }
    std::cerr << "\nDone.\n";
    return 0;
}