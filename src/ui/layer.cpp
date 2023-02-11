#include "../ui/layer.hpp"

namespace sg::ui
{

Layer::Layer(float width, float height)
: Container()
{
  set_size(width, height);
  update_bounds();
}

void Layer::set_size(float width, float height)
{
  _local_bounds.width = width;
  _local_bounds.height = height;
}

}