#include "imgui-test.hpp"

namespace sg::scenes
{

const char* ImguiTest::SCENE_NAME = "ImguiTest";

sg::Scene::EventResponse ImguiTest::handle_event(const sf::Event&)
{
  return sg::Scene::EventResponse::Continue;
}
void ImguiTest::update(const sf::Time&)
{

}
void ImguiTest::render(sf::RenderTarget&)
{
  ImGui::ShowDemoWindow();
}


}