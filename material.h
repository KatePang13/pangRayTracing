#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "vec3.h"
#include "hittable.h"

class meterial {
public:
    virtual bool scatter(const ray& r_in, hit_record& rec, color& attenuation, ray& sattered) const =0;
};

class lambertian : public meterial {
public:
    lambertian(const color& a) : albedo(a) {};
    virtual bool scatter(const ray& r_in, hit_record& rec, color& attenuation, ray& sattered) const {
        vec3 scatter_direction = rec.normal + random_unit_vector();
        sattered = ray( rec.p, scatter_direction );
        attenuation = albedo;
        return true;
    } 

public:
    color albedo;
};

class metal : public meterial {
public:
    metal(const color& a) : albedo(a), fuzz(1.0) {};
    metal(const color& a, double f) : albedo(a), fuzz(f<1 ? f:1) {};
    virtual bool scatter(const ray& r_in, hit_record& rec, color& attenuation, ray& sattered) const {
        vec3 reflect_direction = reflect( unit_vector(r_in.direction()), rec.normal );
        sattered = ray( rec.p, reflect_direction + fuzz*random_in_unit_sphere() );
        attenuation = albedo;
        return  dot(sattered.direction(), rec.normal) > 0;
    } 

public:
    color albedo;
    double fuzz;
};

#endif