#pragma once

#include <utility>
#include "GameSettings.h"
#include "Snake.h"

#include "common/Logger.h"

namespace snek
{
  class Food
  {
  public:
    Food();
    void Spawn();
    void RemoveFood(int index);
    void RemoveAllFood()
    {
      m_Position.clear();
      m_Position.shrink_to_fit();
    }

    // std::pair<int, int> GetPosition() const;
    std::vector<std::pair<int, int>> GetPosition() const;

    common::Logger *logger;

  private:
    GameSettings &m_Settings = GameSettings::getInstance();
    Snake &m_Snake = Snake::getInstance();

    std::vector<std::pair<int, int>> m_Position;
  };
}