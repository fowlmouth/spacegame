#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>

namespace sg
{

class Scene;

class Application
{
  sf::RenderWindow window;
  sf::Clock fps;
  std::stack< std::unique_ptr< Scene >> scene_stack;
  sf::Vector2u window_size;

  Scene* current_scene() const;

public:
  Application();
  ~Application();

  int run();

  sf::Vector2u get_window_size() const;
  void set_window_size(sf::Vector2u);
  void replace_scene(std::unique_ptr< Scene >&&);
  void push_scene(std::unique_ptr< Scene >&&);
  void pop_scene();
  void set_window_title(const char* title);
};

}
