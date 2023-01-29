#pragma once

#include "../scene.hpp"
#include "../application.hpp"

#include "../debug-renderer.hpp"

#include "../components/graphical.hpp"

#include "entt/entt.hpp"

#include <random>

namespace sg::scenes
{

class Snow : public ::sg::Scene
{
  entt::registry reg;

  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<> snow_distribution;
  std::shared_ptr< sf::Texture > snow_texture;
  sf::Clock snow_clock;
  float snow_next_time;
  sf::Clock scene_start_time;
  sf::Font background_text_font;
  sf::Text background_text;
  DebugRenderer renderer;

  bool should_snow() const;
  void reset_snow_timer();
  void make_snowflakes(int count, float screen_width);

public:
  static const char* SCENE_NAME;

  Snow(sf::Time snow_rate, sf::Time variance);
  Snow();

  Scene::EventResponse handle_event(const sf::Event&) override;
  void update(const sf::Time&) override;
  void render(sf::RenderTarget&) override;

  void pre_update(Application&) override;
  void on_enter(Application&) override;

};

}
