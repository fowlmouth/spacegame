#pragma once

#include "../scene.hpp"
#include "../application.hpp"
#include "../components.hpp"
#include "../hid-controller.hpp"
#include "../debug-renderer.hpp"

#include "entt/entt.hpp"
#include "imgui.h"
#include "imgui_entt_entity_editor.hpp"

#include <algorithm>

namespace sg::scenes
{

class Pong : public Scene
{

public:
  struct PaddleInputState
  {
    float vertical_move;
  };

  using PaddleControllerManager = sg::hid::ControllerManager< PaddleInputState >;

private:
  enum class State
  {
    Idle, Demo, Complete, Active
  };
  State state;
  float demo_time_seconds;

  entt::registry reg;
  entt::entity player1, player2, ball;
  MM::EntityEditor< entt::entity > editor;
  sf::Vector2u window_size;
  PaddleControllerManager controller_manager;

  void set_state(State new_state);
  void destroy_ball();

  void reset_ball();
  void reset_score();
  void reset_paddles();

  void set_computer_controller(entt::entity);

public:
  static const char* SCENE_NAME;

  Pong();

  Scene::EventResponse handle_event(const sf::Event&) override;
  void update(const sf::Time&) override;
  void render(sf::RenderTarget&) override;

  void pre_update(Application&) override;
  void on_enter(Application&) override;
};

}
