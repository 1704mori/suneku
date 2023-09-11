#pragma once

#include <vector>
#include "../vendor/glfw/include/glfw3.h"

namespace snek
{
  class Snake
  {
  public:
    Snake();
    void Move();
    void Grow();
    bool IsCollision();
    void ChangeDirection(int newDirection);
    void Reset();
    std::vector<std::pair<int, int>> GetBody() const;

    // get instance
    static Snake &getInstance()
    {
      static Snake instance;
      return instance;
    }

  private:
    std::vector<std::pair<int, int>> m_Body;
    int m_Direction;
  };
}