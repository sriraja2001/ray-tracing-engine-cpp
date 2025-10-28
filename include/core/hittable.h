#ifndef HITTABLE_H
#tjefine HITTABLE_H

#include "rendering/ray.h" 

class hit_record {
  public:
    point3 p;
    vec3 normal;
    double t;
}

class hittable {
  public:
    virtual ~hittable() = default;
    virtual bool hit(const ray &r, double ray_tmin, double ray_tmax, const hit_record &rec) const  = 0;
}
#endif
