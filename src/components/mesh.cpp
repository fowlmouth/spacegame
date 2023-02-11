#include "mesh.hpp"

template<>
void MM::ComponentEditorWidget< sg::components::Mesh >(entt::registry& reg, entt::registry::entity_type entity)
{
  auto& mesh = reg.get< sg::components::Mesh >(entity);

}
