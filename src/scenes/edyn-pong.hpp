#pragma once

#include "pick-scene.hpp"

#include "edyn/edyn.hpp"

namespace sg::scenes
{

class EdynPong : Scene
{


public:
  static const char* SCENE_NAME;

  EdynPong();

  
  Scene::EventResponse handle_event(const sf::Event&) override;
  void update(const sf::Time&) override;
  void render(sf::RenderTarget&) override;


};

}
