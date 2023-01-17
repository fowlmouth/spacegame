#include "sg/debug-renderer.hpp"

namespace sg
{



#define RADIANS_TO_DEGREES(radians) (radians * 180.0 / M_PI)

struct ShapeAdapter : public sf::Shape
{
  const Mesh* mesh = nullptr;

  // ShapeAdapter(const Transform& transform, const Material& material, const Mesh& mesh, float sine_offset, float sine_time)
  // : mesh(&mesh)
  // {
  //   setPosition(transform.x + sine_offset * std::sin(sine_time), transform.y);
  //   setRotation(RADIANS_TO_DEGREES(transform.radians));
  //   setFillColor(material.fill_color);
  //   setOutlineColor(material.outline_color);
  //   setOutlineThickness(material.outline_thickness);
  //   setTexture(material.texture.get(), true);
  // }

  std::size_t getPointCount() const override
  {
    return mesh->points.size();
  }

  sf::Vector2f getPoint(std::size_t index) const override
  {
    return mesh->points.at(index);
  }
};


DebugRenderer::DebugRenderer(sf::RenderTarget& render_target)
: target(render_target)
{
}

void DebugRenderer::render(entt::registry& reg)
{
  auto view = reg.view< Transform, Material, Mesh >();
  ShapeAdapter shape;
  for(auto ent : view)
  {
    shape.mesh = & view.get< Mesh >(ent);
    const auto& transform = view.get< Transform >(ent);
    shape.setPosition(transform.x, transform.y);
    shape.setRotation(RADIANS_TO_DEGREES(transform.radians));
    const auto& mat = view.get< Material >(ent);
    shape.setFillColor(mat.fill_color);
    shape.setOutlineColor(mat.outline_color);
    shape.setOutlineThickness(mat.outline_thickness);
    shape.setTexture(mat.texture.get(), true);
    target.draw(shape);
  }
}

}
