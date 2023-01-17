#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "components.hpp"

namespace sg
{

class DebugRenderer
{
  sf::RenderTarget& target;

public:
  DebugRenderer(sf::RenderTarget& render_target);

  void render(entt::registry&);

};

}