#pragma once

#include <entt/entt.hpp>
#include <SFML/Window.hpp>
#include <cstddef>
#include <string>

#include <iostream>

namespace sg::hid
{

struct todo{};

struct Button
{
  enum ButtonType
  { 
    None, Key, MouseButton
  };

  ButtonType type = None;
  int value;

  bool is_pressed() const;
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

template< typename InputState >
struct ControllerConfiguration
{
  std::vector< ButtonValueMapper > actions;

  ControllerConfiguration(int action_count)
  : actions(action_count)
  {
  }
};

template< typename InputState >
struct Controller
{
  using Configuration = ControllerConfiguration< InputState >;
  using ConfigurationRef = std::shared_ptr< Configuration >;
  ConfigurationRef config;

  inline InputState& input_state(entt::registry& reg, entt::entity entity)
  {
    return reg.get_or_emplace< InputState >(entity);
  }
};

template< typename InputState >
struct ControllerManager
{
  using ThisController = Controller< InputState >;
  using ThisControllerConfigurationRef = typename ThisController::ConfigurationRef;

  struct EntityController
  {
    std::string name;
    entt::entity entity = entt::null;
    ThisControllerConfigurationRef config;
  };

  std::vector< EntityController > controllers;

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

