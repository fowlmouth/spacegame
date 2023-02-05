#pragma once

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui_entt_entity_editor.hpp"

namespace sg::components
{

struct Material
{
  std::shared_ptr< sf::Texture > texture;
  sf::Color fill_color, outline_color;
  float outline_thickness;
};

}

template<>
void MM::ComponentEditorWidget< sg::components::Material >(entt::registry& reg, entt::registry::entity_type entity);

