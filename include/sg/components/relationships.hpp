#pragma once

#include "entt/entt.hpp"
#include <vector>

namespace sg::components
{

struct Child
{
  entt::entity parent;
};

struct Parent
{
  std::vector< entt::entity > children;
};

}
