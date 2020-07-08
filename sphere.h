#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
    sphere() {}
    sphere( point3 c, double r ) : center(c), radius(r) {};

    virtual bool hit( const ray& r, double t_min, double t_max, hit_record& rec) const;
    
public:
    point3 center;
    double radius;
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
    rec.normal = (rec.p - center) / radius;
    return true;
}

#endif