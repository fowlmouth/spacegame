#include "../ui/verticalbox.hpp"

#include <iostream>

namespace sg::ui
{

VerticalBox::VerticalBox()
: Container()
{
}

void VerticalBox::on_element_added(ElementRef element)
{
  element->set_local_position(0, next_y);
  element->update();
  element->update_bounds();
  next_y += element->local_bounds().height;
}

}
