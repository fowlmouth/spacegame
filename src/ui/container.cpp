#include "../ui/container.hpp"

namespace sg::ui
{

Container::Container()
{
}

Container::~Container()
{
}

Container& Container::add(ElementRef child)
{
  child->set_parent(std::dynamic_pointer_cast< Container >(shared_from_this()));
  members.push_back(child);
  this->on_element_added(child);
  return *this;
}

Element::HandleEventResponse Container::handle_event(const sf::Event& event)
{
  for(auto& child : members)
  {
    auto resp = child->handle_event(event);
    if(resp != Element::HandleEventResponse::NotHandled)
    {
      return resp;
    }
  }
  return Element::HandleEventResponse::NotHandled;
}

void Container::on_element_added(ElementRef)
{
}

void Container::render(sf::RenderTarget& target)
{
  if(_dirty)
  {
    update();
    update_bounds();
  }
  for(auto& child : members)
  {
    child->render(target);
  }
}

}
