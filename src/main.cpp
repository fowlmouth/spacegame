#include "sg/application.hpp"
#include "sg/scenes/main.hpp"
#include "sg/scenes/pick-scene.hpp"
#include "sg/scenes/snow.hpp"
#include "sg/scenes/pong.hpp"
#include "sg/scenes/intro.hpp"
#include "sg/scenes/imgui-test.hpp"

#include <iostream>
#include <libgen.h>

int main(int argc, const char** argv)
{
  sg::Application app;
  {
    auto main_scene = std::make_unique< sg::scenes::PickScene >();
    main_scene->register_scenes<
      sg::scenes::Main,
      sg::scenes::Snow,
      sg::scenes::Pong,
      sg::scenes::ImguiTest
    >();
    app.push_scene(std::make_unique< sg::scenes::Intro >(
      sf::seconds(0.2f),
      std::move(main_scene)));
  }
  return app.run();
}
