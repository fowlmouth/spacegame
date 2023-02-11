#include "components.hpp"

#include <cmath>

namespace sg::components
{

void Mesh::set_circle(sf::Vector2f center, int point_count, float radius)
{
  set_radial_polygon(center, point_count, radius, 0.f);
}

void Mesh::set_radial_polygon(sf::Vector2f center, int point_count, float radius, float start_offset_radians)
{
  points.resize(point_count);
  const double angle_increment = 2 * M_PI / point_count;
  for(int i = 0; i < point_count; ++i)
  {
    const double angle = i * angle_increment + start_offset_radians;
    points[i] = sf::Vector2f(
      center.x + radius * std::cos(angle),
      center.y + radius * std::sin(angle));
  }
  this->center = center;
}

void Mesh::set_box(sf::Vector2f center, float width)
{
  set_radial_polygon(center, 4, width / 2, M_PI / 2);
}

void Mesh::set_rectangle(sf::Vector2f center, float width, float height)
{
  points.resize(4);
  points[0] = { center.x + width / 2, center.y - height / 2 };
  points[1] = { center.x - width / 2, center.y - height / 2 };
  points[2] = { center.x - width / 2, center.y + height / 2 };
  points[3] = { center.x + width / 2, center.y + height / 2 };
  this->center = center;
}

}
