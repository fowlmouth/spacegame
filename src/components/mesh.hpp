#pragma once

#include <SFML/System/Vector2.hpp>

#include <vector>

#include "imgui.h"
#include "imgui_entt_entity_editor.hpp"


namespace sg::components
{

struct Mesh
{
  std::vector< sf::Vector2f > points;
  sf::Vector2f center;

  void set_circle(sf::Vector2f center, int point_count, float radius);
  void set_radial_polygon(sf::Vector2f center, int point_count, float radius, float start_offset_radians);
  void set_box(sf::Vector2f center, float width);
  void set_rectangle(sf::Vector2f center, float width, float height);
};

}

template<>
void MM::ComponentEditorWidget< sg::components::Mesh >(entt::registry& reg, entt::registry::entity_type entity);
