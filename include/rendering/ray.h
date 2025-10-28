//
// Created by srira on 14-09-2025.
//

#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H

#include "core/vec3.h"

class ray {
  public:
    ray() {}

    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    const point3& origin() const  { return orig; }
    const vec3& direction() const { return dir; }

    point3 at(double t) const {
        return orig + t*dir;
    }

  private:
      point3 orig;
      vec3 dir;
};

#endif //RAY_TRACER_RAY_H
