#include "sg/scenes/pong.hpp"

#include "sg/hid-controller.hpp"


struct PlayerScore
{
  int score;
};


struct PaddleInputState
{
  float vertical_move;
};

constexpr int PaddleMoveSpeed = 10000.f;

using PaddleController = sg::hid::Controller< PaddleInputState >;
using PaddleControllerConfiguration = sg::hid::ControllerConfiguration;

using PaddleControllerManager = sg::hid::ControllerManager< PaddleInputState >;



void create_paddle_controller_configurations(PaddleControllerManager& controller_manager)
{
  {
    auto kbd = std::make_shared< PaddleControllerConfiguration >(2);

    auto& btn1 = kbd->actions.at(0);
    btn1.button = sg::hid::Button{ sg::hid::Button::Key, sf::Keyboard::Key::Up };
    btn1.type = sg::hid::ButtonValueMapper::BoolToLowFloat;
    btn1.offset = offsetof(PaddleInputState, vertical_move);

    auto& btn2 = kbd->actions.at(1);
    btn2.button = sg::hid::Button{ sg::hid::Button::Key, sf::Keyboard::Key::Down };
    btn2.type = sg::hid::ButtonValueMapper::BoolToHighFloat;
    btn2.offset = offsetof(PaddleInputState, vertical_move);

    controller_manager.controllers.push_back(PaddleControllerManager::EntityController{ "Keyboard Right", entt::null, kbd });
  }
  {
    auto kbd = std::make_shared< PaddleControllerConfiguration >(2);

    auto& btn1 = kbd->actions.at(0);
    btn1.button = sg::hid::Button{ sg::hid::Button::Key, sf::Keyboard::Key::Up };
    btn1.type = sg::hid::ButtonValueMapper::BoolToLowFloat;
    btn1.offset = offsetof(PaddleInputState, vertical_move);

    auto& btn2 = kbd->actions.at(1);
    btn2.button = sg::hid::Button{ sg::hid::Button::Key, sf::Keyboard::Key::Down };
    btn2.type = sg::hid::ButtonValueMapper::BoolToHighFloat;
    btn2.offset = offsetof(PaddleInputState, vertical_move);

    controller_manager.controllers.push_back(PaddleControllerManager::EntityController{ "Keyboard Left", entt::null, kbd });
  }
  {
    auto mwheel = std::make_shared< PaddleControllerConfiguration >(1);

    auto& btn1 = mwheel->actions.at(0);
    btn1.button = sg::hid::Button{ sg::hid::Button::MouseWheel, sf::Mouse::Wheel::VerticalWheel };
    btn1.type = sg::hid::ButtonValueMapper::Float;
    btn1.offset = offsetof(PaddleInputState, vertical_move);

    controller_manager.controllers.push_back(PaddleControllerManager::EntityController{ "MouseWheel", entt::null, mwheel });
  }
}

struct fail{};

namespace sg::scenes
{

const char* Pong::SCENE_NAME = "Pong";

Material default_material{
  .fill_color = sf::Color::White
};

entt::entity create_paddle(entt::registry& reg)
{
  entt::entity ent = reg.create();
  auto& mesh = reg.get_or_emplace< Mesh >(ent);
  mesh.set_rectangle(sf::Vector2f(0,0), 10, 50);

  auto& mat = reg.get_or_emplace< Material >(ent, default_material);
  // mat.fill_color = sf::Color::White;

  reg.emplace< Velocity >(ent, 0.f, 0.f, 0.f);

  return ent;
}

entt::entity create_ball(entt::registry& reg)
{
  entt::entity ent = reg.create();

  auto& mesh = reg.get_or_emplace< Mesh >(ent);
  mesh.set_circle(sf::Vector2f(0,0), 16, 5.f);

  auto& mat = reg.get_or_emplace< Material >(ent, default_material);
  // mat.fill_color = sf::Color::White;

  return ent;
}

void reset_objects(entt::registry& reg, entt::entity ball,
  entt::entity player1, entt::entity player2, sf::Vector2u screen_size)
{
  reg.emplace_or_replace< Transform >(ball, (float)(screen_size.x/2), (float)(screen_size.y/2), 0.f);
  reg.emplace_or_replace< Transform >(player1,
    5.f, (float)(screen_size.y/2), 0.f);
  reg.emplace_or_replace< Transform >(player2,
    (float)(screen_size.x) - 5.f, (float)(screen_size.y/2), 0.f);
}


Pong::Pong()
: ball(entt::null), player1(entt::null), player2(entt::null)
{
  auto& controller_manager = reg.ctx().emplace< PaddleControllerManager >();
  create_paddle_controller_configurations(controller_manager);

  editor.registerComponent< components::Transform >("Transform");
}

void Pong::on_enter(Application& app)
{
  if(ball == entt::null)
    ball = create_ball(reg);
  if(player1 == entt::null)
    player1 = create_paddle(reg);
  if(player2 == entt::null)
    player2 = create_paddle(reg);
  reset_objects(reg, ball, player1, player2, app.get_window_size());

  auto& controller_manager = reg.ctx().get< PaddleControllerManager >();
  if(!controller_manager.claim(2, reg, player1))
  {
    std::cout << "Failed to claim a controller" << std::endl;
    throw fail{};
  }
}

Scene::EventResponse Pong::handle_event(const sf::Event&)
{
  return Scene::EventResponse::Continue;
}

void Pong::pre_update(Application& app)
{
  auto& controller_manager = reg.ctx().get< PaddleControllerManager >();
  controller_manager.update(reg);
}

void Pong::update(const sf::Time& dt)
{
  auto dt_seconds = dt.asSeconds();

  auto input_objects = reg.view< PaddleInputState, Velocity >();
  for(auto ent : input_objects)
  {
    auto& input_state = input_objects.get< PaddleInputState >(ent);
    auto& velocity = input_objects.get< Velocity >(ent);
    velocity.vy = input_state.vertical_move * PaddleMoveSpeed * dt_seconds;
  }

  auto velocity_objects = reg.view< Transform, Velocity >();
  for(auto ent : velocity_objects)
  {
    auto& transform = velocity_objects.get< Transform >(ent);
    auto& velocity = velocity_objects.get< Velocity >(ent);
    transform.x += velocity.vx * dt_seconds;
    transform.y += velocity.vy * dt_seconds;
    transform.radians += velocity.angular * dt_seconds;
  }

}

void Pong::render(sf::RenderTarget& target)
{
  DebugRenderer renderer;
  renderer.render(target, reg);

  if(ball != entt::null)
    editor.renderSimpleCombo(reg, ball);
}

}
