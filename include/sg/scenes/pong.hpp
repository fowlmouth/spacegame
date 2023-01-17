#pragma once

#include "../scene.hpp"
#include "../application.hpp"
#include "../components.hpp"

#include "../debug-renderer.hpp"

#include "entt/entt.hpp"

namespace sg::scenes
{

class Pong : public Scene
{
  entt::registry reg;
  entt::entity player1, player2, ball;

public:
  static const char* SCENE_NAME;

  Pong();

  Scene::EventResponse handle_event(const sf::Event&) override;
  void update(const sf::Time&) override;
  void render(sf::RenderTarget&) override;

  void on_enter(Application&) override;
};

}
