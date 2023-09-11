#pragma once

#include "common/Logger.h"

#include "GameSettings.h"
#include "Snake.h"

#include <vector>

namespace snek
{
  enum class EntityType
  {
    Food,
    Pickups,
  };

  class Entity
  {
  public:
    Entity(EntityType type);
    ~Entity();

    EntityType GetType() const;
    std::vector<std::pair<int32_t, int32_t>> GetPosition() const;
    void SetPosition(int index, const std::vector<std::pair<int32_t, int32_t>> &newPosition);
    void Spawn();

    uint32_t Count() { return m_Position.size(); }

    void RemoveAll() { m_Position.clear(); }
    void Remove(int index)
    {
      m_Position.erase(m_Position.begin() + index);
      m_Position.shrink_to_fit();
    }

  private:
    GameSettings &m_Settings = GameSettings::getInstance();
    Snake &m_Snake = Snake::getInstance();

    EntityType m_Type;
    std::vector<std::pair<int32_t, int32_t>> m_Position;
    common::Logger *logger;
  };
}
