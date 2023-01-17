#pragma once

#include "../scene.hpp"
#include "../asset-cache.hpp"

#include "../ui.hpp"

#include "../components.hpp"

#include <vector>
#include <functional>

#include "../application.hpp"

#include "entt/entt.hpp"

namespace sg::scenes
{

class PickableScene : public Scene
{
};

class PickScene : public Scene
{
  using SceneConstructor = std::function< PickableScene*() >;

  struct PickSceneRecord
  {
    const char* name;
    SceneConstructor constructor;
  };

  std::vector< PickSceneRecord > scenes;
  AssetCache::FontRef ui_font;

  AssetCache cache;

  entt::registry reg;
  sg::ui::ContainerRef ui_root;
  sg::ui::StyleRef ui_style;
  SceneConstructor next_scene;

public:

  PickScene();

  template< typename SceneType >
  void register_scene_type(const char* name)
  {
    scenes.push_back({ name, [](){ return (PickableScene*)new SceneType(); }});
  }

  template< typename... Scenes >
  void register_scenes()
  {
    (this->register_scene_type< Scenes >(Scenes::SCENE_NAME), ...);
  }


  Scene::EventResponse handle_event(const sf::Event&) override;
  void update(const sf::Time&) override;
  void render(sf::RenderTarget&) override;

  void pre_update(Application&) override;
  void post_update(Application&) override;
  void on_enter(Application&) override;

  void schedule_scene(PickScene::SceneConstructor constructor);

};

}