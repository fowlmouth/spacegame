#pragma once

#include "../scene.hpp"

#include "entt/entt.hpp"

namespace sg::scenes
{

class Intro : public Scene
{
  sf::Clock scene_begin_time;
  sf::Time scene_time;
  std::unique_ptr< Scene > next_scene;
  sf::Font font;
  sf::Text text;

public:
  Intro(sf::Time time, std::unique_ptr<Scene>&& next_scene);

  Scene::EventResponse handle_event(const sf::Event&) override;
  void pre_update(ApplicationInterface&) override;
  void update(const sf::Time&) override;
  void render(sf::RenderTarget&) override;

};

}
