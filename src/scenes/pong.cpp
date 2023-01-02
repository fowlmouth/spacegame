#include "sg/scenes/pong.hpp"

namespace sg::scenes
{

const char* Pong::SCENE_NAME = "Pong";

Pong::Pong()
{
  ball = reg.create();

  player = reg.create();

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
