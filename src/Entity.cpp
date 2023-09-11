#include "Entity.h"

namespace snek
{
  Entity::Entity(EntityType type)
      : m_Type(type), logger(new common::Logger("Entity", false))
  {
  }

  Entity::~Entity() {}

  EntityType Entity::GetType() const
  {
    return m_Type;
  }

  std::vector<std::pair<int32_t, int32_t>> Entity::GetPosition() const
  {
    return m_Position;
  }

  void Entity::Spawn()
  {
    logger->info("Spawning entity: " + std::to_string(static_cast<int>(m_Type)) + "...");

    int x = std::rand() % (m_Settings.GetWindowWidth() / m_Settings.GetGridSize());
    int y = std::rand() % (m_Settings.GetWindowHeight() / m_Settings.GetGridSize());

    // Check if the food spawned on the snake
    for (const auto &segment : m_Snake.GetBody())
    {
      if (segment.first == x && segment.second == y)
      {
        logger->info("Food spawned on snake, respawning...");
        Spawn();
        return;
      }
    }

    m_Position.push_back(std::make_pair(x, y));
    // m_Position.push_back({x, y});
  }

  void Entity::SetPosition(int index, const std::vector<std::pair<int32_t, int32_t>> &newPosition)
  {
    m_Position[index] = newPosition[index];
  }
}
