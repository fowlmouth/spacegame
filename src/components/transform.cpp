#include "transform.hpp"

template<>
void MM::ComponentEditorWidget< sg::components::Transform >(entt::registry& reg, entt::registry::entity_type entity)
{
  auto& t = reg.get< sg::components::Transform >(entity);
  ImGui::DragFloat("x##Transform", &t.x, 0.1f);
  ImGui::DragFloat("y##Transform", &t.y, 0.1f);
  ImGui::DragFloat("angle##Transform", &t.radians, 0.1f);
}
