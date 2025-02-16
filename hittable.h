#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
class material;

struct hit_record {
    point3 p;       //交点处-坐标;
    vec3 normal;    //交点处-平面法线;
    double t;       //交点处-光线t值;
    bool front_face;//朝向
    shared_ptr<material> material_ptr;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot( r.direction(), outward_normal ) < 0 ;
        normal = front_face ? outward_normal : ~outward_normal ;
    }

};



class hittable {
public:
    virtual bool hit( const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif