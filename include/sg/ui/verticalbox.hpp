#pragma once

#include "container.hpp"

namespace sg::ui
{

class VerticalBox : public Container
{
private:
  void on_element_added(ElementRef) override;

protected:
  float next_y = 0;

public:
  VerticalBox();

};

}
