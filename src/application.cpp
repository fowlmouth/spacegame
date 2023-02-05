#include "sg/application.hpp"
#include "sg/scene.hpp"

#include <iostream>

#include "sg/hid-controller.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

namespace sg
{

Scene* Application::current_scene() const
{
  return scene_stack.top().get();
}

Application::Application()
: window(sf::VideoMode(800, 600), "Space Game")
{
  window.setVerticalSyncEnabled(true);
  ImGui::SFML::Init(window);
}

Application::~Application()
{
  ImGui::SFML::Shutdown(window);
}

int Application::run()
{
  while(window.isOpen() && !scene_stack.empty())
  {
    sf::Event event;
    while(window.pollEvent(event))
    {
      sg::hid::observeEvent(event);
      ImGui::SFML::ProcessEvent(window, event);
      switch(event.type)
      {
      case sf::Event::Closed:
        window.close();
        return 0;

      default:
        switch(current_scene()->handle_event(event))
        {
        case Scene::EventResponse::Continue:
          break;
        case Scene::EventResponse::Close:
          window.close();
          return 0;
        }
        break;
      }
    }
    current_scene()->pre_update(*this);

    sf::Time elapsed = fps.restart();
    current_scene()->update(elapsed);
    ImGui::SFML::Update(window, elapsed);

    current_scene()->post_update(*this);
    sg::hid::endFrame();

    window.clear(sf::Color::Black);
    current_scene()->render(window);
    ImGui::SFML::Render(window);
    window.display();
  }
  return 0;
}

void Application::replace_scene(std::unique_ptr< Scene >&& new_scene)
{
  if(!scene_stack.empty())
  {
    scene_stack.top()->on_leave(*this);
    scene_stack.pop();
  }
  if(new_scene)
  {
    scene_stack.push(std::move(new_scene));
    scene_stack.top()->on_enter(*this);
  }
}

void Application::push_scene(std::unique_ptr< Scene >&& new_scene)
{
  if(! scene_stack.empty())
  {
    scene_stack.top()->on_leave(*this);
  }
  scene_stack.push(std::move(new_scene));
  scene_stack.top()->on_enter(*this);
}

void Application::pop_scene()
{
  if(! scene_stack.empty())
  {
    scene_stack.top().get()->on_leave(*this);
    scene_stack.pop();
  }
}

sf::Vector2u Application::get_window_size() const
{
  return window.getSize();
}

void Application::set_window_size(sf::Vector2u new_size)
{
  window.setSize(new_size);
}

void Application::set_window_title(const char* title)
{
  window.setTitle(title);
}


}
