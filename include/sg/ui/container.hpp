#pragma once

#include "element.hpp"

namespace sg::ui
{

class Container : public Element
{
private:
  virtual void on_element_added(ElementRef);

protected:
  std::vector< ElementRef > members;

public:
  Container();
  ~Container();

  Container& add(ElementRef child);
  Element::HandleEventResponse handle_event(const sf::Event& event);

  void render(sf::RenderTarget&);
};

}
