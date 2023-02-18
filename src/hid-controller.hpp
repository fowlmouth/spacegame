#pragma once

#include <entt/entt.hpp>
#include <SFML/Window.hpp>
#include <cstddef>
#include <string>

#include <iostream>

namespace sg::hid
{

struct todo{};

void observeEvent(const sf::Event&);
void endFrame();

struct Button
{
  enum ButtonType
  { 
    None, Key, MouseButton, MouseWheel
  };

  ButtonType type = None;
  int value;

  bool is_pressed(float& axis) const;
};



struct ButtonValueMapper
{
  enum ValueType
  {
    None, Bool, BoolToLowFloat, BoolToHighFloat, Float
  };

  Button button;
  ValueType type = None;
  int offset;

  void apply(void* input_state) const;
};



struct ControllerConfiguration
{
  std::vector< ButtonValueMapper > actions;

  ControllerConfiguration(int action_count)
  : actions(action_count)
  {
  }
};

using ControllerConfigurationRef = std::shared_ptr< ControllerConfiguration >;


template< typename InputState >
struct Controller
{
  ControllerConfigurationRef config;

  inline InputState& input_state(entt::registry& reg, entt::entity entity)
  {
    return reg.get_or_emplace< InputState >(entity);
  }
};

template< typename InputState >
struct ControllerManager
{
  using ThisController = Controller< InputState >;

  struct EntityController
  {
    std::string name;
    entt::entity entity = entt::null;
    ControllerConfigurationRef config;
  };

  std::vector< EntityController > controllers;

  void release(int id, entt::registry& reg)
  {
    claim(id, reg, entt::null);
  }

  void clear(entt::registry& reg)
  {
    for(int i = 0; i < controllers.size(); ++i)
    {
      release(i, reg);
    }
  }

  bool claim(int id, entt::registry& reg, entt::entity new_entity)
  {
    if(id < 0 || id >= controllers.size()) return false;

    auto& ctrl = controllers[id];
    if(ctrl.entity != entt::null)
    {
      reg.remove< ThisController >(ctrl.entity);
    }
    ctrl.entity = new_entity;
    if(ctrl.entity != entt::null)
    {
      auto& controller = reg.emplace< ThisController >(ctrl.entity, ctrl.config);
      controller.input_state(reg, ctrl.entity);
    }
    return true;
  }

  void update(entt::registry& reg)
  {
    for(auto& ctrl : controllers)
    {
      if(ctrl.entity != entt::null)
      {
        auto& controller = reg.get< ThisController >(ctrl.entity);
        auto& input_state = controller.input_state(reg, ctrl.entity);
        const auto& config = controller.config;
        for(const auto& action : config->actions)
        {
          action.apply(&input_state);
        }
      }
    }
  }

};


}

