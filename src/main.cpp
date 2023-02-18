#include "application.hpp"
#include "scenes/main.hpp"
#include "scenes/pick-scene.hpp"
#include "scenes/snow.hpp"
#include "scenes/pong.hpp"
#include "scenes/edyn-pong.hpp"
#include "scenes/intro.hpp"
#include "scenes/imgui-test.hpp"

#include <iostream>
#include <libgen.h>

int main(int argc, const char** argv)
{
  srand(time(NULL));
  sg::Application app;
  {
    auto main_scene = std::make_unique< sg::scenes::PickScene >();
    main_scene->register_scenes<
      sg::scenes::Main,
      sg::scenes::Snow,
      sg::scenes::Pong,
      sg::scenes::EdynPong,
      sg::scenes::ImguiTest
    >();
    app.push_scene(std::make_unique< sg::scenes::Intro >(
      sf::seconds(0.2f),
      std::move(main_scene)));
  }
  return app.run();
}
