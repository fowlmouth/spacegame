#include "sg/scenes/pong.hpp"

namespace sg::scenes
{

const char* Pong::SCENE_NAME = "Pong";

entt::entity create_paddle(entt::registry& reg)
{
  entt::entity ent = reg.create();
  auto& mesh = reg.get_or_emplace< Mesh >(ent);
  mesh.set_rectangle(sf::Vector2f(0,0), 10, 50);

  auto& mat = reg.get_or_emplace< Material >(ent);
  mat.fill_color = sf::Color::White;

  return ent;
}

entt::entity create_ball(entt::registry& reg)
{
  entt::entity ent = reg.create();

  auto& mesh = reg.get_or_emplace< Mesh >(ent);
  mesh.set_circle(sf::Vector2f(0,0), 16, 5.f);

  auto& mat = reg.get_or_emplace< Material >(ent);
  mat.fill_color = sf::Color::White;

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
}

Scene::EventResponse Pong::handle_event(const sf::Event&)
{
  return Scene::EventResponse::Continue;
}

void Pong::update(const sf::Time& dt)
{
  auto dt_seconds = dt.asSeconds();
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
  DebugRenderer renderer(target);
  renderer.render(reg);
}

}
