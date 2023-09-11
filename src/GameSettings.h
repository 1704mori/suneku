#pragma once

#include "Utils.h"

#include <algorithm>

namespace snek
{
  class GameSettings
  {
  public:
    static GameSettings &getInstance()
    {
      static GameSettings instance;
      return instance;
    }

    int GetWindowWidth() const { return m_WindowWidth; }
    int GetWindowHeight() const { return m_WindowHeight; }
    int GetGridSize() const { return m_GridSize; }

    void UpdateWindowSize(int width, int height)
    {
      m_WindowWidth = width;
      m_WindowHeight = height;
      m_GridSize = std::min(width, height) / 40;
    }

  private:
    GameSettings() : m_WindowWidth(800), m_WindowHeight(600), m_GridSize(20) {}
    GameSettings(const GameSettings &) = delete;
    GameSettings &operator=(const GameSettings &) = delete;

    int m_WindowWidth;
    int m_WindowHeight;
    int m_GridSize;
  };

}