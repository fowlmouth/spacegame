#include "hid-controller.hpp"

#include <array>

namespace sg::hid
{

float wheel_deltas[2] = {0, 0};

void observeEvent(const sf::Event& event)
{
  switch(event.type)
  {
  case sf::Event::MouseWheelScrolled:
    wheel_deltas[(int)event.mouseWheelScroll.wheel] = event.mouseWheelScroll.delta;
    break;

  default:
    break;
  }
}

void endFrame()
{
  wheel_deltas[0] = 0;
  wheel_deltas[1] = 0;
}

bool Button::is_pressed(float& axis) const
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
  case MouseWheel:
    result = (value >= 0 && value < 2) ? (wheel_deltas[value] != 0.0) : false;
    axis = wheel_deltas[value];
    break;
  default:
    break;
  }
  return result;
}

void ButtonValueMapper::apply(void* input_state) const
{
  bool boolean_value = false;
  float axis = 0.f;
  if(button.is_pressed(axis))
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

  case ButtonValueMapper::Float:
  {
    float* val = (float*)((char*)input_state + offset);
    *val = axis;
    break;
  }

  default:
    throw todo{};

  }
}

}
