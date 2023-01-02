#pragma once

#include "label.hpp"

namespace sg::ui
{

class Button : public Label
{
public:
  using Callback = std::function< void(ElementRef) >;

private:
  Callback on_click_fn;

public:
  using Label::Label;

  void on_click(Callback function);

  Element::HandleEventResponse handle_event(const sf::Event&);
};

}
