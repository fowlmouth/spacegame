#pragma once

#include "pick-scene.hpp"

#include "imgui.h"

namespace sg::scenes
{

struct ImguiTest : PickableScene
{
  static const char* SCENE_NAME;

  sg::Scene::EventResponse handle_event(const sf::Event&) override;
  void update(const sf::Time&) override;
  void render(sf::RenderTarget&) override;


};

}