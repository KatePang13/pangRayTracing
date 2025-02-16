#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
    sphere() {}
    sphere( point3 c, double r, shared_ptr<material> m ) 
        : center(c), radius(r), material_ptr(m) {};

    virtual bool hit( const ray& r, double t_min, double t_max, hit_record& rec) const;
    
public:
    point3 center;
    double radius;
    shared_ptr<material> material_ptr;
};

bool sphere::hit( const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if( discriminant <=0 ) {
        return false;
    }

    auto root = sqrt( discriminant );
    auto t = (-half_b - root) / a;
    if( t<=t_min || t >= t_max ) {
        t = (-half_b + root);
        if( t<=t_min || t >= t_max ) {
            return false;
        }
    }

    rec.t = t;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.material_ptr = material_ptr;
    return true;
}

#endif