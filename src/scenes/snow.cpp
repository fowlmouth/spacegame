#include "sg/scenes/snow.hpp"
#include "sg/components.hpp"

#include <iostream>
#include <cmath>

struct SinusoidalTransformOffset
{
  float length, time_offset;
};

static const sf::Color dark_green(0x003e1fFF),
  red(0xd90429FF),
  light_red(0xef233cDD);

namespace sg::scenes
{

void randomize_position(entt::registry& reg, entt::entity ent, auto& random_gen, sf::Vector2f min, sf::Vector2f max)
{
  std::uniform_real_distribution<> dist_x(min.x, max.x);
  std::uniform_real_distribution<> dist_y(min.y, max.y);
  std::uniform_real_distribution<> dist_angle(0.0, M_PI*2);
  Transform& t = reg.get_or_emplace< Transform >(ent);
  t.x = dist_x(random_gen);
  t.y = dist_y(random_gen);
  t.radians = dist_angle(random_gen);
}

const char* Snow::SCENE_NAME = "Snow Demo Scene";

bool Snow::should_snow() const
{
  return snow_clock.getElapsedTime().asSeconds() > snow_next_time;
}

void Snow::reset_snow_timer()
{
  snow_clock.restart();
  snow_next_time = snow_distribution(gen);
}

void Snow::make_snowflakes(int count, float screen_width)
{
  std::uniform_real_distribution<float> dist_angular_velocity(-2.f, 2.f);
  std::uniform_real_distribution<float> dist_velocity(20.5, 36.9);
  std::uniform_real_distribution<float> dist_radius(22.f, 28.f);
  std::uniform_real_distribution<float> dist_sin_time(0.f, 1.f);
  std::uniform_real_distribution<float> dist_sin_offset(0.f, 60.f);
  for(int i = 0; i < count; ++i)
  {
    auto ent = reg.create();
    Material& mat = reg.emplace< Material >(ent);
    mat.fill_color = sf::Color::White;
    mat.fill_color.a = 180;
    mat.outline_color = sf::Color::Transparent;
    mat.texture = snow_texture;
    Mesh& mesh = reg.emplace< Mesh >(ent);
    float radius = dist_radius(gen);
    mesh.set_circle(sf::Vector2f(0,0), 30, radius);
    sf::Vector2f min_pos(0, -radius - 10.0), max_pos(screen_width, -radius);
    randomize_position(reg, ent, gen, min_pos, max_pos);
    Velocity& v = reg.get_or_emplace< Velocity >(ent, 0.f, (float)dist_velocity(gen), (float)dist_angular_velocity(gen));

    auto& effects = reg.get_or_emplace< components::VisualEffectQueue >(ent);
    effects.effects.emplace_back(components::VisualEffect::sin_offset(
      M_PI * 13 / 27, dist_sin_offset(gen), dist_sin_time(gen)));
  }
}

Snow::Snow()
: Snow(sf::seconds(1), sf::seconds(0.3))
{
}

Snow::Snow(sf::Time snow_rate, sf::Time variance)
: rd(), gen(this->rd()),
  snow_distribution((snow_rate - variance).asSeconds(), (snow_rate + variance).asSeconds())
{
  snow_texture = std::make_shared< sf::Texture >();
  if(!snow_texture->loadFromFile("assets/imgbin_snowflake-icon-weather-collection-icon-snow-icon-png.png"))
  {
    std::cerr << "failed to load texture imgbin_snowflake-icon-weather-collection-icon-snow-icon-png.png" << std::endl;
    snow_texture = nullptr;
  }
  if(!background_text_font.loadFromFile("assets/ChristmasSparklePersonalUse-dLal.ttf"))
  {
    std::cerr << "failed to load font ChristmasSparklePersonalUse-dLal.ttf" << std::endl;
  }
  else
  {
    background_text.setFont(background_text_font);
  }
  background_text.setString("Merry Christmas!");
  background_text.setCharacterSize(120);
  background_text.setPosition(25, 100);
  background_text.setFillColor(red);
  reset_snow_timer();
}

Scene::EventResponse Snow::handle_event(const sf::Event& event)
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

void Snow::pre_update(Application& app)
{
  if(should_snow())
  {
    reset_snow_timer();
    std::discrete_distribution<int> snowflake_count{3, 11, 5, 2, 0, 10, 10};
    auto window_size = app.get_window_size();
    make_snowflakes(snowflake_count(gen), (float)window_size.x);
    const auto transform_entities = reg.view< const Transform >();
    std::deque< entt::entity > delete_entities;
    for(const auto& [ entity, transform ] : transform_entities.each())
    {
      if(transform.y > (float)window_size.y)
      {
        delete_entities.push_back(entity);
      }
    }
    for(const auto ent : delete_entities)
    {
      reg.destroy(ent);
    }
  }
}

void Snow::on_enter(Application& app)
{
  scene_start_time.restart();
  app.set_window_title("Merry Christmas!");
}

void Snow::update(const sf::Time& elapsed)
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

void Snow::render(sf::RenderTarget& target)
{
  target.clear(dark_green);
  target.draw(background_text);

  renderer.render(target, reg);
}

}
