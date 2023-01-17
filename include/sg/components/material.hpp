#pragma once

#include <SFML/Graphics.hpp>

namespace sg::components
{

struct Material
{
  std::shared_ptr< sf::Texture > texture;
  sf::Color fill_color, outline_color;
  float outline_thickness;
};

}
