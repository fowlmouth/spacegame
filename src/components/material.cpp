#include "sg/components/material.hpp"

template<>
void MM::ComponentEditorWidget< sg::components::Material >(entt::registry& reg, entt::registry::entity_type entity)
{
  auto& mat = reg.get< sg::components::Material >(entity);

}
