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

  private:
    common::Logger *logger;

    GLFWwindow *m_Window;
    Renderer m_Renderer;
    GameSettings &m_Settings = GameSettings::getInstance();

    Snake m_Snake;
    Food m_Food;

    bool m_Running = false;
    bool m_GameOver = false;

    uint32_t m_FoodCount = 0;
    uint32_t m_MaxFoodCount = 5;

    void ProcessInput();
    void Update();
    void RenderGameOverScreen();
    void RenderTitleScreen();
  };
}