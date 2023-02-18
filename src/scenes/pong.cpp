#include "pong.hpp"

// Components

struct PlayerScore
{
  int score;
};

struct PaddleInputState
{
  float vertical_move;
};

static constexpr float DEMO_TIME_SECONDS = 1.5f;

constexpr int PaddleMoveSpeed = 10000.f;

using HumanController = sg::hid::Controller< PaddleInputState >;

using PaddleControllerConfiguration = sg::hid::ControllerConfiguration;

using PaddleControllerManager = sg::hid::ControllerManager< PaddleInputState >;

struct ComputerController
{
};

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

  reg.emplace< Velocity >(ent, 0.f, 0.f, 0.f);

  return ent;
}

entt::entity create_ball(entt::registry& reg)
{
  entt::entity ent = reg.create();

  auto& mesh = reg.get_or_emplace< Mesh >(ent);
  mesh.set_circle(sf::Vector2f(0,0), 16, 5.f);

  auto& mat = reg.get_or_emplace< Material >(ent, default_material);

  return ent;
}


Pong::Pong()
: state(Pong::State::Idle), ball(entt::null), player1(entt::null), player2(entt::null)
{
  auto& controller_manager = reg.ctx().emplace< PaddleControllerManager >();
  create_paddle_controller_configurations(controller_manager);

  editor.registerComponent< components::Transform >("Transform");
  editor.registerComponent< components::Material >("Material");
  editor.registerComponent< components::Mesh >("Mesh");
  // editor.registerComponent< components::Transform >("Transform");

}

void Pong::destroy_ball()
{
  if(ball != entt::null)
  {
    reg.destroy(ball);
    ball = entt::null;
  }
}

sf::Vector2f ball_directions[4] = {
  { 1.f,  1.f},
  {-1.f,  1.f},
  {-1.f, -1.f},
  { 1.f, -1.f}
};

void Pong::reset_ball()
{
  if(ball == entt::null)
  {
    ball = create_ball(reg);
  }
  auto& transform = reg.emplace_or_replace< Transform >(ball, (float)(window_size.x)/2, (float)(window_size.y)/2, 0.f);
  auto pos = ball_directions[ rand() & 0b11 ];
  auto& velocity = reg.emplace_or_replace< Velocity >(ball, pos.x, pos.y, 0.f);
}

void Pong::reset_score()
{
}

void Pong::reset_paddles()
{
  if(player1 == entt::null)
    player1 = create_paddle(reg);
  if(player2 == entt::null)
    player2 = create_paddle(reg);

  reg.emplace_or_replace< Transform >(player1,
    5.f, (float)(window_size.y)/2, 0.f);
  reg.emplace_or_replace< Transform >(player2,
    (float)(window_size.x) - 5.f, (float)(window_size.y)/2, 0.f);
}

void Pong::set_computer_controller(entt::entity paddle)
{
  reg.remove< HumanController >(paddle);
  reg.emplace< ComputerController >(paddle);
}

void Pong::set_state(Pong::State new_state)
{
  std::cout << "Pong: set_state new_state= " << (int)new_state << std::endl;

  switch(new_state)
  {
  case Pong::State::Idle:
    destroy_ball();
    demo_time_seconds = DEMO_TIME_SECONDS;
    break;

  case Pong::State::Demo:
  {
    // reset objects and add computer controllers
    reset_score();
    reset_ball();
    reset_paddles();
    set_computer_controller(player1);
    set_computer_controller(player2);

    break;
  }

  default:
    break;

  }
  state = new_state;
  // reset_objects(reg, ball, player1, player2, app.get_window_size());
}

void Pong::on_enter(Application& app)
{
  window_size = app.get_window_size();
  set_state(Pong::State::Demo);

  auto& controller_manager = reg.ctx().get< PaddleControllerManager >();
  if(!controller_manager.claim(2, reg, player1))
  {
    std::cout << "Failed to claim a controller" << std::endl;
    throw fail{};
  }
}

Scene::EventResponse Pong::handle_event(const sf::Event& event)
{
  if(event.type == sf::Event::KeyPressed)
  {
    if(event.key.code == sf::Keyboard::Key::Escape)
    {
      return Scene::EventResponse::Close;
    }
  }
  return Scene::EventResponse::Continue;
}

void Pong::pre_update(Application& app)
{
  auto& controller_manager = reg.ctx().get< PaddleControllerManager >();
  controller_manager.update(reg);

  if(ball != entt::null)
  {
    auto ball_position = reg.get< components::Transform >(ball);

    auto computer_controllers = reg.view< ComputerController, Transform, PaddleInputState >();
    for(auto ent : computer_controllers)
    {
      auto& transform = computer_controllers.get< Transform >(ent);
      auto& input_state = computer_controllers.get< PaddleInputState >(ent);

      if(ball_position.y > transform.y)
      {
        input_state.vertical_move = 1.f;
      }
      else if(ball_position.y < transform.y)
      {
        input_state.vertical_move = -1.f;
      }
    }
  }

  window_size = app.get_window_size();
}

void Pong::update(const sf::Time& dt)
{
  auto dt_seconds = dt.asSeconds();

  if(state == Pong::State::Idle)
  {
    demo_time_seconds -= dt_seconds;
    if(demo_time_seconds <= 0.f)
    {
      set_state(Pong::State::Demo);
    }
  }

  auto input_objects = reg.view< PaddleInputState, Velocity >();
  for(auto ent : input_objects)
  {
    auto& input_state = input_objects.get< PaddleInputState >(ent);
    auto& velocity = input_objects.get< Velocity >(ent);
    velocity.vy = std::clamp(input_state.vertical_move, -1.f, 1.f) * PaddleMoveSpeed * dt_seconds;
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

  // if(ball != entt::null)
  //   editor.renderSimpleCombo(reg, ball);
}

}
