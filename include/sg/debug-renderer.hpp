#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "components.hpp"
#include "components/graphical.hpp"

#include <vector>

namespace sg
{

class DebugRenderer
{
  components::Material default_material;
  sf::Clock scene_time;

public:
  DebugRenderer();

  void render(sf::RenderTarget&, entt::registry&);

};

}
