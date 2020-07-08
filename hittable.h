#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
    point3 p;       //交点处-坐标;
    vec3 normal;    //交点处-平面法线;
    double t;       //交点处-光线t值;
};

class hittable {
public:
    virtual bool hit( const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
}

#endif