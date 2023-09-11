#pragma once

#include "Renderer.h"
#include "Snake.h"
#include "Food.h"
#include "GameSettings.h"

#include "common/Logger.h"

#include "../vendor/glfw/include/glfw3.h"

#include <iostream>

namespace snek
{
  class Game
  {
  public:
    Game(GLFWwindow *window);

    void Run();
    void SetMaxFoodCount(uint32_t count) { m_MaxFoodCount = count; }
    void SetScore(uint32_t score) { m_Score = score; }
    uint32_t GetScore() const { return m_Score; }

  private:
    common::Logger *logger;

    GLFWwindow *m_Window;
    Renderer m_Renderer;
    GameSettings &m_Settings = GameSettings::getInstance();

    Snake m_Snake;
    Food m_Food;

    bool m_Running = false;
    bool m_GameOver = false;

    uint32_t m_Score;
    uint32_t m_FoodCount = 0;
    uint32_t m_MaxFoodCount = 7;

    double m_FoodSpawnTimer = 0;
    const double m_FoodSpawnTime = 1;

    using KeyCallbackType = void (*)(GLFWwindow *, int, int, int, int);
    KeyCallbackType keyCallback;

    void ProcessInput(int key, int action);
    void Update();
    void RenderGameOverScreen();
    void RenderTitleScreen();
  };
}