#pragma once

#include <SFML/Graphics.hpp>
#include "application-interface.hpp"
#include <memory>
#include <stack>

namespace sg
{

class Application : public ApplicationInterface
{
  sf::RenderWindow window;
  sf::Clock fps;
  std::stack< std::unique_ptr< Scene >> scene_stack;

  Scene* current_scene() const;

public:
  Application();
  ~Application();

  int run();

  sf::Vector2u get_window_size() const override;
  void set_window_size(sf::Vector2u) override;
  void replace_scene(std::unique_ptr< Scene >&&) override;
  void push_scene(std::unique_ptr< Scene >&&) override;
  void pop_scene() override;
  void set_window_title(const char* title) override;
};

}
