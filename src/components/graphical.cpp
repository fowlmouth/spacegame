#include "sg/components/graphical.hpp"

namespace sg::components
{

sf::Vector2f rotate(const sf::Vector2f& vector, float angle_radians)
{
  float x = vector.x * std::cos(angle_radians) - vector.y * std::sin(angle_radians);
  float y = vector.x * std::sin(angle_radians) + vector.y * std::cos(angle_radians);
  return sf::Vector2f(x, y);
}

void VisualEffect::apply(sf::Drawable* drawable, sf::Transformable* transformable, float scene_time_seconds) const
{
  switch(type)
  {
  case VisualEffect::SinOffset:
    if(transformable)
    {
      sf::Vector2f offset = rotate(sf::Vector2f(0, std::sin(scene_time_seconds)) * arg[1], arg[0]);
      transformable->setPosition(transformable->getPosition() + offset);
    }
    break;

  default:
    break;
  }
}

VisualEffect VisualEffect::sin_offset(float angle_radians, float distance, float time_offset)
{
  return VisualEffect{ .type= VisualEffect::SinOffset, .arg = { angle_radians, distance, time_offset } };
}

}
