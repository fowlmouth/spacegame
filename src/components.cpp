#include "sg/components.hpp"

#include <cmath>

namespace sg
{

void Mesh::set_circle(sf::Vector2f center, int point_count, float radius)
{
  points.resize(point_count);
  const double angle_increment = 2 * M_PI / point_count;
  for(int i = 0; i < point_count; ++i)
  {
    const double angle = i * angle_increment;
    points[i] = sf::Vector2f(
      center.x + radius * std::cos(angle),
      center.y + radius * std::sin(angle));
  }

}

}
