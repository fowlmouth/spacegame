#include "sg/hid-controller.hpp"

namespace sg::hid
{

bool Button::is_pressed() const
{
  bool result = false;
  switch(type)
  {
  case Key:
    result = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)value);
    break;
  case MouseButton:
    result = sf::Mouse::isButtonPressed((sf::Mouse::Button)value);
    break;
  default:
    break;
  }
  return result;
}

void ButtonValueMapper::apply(void* input_state) const
{
  bool boolean_value = false;
  if(button.is_pressed())
  {
    boolean_value = true;
  }

  switch(type)
  {
  case ButtonValueMapper::Bool:
  {
    bool* val = (bool*)((char*)input_state + offset);
    *val = boolean_value;
    break;
  }
  case ButtonValueMapper::BoolToLowFloat:
  {
    float* val = (float*)((char*)input_state + offset);
    if(boolean_value)
      *val = -1.f;
    else if(*val < -0.9f) // reset val only if val is already low
      *val = 0.f;
    break;
  }
  case ButtonValueMapper::BoolToHighFloat:
  {
    float* val = (float*)((char*)input_state + offset);
    if(boolean_value)
      *val = 1.f;
    else if(*val > 0.9f) // reset val only if val is already high
      *val = 0.f;
    break;
  }

  case ButtonValueMapper::None:
    break;

  default:
    throw todo{};

  }
}

}
