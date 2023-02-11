#pragma once

#include "container.hpp"

namespace sg::ui
{

class Layer : public Container
{
public:
  Layer(float width, float height);

  void set_size(float width, float height);

};

}
