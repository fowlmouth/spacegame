#include "sg/components/material.hpp"

template<>
void MM::ComponentEditorWidget< sg::components::Material >(entt::registry& reg, entt::registry::entity_type entity)
{
  auto& mat = reg.get< sg::components::Material >(entity);

  float color[3] = {
    (float)mat.fill_color.r / 255,
    (float)mat.fill_color.g / 255,
    (float)mat.fill_color.b / 255
  };
  ImGui::ColorEdit3("Fill Color##Material", color, 0);
  mat.fill_color.r = (unsigned char)(color[0] * 255);
  mat.fill_color.g = (unsigned char)(color[1] * 255);
  mat.fill_color.b = (unsigned char)(color[2] * 255);
}
