#pragma once

#include "../scene.hpp"

#include "entt/entt.hpp"

namespace sg::scenes
{

class Main : public Scene
{
  entt::registry reg;

public:
  static const char* SCENE_NAME;

  Main();

  Scene::EventResponse handle_event(const sf::Event&) override;
  void update(const sf::Time&) override;
  void render(sf::RenderTarget&) override;

};

}
