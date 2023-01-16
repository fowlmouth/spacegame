#include "sg/scenes/pong.hpp"
#include "sg/components.hpp"

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

Pong::Pong()
{
  ball = create_ball(reg);
  player1 = create_paddle(reg);
  player2 = create_paddle(reg);
}


Scene::EventResponse Pong::handle_event(const sf::Event&)
{
  return Scene::EventResponse::Continue;
}
void Pong::update(const sf::Time&)
{
}
void Pong::render(sf::RenderTarget&)
{

}

}
