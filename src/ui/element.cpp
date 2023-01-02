#include "sg/ui/element.hpp"
#include "sg/ui/container.hpp"

namespace sg::ui
{

Element::~Element()
{
}

Element::Element()
{
}

StyleRef Element::style() const
{
  if(_style)
    return _style;
  if(_parent)
    return _parent->style();
  return {};
}

void Element::set_style(StyleRef new_style)
{
  _style = new_style;
}

ContainerRef Element::parent() const
{
  return _parent;
}

void Element::set_parent(ContainerRef new_parent)
{
  if(_parent)
    throw Element::ParentExists{};
  _parent = new_parent;
}


bool Element::is_dirty() const
{
  return _dirty;
}

void Element::set_local_position(float x, float y)
{
  _local_bounds.left = x;
  _local_bounds.top = y;
  _dirty = true;
}

sf::FloatRect Element::local_bounds() const
{
  return _local_bounds;
}

sf::FloatRect Element::global_bounds() const
{
  return _global_bounds;
}

void Element::update()
{
}

sf::FloatRect intersection(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
  // Find the intersection of the two rectangles
  float left = std::max(rect1.left, rect2.left);
  float top = std::max(rect1.top, rect2.top);
  float right = std::min(rect1.left + rect1.width, rect2.left + rect2.width);
  float bottom = std::min(rect1.top + rect1.height, rect2.top + rect2.height);

  // Check for an intersection
  if (left < right && top < bottom) {
    return sf::FloatRect(left, top, right - left, bottom - top);
  } else {
    return sf::FloatRect();  // No intersection
  }
}

void Element::update_bounds()
{
  _global_bounds = _local_bounds;
  if(const auto this_parent = parent())
  {
    _global_bounds.left += this_parent->_local_bounds.left;
    _global_bounds.top += this_parent->_local_bounds.top;
    // _global_bounds = intersection(_global_bounds, this_parent->_global_bounds);
  }
}


}
