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
    void Spawn(uint32_t amount = 2);
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
    // std::pair<int, int> m_Position;
    // vector of pairs
    std::vector<std::pair<int, int>> m_Position;
    GameSettings &m_Settings = GameSettings::getInstance();
    Snake &m_Snake = Snake::getInstance();
  };
}