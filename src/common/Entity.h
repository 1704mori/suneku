#pragma once

#include "Logger.h"

#include <vector>

namespace snek
{
  struct Position
  {
    int32_t x;
    int32_t y;
  };

  class Entity
  {
  public:
    Entity() = default;
    virtual ~Entity() = default;

    virtual void Spawn() = 0;
    virtual void Remove(int index) = 0;

    void SetLogger(common::Logger *logger)
    {
      this->logger = logger;
    }

    // virtual std::vector<std::pair<int32_t, int32_t>> GetPosition() const = 0;
    virtual std::vector<Position> GetPosition() const = 0;

  protected:
    common::Logger *logger;
  };
}