#include "debug-renderer.hpp"

namespace sg
{


#define RADIANS_TO_DEGREES(radians) (radians * 180.0 / M_PI)

struct ShapeAdapter : public sf::Shape
{
  const Mesh* mesh = nullptr;

  std::size_t getPointCount() const override
  {
    return mesh->points.size();
  }

  sf::Vector2f getPoint(std::size_t index) const override
  {
    return mesh->points.at(index);
  }
};


DebugRenderer::DebugRenderer()
{
  default_material.fill_color = sf::Color(180,180,180,255);
  default_material.outline_color = sf::Color::White;
  default_material.outline_thickness = 1.2f;
}

void DebugRenderer::render(sf::RenderTarget& target, entt::registry& reg)
{
  auto view = reg.view< Transform, Mesh >();
  for(auto ent : view)
  {
    ShapeAdapter& shape = reg.get_or_emplace< ShapeAdapter >(ent);
    shape.mesh = & view.get< Mesh >(ent);
    const auto& transform = view.get< Transform >(ent);
    shape.setPosition(transform.x, transform.y);
    shape.setRotation(RADIANS_TO_DEGREES(transform.radians));
    auto mat = reg.try_get< Material >(ent);
    if(!mat)
      mat = &default_material;
    shape.setFillColor(mat->fill_color);
    shape.setOutlineColor(mat->outline_color);
    shape.setOutlineThickness(mat->outline_thickness);
    shape.setTexture(mat->texture.get(), true);
  }

  auto view2 = reg.view< ShapeAdapter, components::VisualEffectQueue >();
  float scene_time_seconds = scene_time.getElapsedTime().asSeconds();
  for(auto&& [ent, shape, queue] : view2.each())
  {
    for(const auto& effect : queue.effects)
    {
      effect.apply(&shape, &shape, scene_time_seconds);
    }
  }

  auto view3 = reg.view< ShapeAdapter >();
  for(auto&& [ent, shape] : view3.each())
  {
    target.draw(shape);
  }
}

}
