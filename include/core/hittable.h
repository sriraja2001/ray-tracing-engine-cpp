#ifndef HITTABLE_H
#define HITTABLE_H

#include "rendering/ray.h" 

class hit_record {
  public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray &r, const vec3 &outward_normal) {
      double dot_prd = dot(r.direction(), outward_normal);
      // If the dot product of the ray and the outward normal is negative, then the ray strikes the outside face of the shape
      // Else, the ray strikes the inward face of the shape; in this case, reverse the normal, since the normal is always against the direction of the ray
      front_face = dot_prd < 0;
      normal = front_face ? outward_normal : -outward_normal;
    }
}

class hittable {
  public:
    virtual ~hittable() = default;
    virtual bool hit(const ray &r, const double ray_tmin, const double ray_tmax, hit_record &rec) const  = 0;
}

#endif
