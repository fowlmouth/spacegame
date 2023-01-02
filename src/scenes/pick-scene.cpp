
#include "sg/scenes/pick-scene.hpp"
#include "sg/components/relationships.hpp"

#include "sg/application-interface.hpp"

#include "sg/ui.hpp"

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
  if(ui_root->handle_event(event) != sg::ui::Element::HandleEventResponse::NotHandled)
  {
    return Scene::EventResponse::Continue;
  }
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
  ui_root->render(target);
}

void PickScene::pre_update(ApplicationInterface&)
{

}

void PickScene::post_update(ApplicationInterface& app)
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

void PickScene::on_enter(ApplicationInterface& app)
{
  if(!ui_style)
  {
    ui_style = std::make_shared< sg::ui::Style >();
    ui_style->font = cache.font("Work-Sans/fonts/ttf/WorkSans-Regular.ttf");
    ui_style->font_size = 24;
    // ui_style->packing_style = UIStyle::Vertical;
    ui_style->foreground = sf::Color::White;
    ui_style->background = sf::Color::Transparent;
  }

  if(!ui_root)
  {
    auto window_size = app.get_window_size();

    ui_root = std::make_shared< sg::ui::Layer >((float)window_size.x, (float)window_size.y);
    ui_root->set_style(ui_style);
    ui_root->update_bounds();

    auto vbox = std::make_shared< sg::ui::VerticalBox >();
    vbox->set_style(ui_style);
    vbox->set_local_position(50,100);

    ui_root->add(vbox);

    float y = 0.f;
    for(int i = 0; i < scenes.size(); ++i)
    {
      auto label = std::make_shared< sg::ui::Button >(scenes[i].name);
      label->set_style(ui_style);
      auto constructor = scenes[i].constructor;
      label->on_click([=](sg::ui::ElementRef){
        this->schedule_scene(constructor);
      });

      vbox->add(label);
    }
  }
}


}
