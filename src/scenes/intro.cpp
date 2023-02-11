#include "intro.hpp"

#include <iostream>

namespace sg::scenes
{

Intro::Intro(sf::Time time, std::unique_ptr<Scene>&& next_scene)
: scene_time(time), next_scene(std::move(next_scene))
{
  font.loadFromFile("./assets/Work-Sans/fonts/ttf/WorkSans-Regular.ttf");
  text.setFont(font);
  text.setString("hello :)");
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::Black);
  text.setPosition(10,40);
  if(! this->next_scene)
  {
    std::cout << "error: no next scene set for Intro" << std::endl;
  }
}
;
Scene::EventResponse Intro::handle_event(const sf::Event&)
{
  return Scene::EventResponse::Continue;
}

void Intro::pre_update(Application& app)
{
  if(scene_begin_time.getElapsedTime() >= scene_time)
  {
    std::unique_ptr< Scene > scene = std::move(next_scene);
    app.replace_scene(std::move(scene));
    // app.replace_scene(std::move(next_scene));
  }
}

void Intro::update(const sf::Time&)
{
}

void Intro::render(sf::RenderTarget& target)
{
  target.clear(sf::Color::White);
  target.draw(text);
}

}
