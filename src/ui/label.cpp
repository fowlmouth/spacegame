#include "sg/ui/label.hpp"

#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>


namespace sg::ui
{

Label::Label(const std::string& str)
{
  text.setString(str);
}

void Label::render(sf::RenderTarget& target)
{
  if(_dirty)
  {
    update();
    update_bounds();
  }

  sf::RectangleShape rect;
  rect.setPosition(_global_bounds.left, _global_bounds.top);
  rect.setSize({_global_bounds.width, _global_bounds.height});
  rect.setFillColor(sf::Color::Transparent);
  rect.setOutlineColor(sf::Color::White);
  rect.setOutlineThickness(1.5f);
  target.draw(rect);

  text.setPosition(_global_bounds.left, _global_bounds.top);
  target.draw(text);

  // std::cout << "render " << text.getString().toAnsiString() << std::endl
  //   << "  x= " << text.getPosition().x << "  y= " << text.getPosition().y << std::endl
  //   << "  local= " << _local_bounds << "  global= " << _global_bounds << std::endl;
}

void Label::update()
{
  auto this_style = style();
  text.setPosition(_local_bounds.left, _local_bounds.top);
  if(const auto font_ref = this_style->font)
  {
    text.setFont(*font_ref);
  }
  text.setCharacterSize(this_style->font_size);
  text.setFillColor(this_style->foreground);
  _local_bounds.height = text.getLocalBounds().height;
  _local_bounds.width = text.getLocalBounds().width;
  _dirty = false;
}

}
