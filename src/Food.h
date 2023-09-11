#pragma once

#include "common/Entity.h"
#include "GameSettings.h"
#include "Snake.h"

#include "common/Logger.h"

#include <utility>

namespace snek
{
  class Food : Entity
  {
  public:
    Food();
    virtual ~Food();
    virtual void Spawn();
    virtual void Remove(int index);

    void RemoveAllFood();

    // std::pair<int, int> GetPosition() const;
    // std::vector<std::pair<int, int>> GetPosition() const;
    virtual std::vector<Position> GetPosition() const;

    // common::Logger *logger;

  private:
    GameSettings &m_Settings = GameSettings::getInstance();
    Snake &m_Snake = Snake::getInstance();

    std::vector<Position> m_Position;
  };
}