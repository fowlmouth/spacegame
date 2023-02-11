
#include "pick-scene.hpp"
#include "../components/relationships.hpp"

#include "../ui.hpp"

#include <memory>

// struct UIStyle
// {
//   enum PackingStyle { Horizontal, Vertical };

//   sg::AssetCache::FontRef font;
//   int font_size;
//   PackingStyle packing_style;
//   sf::Color background, foreground;
// };

// struct UIClickHandler
// {
//   entt::any value;
//   int(*action)(entt::registry&, entt::entity, entt::any&);
// };

struct CalculatedTransform : public sg::components::Transform
{
};

// struct UIText
// {
//   std::string text;
// };

namespace sg::scenes
{

PickScene::PickScene()
: cache("assets")
{
  // reg.on_construct< Transform >().connect< & entt::registry::emplace< CalculatedTransform > >();
}

Scene::EventResponse PickScene::handle_event(const sf::Event& event)
{
  switch(event.type)
  {
  case sf::Event::Closed:
    return Scene::EventResponse::Close;
  case sf::Event::KeyPressed:
    if(event.key.code == sf::Keyboard::Key::Escape)
    {
      return Scene::EventResponse::Close;
    }
    // continue
  default:
    return Scene::EventResponse::Continue;
  }
}

void PickScene::update(const sf::Time&)
{
}

void PickScene::render(sf::RenderTarget& target)
{
  ImGui::Begin("Scenes##PickScene", 0, 0);
  for(int i = 0; i < scenes.size(); ++i)
  {
    if(ImGui::Button(scenes[i].name))
    {
      schedule_scene(scenes[i].constructor);
    }
  }
  ImGui::End();
}

void PickScene::pre_update(Application&)
{

}

void PickScene::post_update(Application& app)
{
  if(next_scene)
  {
    PickableScene* scene = next_scene();
    next_scene = nullptr;
    if(scene)
    {
      std::unique_ptr< Scene > ptr;
      ptr.reset((Scene*)scene);
      app.replace_scene(std::move(ptr));
    }
  }
}

void PickScene::schedule_scene(PickScene::SceneConstructor constructor)
{
  next_scene = constructor;
}

void PickScene::on_enter(Application& app)
{
}


}
