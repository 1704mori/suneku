#include <iostream>
#include "../vendor/glfw/include/glfw3.h"
#include "Game.h"
#include "GameSettings.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  snek::GameSettings &settings = snek::GameSettings::getInstance();

  settings.UpdateWindowSize(width, height);

  glViewport(0, 0, settings.GetWindowWidth(), settings.GetWindowHeight());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, settings.GetWindowWidth(), 0, settings.GetWindowHeight(), -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main()
{
  if (!glfwInit())
  {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  GLFWwindow *window = glfwCreateWindow(snek::GameSettings::getInstance().GetWindowWidth(),
                                        snek::GameSettings::getInstance().GetWindowHeight(),
                                        "Snake Game", nullptr, nullptr);
  if (!window)
  {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glOrtho(0, wW, 0, wH, -1, 1);
  glOrtho(0, snek::GameSettings::getInstance().GetWindowWidth(), 0, snek::GameSettings::getInstance().GetWindowHeight(), -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  snek::Game game(window);
  game.Run();

  glfwTerminate();

  // todo: clean up imgui stuff
  return 0;
}
