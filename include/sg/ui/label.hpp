#pragma once

#include "element.hpp"

namespace sg::ui
{

class Label : public Element
{
public:
  sf::Text text;

  Label(const std::string& text);

  void render(sf::RenderTarget&);
  void update();
};

}
