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

    void SetScore(uint32_t score) { m_Score = score; }
    uint32_t GetScore() const { return m_Score; }

    // get instance
    static Snake &getInstance()
    {
      static Snake instance;
      return instance;
    }

  private:
    std::vector<std::pair<int, int>> m_Body;
    int m_Direction;
    uint32_t m_Score;
  };
}