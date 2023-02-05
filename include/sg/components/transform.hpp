#pragma once

#include "imgui.h"
#include "imgui_entt_entity_editor.hpp"

namespace sg::components
{

struct Transform
{
  float x, y, radians;
};

}

template<>
void MM::ComponentEditorWidget< sg::components::Transform >(entt::registry& reg, entt::registry::entity_type entity);
