#pragma once

#include <memory>
#include "style.hpp"
#include "../common-sfml.hpp"

#include <SFML/Graphics.hpp>

namespace sg::ui
{

class Element;
using ElementRef = std::shared_ptr< Element >;

class Container;
using ContainerRef = std::shared_ptr< Container >;

class Element : public std::enable_shared_from_this< Element >
{
protected:
  ContainerRef _parent;
  sf::FloatRect _local_bounds, _global_bounds;
  bool _dirty;

private:
  StyleRef _style;

public:
  Element();
  virtual ~Element();

  StyleRef style() const;
  void set_style(StyleRef);

  bool is_dirty() const;
  void set_local_position(float x, float y);
  sf::FloatRect local_bounds() const;
  sf::FloatRect global_bounds() const;

  struct ParentExists
  {
  };

  ContainerRef parent() const;
  void set_parent(ContainerRef);

  enum HandleEventResponse
  {
    NotHandled, Handled, HandledPassEvent
  };
  virtual HandleEventResponse handle_event(const sf::Event& event) = 0;

  virtual void render(sf::RenderTarget& ) = 0;
  virtual void update();

  void update_bounds();
};

}
