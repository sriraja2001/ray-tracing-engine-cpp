#ifndef SPHERE_H
#define SPHERE_H

#include "core/hittable.h"

class sphere : public hittable {
  public:
    sphere(const point3 &center, const double radius) : center(center), radius(fmax(0, radius)) {}

    bool hit(const ray &r, const double ray_tmin, double ray_tmax, hit_record &rec) const override {
      // The function checks if the given ray hits the circle and also set the hit_record object 
      vec3 oc = center - r.origin();
      double a = r.direction().length_squared();
      double h = dot(r.direction(), oc);
      double c = oc.length_squared() - radius * radius;
      double discrim = (h * h) - (a * c);

      if (discrim < 0) return false; // The quadratic equation has no real roots, so the ray does not intersect the sphere
      double root = (h - sqrt(discrim)) / a; // Start with the closest root, if not in range, then check the other one 

      if(root <= ray_tmin || ray_tmax <= root) {
        root = (h + sqrt(discrim)) / a;
        if(root <= ray_tmin || ray_tmax <= root) return false;
      }

      rec.t = root;
      rec.p = r.at(rec.t);
      rec.normal = unit_vector(rec.p - center);

      return true;
    }

  private:
    point3 center;
    double radius;
};

#endif
