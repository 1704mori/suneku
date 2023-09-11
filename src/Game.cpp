#include "Game.h"
#include "Entity.h"

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

namespace snek
{
  Game::Game(GLFWwindow *window) : m_Window(window), m_GameOver(false)
  {
    glfwSetWindowUserPointer(m_Window, this);

    keyCallback = [](GLFWwindow *window, int key, int scancode, int action, int mods)
    {
      Game *game = static_cast<Game *>(glfwGetWindowUserPointer(window));
      if (game)
      {
        game->ProcessInput(key, action);
      }
    };

    logger = new common::Logger("Game", false);

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init();

    m_Food = new Entity(EntityType::Food);
    m_Food->Spawn();
    m_FoodCount = m_Food->Count();

    m_Pickups = new Entity(EntityType::Pickups);
    m_Pickups->Spawn();

    // m_Food.Spawn();
    // m_FoodCount = m_Food.GetPosition().size();

    // logger->info(std::to_string(m_FoodCount) + " food(s) spawned");
    // logger->info("Score: " + std::to_string(GetScore()));
    logger->info("Initialized");
    logger->info("Max food count: " + std::to_string(m_MaxFoodCount));
    logger->info("Food spawn time: " + std::to_string(m_FoodSpawnTime));
    logger->info("Food count: " + std::to_string(m_FoodCount));
    logger->info("Score: " + std::to_string(GetScore()));
  }

  void Game::Run()
  {
    double lastFrameTime = glfwGetTime();
    double deltaTime = 0;

    glfwSetKeyCallback(m_Window, keyCallback);

    while (!glfwWindowShouldClose(m_Window))
    {
      double currentTime = glfwGetTime();
      deltaTime += currentTime - lastFrameTime;
      lastFrameTime = currentTime;
      double fps = 1.0 / deltaTime;

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

        for (const auto &foodPos : m_Food->GetPosition())
        {
          m_Renderer.DrawRectangle(foodPos.first * m_Settings.GetGridSize(), foodPos.second * m_Settings.GetGridSize(), m_Settings.GetGridSize(), m_Settings.GetGridSize(), 0x00D45252);
        }

        for (const auto &pickupPos : m_Pickups->GetPosition())
        {
          m_Renderer.DrawRectangle(pickupPos.first * m_Settings.GetGridSize(), pickupPos.second * m_Settings.GetGridSize(), m_Settings.GetGridSize(), m_Settings.GetGridSize(), 0x00D4CE52);
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
    std::string score = "Score: " + std::to_string(GetScore());

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

  void Game::ProcessInput(int key, int action)
  {
    if (action != GLFW_PRESS)
      return;

    switch (key)
    {
    case GLFW_KEY_ESCAPE:
      glfwSetWindowShouldClose(m_Window, true);
      break;
    case GLFW_KEY_UP:
    case GLFW_KEY_W:
    case GLFW_KEY_KP_8:
      m_Snake.ChangeDirection(GLFW_KEY_UP);
      break;
    case GLFW_KEY_DOWN:
    case GLFW_KEY_S:
    case GLFW_KEY_KP_2:
      m_Snake.ChangeDirection(GLFW_KEY_DOWN);
      break;
    case GLFW_KEY_LEFT:
    case GLFW_KEY_A:
    case GLFW_KEY_KP_4:
      m_Snake.ChangeDirection(GLFW_KEY_LEFT);
      break;
    case GLFW_KEY_RIGHT:
    case GLFW_KEY_D:
    case GLFW_KEY_KP_6:
      m_Snake.ChangeDirection(GLFW_KEY_RIGHT);
      break;
    case GLFW_KEY_SPACE:
      if (m_GameOver)
      {
        m_Snake.Reset();
        m_Food->RemoveAll();
        m_Food->Spawn();
        m_GameOver = false;
      }

      if (!m_Running)
      {
        m_Running = true;
      }
      break;

    default:
      break;
    }
  }

  void Game::Update()
  {
    if (m_GameOver || !m_Running)
    {
      return;
    }

    m_Snake.Move();

    for (uint16_t i = 0; i < m_Food->GetPosition().size(); i++)
    {
      if (m_Snake.GetBody().front().first == m_Food->GetPosition()[i].first && m_Snake.GetBody().front().second == m_Food->GetPosition()[i].second)
      {
        m_Snake.Grow();
        SetScore(GetScore() + 1);

        m_Food->Remove(i);
        m_FoodCount--;

        if (m_MaxFoodCount == 1)
        {
          SetMaxFoodCount(5);
          logger->info("Max food count is now 5");
        }
      }
    }

    m_FoodSpawnTimer += GAME_SPEED;

    if (m_FoodCount < m_MaxFoodCount && m_FoodSpawnTimer >= m_FoodSpawnTime)
    {
      m_FoodSpawnTimer = 0;
      m_Food->Spawn();
      m_FoodCount++;
    }

    // Check for game over
    if (m_Snake.IsCollision())
    {
      logger->info("Game Over!");
      logger->clear();
      m_GameOver = true;
    }
  }
}