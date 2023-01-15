#include "sg/scenes/pong.hpp"

namespace sg::scenes
{

const char* Pong::SCENE_NAME = "Pong";

entt::entity create_paddle(entt::registry& reg)
{
  entt::entity ent = reg.create();

  return ent;
}

entt::entity create_ball(entt::registry& reg)
{
  entt::entity ent = reg.create();

  return ent;
}

Pong::Pong()
{
  ball = create_ball(reg);
  player1 = create_paddle(reg);
  player2 = create_paddle(reg);
}



// class Pong : public Scene
// {
//   entt::registry reg;
//   entt::entity player, enemy, ball;

// public:
//   static const char* SCENE_NAME;

//   Pong();

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
