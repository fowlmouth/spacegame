#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace sg
{

class Application;

class Scene
{

public:

  virtual ~Scene();

  enum class EventResponse
  {
    Continue, Close
  };

  virtual EventResponse handle_event(const sf::Event&) = 0;
  virtual void update(const sf::Time&) = 0;
  virtual void render(sf::RenderTarget&) = 0;

  // Called before each update phase
  virtual void pre_update(Application&);

  // Called after each update phase
  virtual void post_update(Application&);

  // Called after each render phase
  virtual void post_render(Application&);

  // Called when the scene is entered
  virtual void on_enter(Application&);

  // Called when the scene is left
  virtual void on_leave(Application&);

};
}
