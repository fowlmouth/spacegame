#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

namespace sg::components
{

struct VisualEffect
{
  enum{
    None, SinOffset
  } type;
  float arg[6];

  static VisualEffect sin_offset(float angle_radians, float distance, float time_offset);

  void apply(sf::Drawable*, sf::Transformable*, float) const;
};

struct VisualEffectQueue
{
  std::vector< VisualEffect > effects;
};

}
