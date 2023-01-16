#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

namespace sg
{

struct Transform
{
  float x, y, radians;
};

struct Velocity
{
  float vx, vy, angular;
};

struct Mesh
{
  std::vector< sf::Vector2f > points;
  sf::Vector2f center;

  void set_circle(sf::Vector2f center, int point_count, float radius);
  void set_radial_polygon(sf::Vector2f center, int point_count, float radius, float start_offset_radians);
  void set_box(sf::Vector2f center, float width);
  void set_rectangle(sf::Vector2f center, float width, float height);
};

struct Material
{
  std::shared_ptr< sf::Texture > texture;
  sf::Color fill_color, outline_color;
  float outline_thickness;
};

}
