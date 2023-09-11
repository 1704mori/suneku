#include "Game.h"

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

namespace snek
{
  Game::Game(GLFWwindow *window) : m_Window(window), m_GameOver(false)
  {
    logger = new common::Logger("Game", false);

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init();

    m_Food.Spawn(3);
    m_FoodCount = m_Food.GetPosition().size();

    logger->info(std::to_string(m_FoodCount) + " food(s) spawned");
  }

  void Game::Run()
  {
    double lastFrameTime = glfwGetTime();
    double deltaTime = 0;

    while (!glfwWindowShouldClose(m_Window))
    {
      double currentTime = glfwGetTime();
      deltaTime += currentTime - lastFrameTime;
      lastFrameTime = currentTime;
      double fps = 1.0 / deltaTime;

      ProcessInput();
      if (!m_GameOver)
      {
        if (deltaTime >= GAME_SPEED)
        {
          Update();
          deltaTime = 0;
        }
      }

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();

      ImGui::NewFrame(); // <-- Added

      glClear(GL_COLOR_BUFFER_BIT);
      // m_Renderer.DrawGridLines();

      if (!m_GameOver && m_Running)
      {
        // Draw the snake
        for (const auto &segment : m_Snake.GetBody())
        {
          m_Renderer.DrawRectangle(segment.first * m_Settings.GetGridSize(), segment.second * m_Settings.GetGridSize(), m_Settings.GetGridSize(), m_Settings.GetGridSize(), 0x0052D452);
        }

        // std::pair<int, int> foodPos = m_Food.GetPosition();
        // m_Renderer.DrawRectangle(foodPos.first * m_Settings.GetGridSize(), foodPos.second * m_Settings.GetGridSize(), m_Settings.GetGridSize(), m_Settings.GetGridSize(), 0x00D45252);

        // Draw the food
        for (const auto &foodPos : m_Food.GetPosition())
        {
          m_Renderer.DrawRectangle(foodPos.first * m_Settings.GetGridSize(), foodPos.second * m_Settings.GetGridSize(), m_Settings.GetGridSize(), m_Settings.GetGridSize(), 0x00D45252);
        }
      }
      else if (!m_Running)
      {
        RenderTitleScreen();
      }
      else if (m_GameOver)
      {
        RenderGameOverScreen();
      }

      std::string title = "snek | FPS: " + std::to_string(fps);
      glfwSetWindowTitle(m_Window, title.c_str());

      ImGui::Render();
      ImGui::EndFrame(); // <-- Added
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(m_Window);
      glfwPollEvents();
    }
  }

  void Game::RenderGameOverScreen()
  {
    std::string score = "Score: " + std::to_string(m_Snake.GetScore());

    ImVec2 gameOverSize = ImGui::CalcTextSize("Game Over!");
    ImVec2 scoreSize = ImGui::CalcTextSize(score.c_str());
    ImVec2 playAgainSize = ImGui::CalcTextSize("Press <Space> to Play Again");

    // // create a window to fit the three texts
    ImGui::SetNextWindowSize(ImVec2(std::max(gameOverSize.x, std::max(scoreSize.x, playAgainSize.x)) + 20, gameOverSize.y + scoreSize.y + playAgainSize.y + 20));
    ImGui::SetNextWindowPos(ImVec2(m_Settings.GetWindowWidth() / 2, m_Settings.GetWindowHeight() / 2), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::Begin("Game Over!", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoScrollbar);

    // center the texts
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - gameOverSize.x) / 2);
    ImGui::Text("Game Over!");

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - scoreSize.x) / 2);
    ImGui::Text(score.c_str());

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - playAgainSize.x) / 2);
    ImGui::Text("Press Space to Play Again");

    ImGui::End();
  }

  void Game::RenderTitleScreen()
  {
    ImVec2 titleSize = ImGui::CalcTextSize("snek");
    ImVec2 playSize = ImGui::CalcTextSize("Press <Space> to Play");

    // create a window to fit the two texts
    ImGui::SetNextWindowSize(ImVec2(std::max(titleSize.x, playSize.x) + 20, titleSize.y + playSize.y + 20));
    ImGui::SetNextWindowPos(ImVec2(m_Settings.GetWindowWidth() / 2, m_Settings.GetWindowHeight() / 2), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::Begin("snek", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoScrollbar);

    // center the texts
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - titleSize.x) / 2);
    ImGui::Text("snek");

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - playSize.x) / 2);
    ImGui::Text("Press Space to Play");

    ImGui::End();
  }

  void Game::ProcessInput()
  {
    if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
      if (m_GameOver)
      {
        m_Snake.Reset();
        m_Food.RemoveAllFood();
        m_Food.Spawn(3);
        m_GameOver = false;
      }

      if (!m_Running)
      {
        m_Running = true;
      }
    }

    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(m_Window, true);
    }

    if (glfwGetKey(m_Window, GLFW_KEY_UP) == GLFW_PRESS)
    {
      m_Snake.ChangeDirection(GLFW_KEY_UP);
    }
    if (glfwGetKey(m_Window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
      m_Snake.ChangeDirection(GLFW_KEY_DOWN);
    }
    if (glfwGetKey(m_Window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
      m_Snake.ChangeDirection(GLFW_KEY_LEFT);
    }
    if (glfwGetKey(m_Window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
      m_Snake.ChangeDirection(GLFW_KEY_RIGHT);
    }
  }

  void Game::Update()
  {
    if (m_GameOver || !m_Running)
    {
      return;
    }

    m_Snake.Move();

    for (uint16_t i = 0; i < m_Food.GetPosition().size(); i++)
    {
      if (m_Snake.GetBody().front() == m_Food.GetPosition()[i])
      {
        m_Snake.Grow();
        m_Snake.SetScore(m_Snake.GetScore() + 1);

        m_Food.RemoveFood(i);
        m_FoodCount--;

        if (m_FoodCount < m_MaxFoodCount)
        {
          logger->info("Food count is less than max food count, spawning new food");
          m_Food.Spawn(1);
          m_FoodCount++;
        }
      }
    }

    // Check for game over
    if (m_Snake.IsCollision())
    {
      logger->info("Game Over!");
      m_GameOver = true;
    }
  }
}