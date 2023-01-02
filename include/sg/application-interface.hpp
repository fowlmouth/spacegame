#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

namespace sg
{

class Scene;

class ApplicationInterface
{
public:
  virtual sf::Vector2u get_window_size() const = 0;
  virtual void set_window_size(sf::Vector2u) = 0;
  virtual void set_window_title(const char*) = 0;
  virtual void replace_scene(std::unique_ptr< Scene >&&) = 0;
  virtual void push_scene(std::unique_ptr< Scene >&&) = 0;
  virtual void pop_scene() = 0;
};

}
