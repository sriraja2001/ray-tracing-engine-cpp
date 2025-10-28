//
// Created by srira on 14-09-2025.
//

#ifndef RAY_TRACER_COLOR_H
#define RAY_TRACER_COLOR_H

#include "vec3.h"

#include <iostream>

using color = vec3;

void write_color(std::ofstream& out, const color& pixel_color) {
  const auto r = pixel_color.x();
  const auto g = pixel_color.y();
  const auto b = pixel_color.z();

  // Translate the [0,1] component values to the byte range [0,255].
  const int rByte = static_cast<int>(255.999 * r);
  const int gByte = static_cast<int>(255.999 * g);
  const int bByte = static_cast<int>(255.999 * b);

  // Write out the pixel color components.
  out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}


#endif //RAY_TRACER_COLOR_H
