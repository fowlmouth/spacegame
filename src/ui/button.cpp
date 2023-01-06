#include "sg/ui/button.hpp"

namespace sg::ui
{

void Button::on_click(Callback function)
{
  on_click_fn = function;
}

Element::HandleEventResponse Button::handle_event(const sf::Event& event)
{
  switch(event.type)
  {
  case sf::Event::MouseButtonReleased:
  {
    // std::cout << "checking button released in a Button _global_bounds= " << _global_bounds << std::endl;
    if(event.mouseButton.button == sf::Mouse::Button::Left)
    {
      int mouse_x = event.mouseButton.x, mouse_y = event.mouseButton.y;
      if(_global_bounds.contains((float)mouse_x, (float)mouse_y))
      {
        // std::cout << "contained!" << std::endl;
        if(on_click_fn)
        {
          on_click_fn(this->shared_from_this());
        }
        return sg::ui::Element::HandleEventResponse::Handled;
      }
    }
    else
    {
      // std::cout << "not matched" << std::endl;
    }
    break;
  }
  default:
    break;
  }
  return Element::HandleEventResponse::NotHandled;
}

}
