#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "vec3.h"
#include "hittable.h"

class meterial {
public:
    virtual bool scatter(const ray& r_in, hit_record& rec, color& attenuation, ray& sattered) const =0;
};

#endif