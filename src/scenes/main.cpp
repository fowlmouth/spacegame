#include "main.hpp"
#include "../components.hpp"

#include <iostream>

namespace sg::scenes
{

const char* Main::SCENE_NAME = "Main Scene";

Main::Main()
{
  auto ent = reg.create();
  reg.emplace< Transform >(ent, 10.f, 10.f, 0.f);
  reg.emplace< Velocity >(ent, 1.f, 12.f, 0.f);
  Material& mat = reg.emplace< Material >(ent);
  mat.fill_color = sf::Color::White;
  mat.fill_color.a = 120;
  mat.outline_color = sf::Color::Green;
  mat.outline_thickness = 1.5;
  Mesh& mesh = reg.emplace< Mesh >(ent);
  mesh.set_circle(sf::Vector2f(0,0), 30, 15.f);
}

Scene::EventResponse Main::handle_event(const sf::Event& event)
{
  switch(event.type)
  {
  case sf::Event::KeyPressed:
    switch(event.key.code)
    {
    case sf::Keyboard::Key::Escape:
      return Scene::EventResponse::Close;

    default:
      break;
    }
    break;

  default:
    break;
  }
  return Scene::EventResponse::Continue;
}

void Main::update(const sf::Time& elapsed)
{
  const float dt_seconds = elapsed.asSeconds();
  const auto movers = reg.view< Transform, const Velocity >();
  for(const auto& [ entity, transform, velocity ] : movers.each())
  {
    transform.x += velocity.vx * dt_seconds;
    transform.y += velocity.vy * dt_seconds;
    transform.radians += velocity.angular * dt_seconds;
  }
}




#define RADIANS_TO_DEGREES(radians) (radians * 180.0 / M_PI)

struct ShapeAdapter : public sf::Shape
{
  const Mesh* mesh = nullptr;

  ShapeAdapter(const Transform& transform, const Material& material, const Mesh& mesh)
  : mesh(&mesh)
  {
    setPosition(transform.x, transform.y);
    setRotation(RADIANS_TO_DEGREES(transform.radians));
    setFillColor(material.fill_color);
    setOutlineColor(material.outline_color);
    setOutlineThickness(material.outline_thickness);
    setTexture(material.texture.get(), true);
  }

  std::size_t getPointCount() const override
  {
    return mesh->points.size();
  }

  sf::Vector2f getPoint(std::size_t index) const override
  {
    return mesh->points.at(index);
  }
};



void Main::render(sf::RenderTarget& target)
{
  const auto renderables = reg.view< const Transform, const Material, const Mesh >();

  for(const auto& [entity, transform, material, mesh] : renderables.each())
  {
    ShapeAdapter shape(transform, material, mesh);
    target.draw(shape);
  }
}

}
