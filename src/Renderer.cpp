#include "Renderer.h"
#include "GameSettings.h"

#include "../vendor/imgui/imgui.h"

#include <cstring>

void Renderer::DrawRectangle(float x, float y, float width, float height, uint32_t color)
{
  glBegin(GL_QUADS);
  glColor4f(((color >> 16) & 0xFF) / 255.0f, ((color >> 8) & 0xFF) / 255.0f, (color & 0xFF) / 255.0f, ((color >> 24) & 0xFF) / 255.0f);
  glVertex2f(x, y);
  glVertex2f(x + width, y);
  glVertex2f(x + width, y + height);
  glVertex2f(x, y + height);
  glEnd();
}

void Renderer::DrawRectangle(float x, float y, float width, float height, std::vector<float> color)
{
  glBegin(GL_QUADS);
  glColor4f(color[0], color[1], color[2], color[3]);
  glVertex2f(x, y);
  glVertex2f(x + width, y);
  glVertex2f(x + width, y + height);
  glVertex2f(x, y + height);
  glEnd();
}

void Renderer::DrawGridLines()
{
  snek::GameSettings &settings = snek::GameSettings::getInstance();
  int windowWidth = settings.GetWindowWidth();
  int windowHeight = settings.GetWindowHeight();
  int gridSize = settings.GetGridSize();

  glColor4f(1.0f, 1.0f, 1.0f, 0.2f);

  for (int x = 0; x <= windowWidth; x += gridSize)
  {
    glBegin(GL_LINES);
    glVertex2f(x, 0);
    glVertex2f(x, windowHeight);
    glEnd();
  }

  // Draw horizontal grid borders
  for (int y = 0; y <= windowHeight; y += gridSize)
  {
    glBegin(GL_LINES);
    glVertex2f(0, y);
    glVertex2f(windowWidth, y);
    glEnd();
  }
}

void Renderer::DrawLine(float x1, float y1, float x2, float y2, uint32_t color)
{
  float red = ((color >> 24) & 0xFF) / 255.0f;
  float green = ((color >> 16) & 0xFF) / 255.0f;
  float blue = ((color >> 8) & 0xFF) / 255.0f;
  float alpha = (color & 0xFF) / 255.0f;

  glBegin(GL_LINES);
  // glColor3f(((color >> 16) & 0xFF) / 255.0f, ((color >> 8) & 0xFF) / 255.0f, (color & 0xFF) / 255.0f);
  // 0x66FFFFFF
  glColor4f(red, green, blue, alpha);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  glEnd();
}

void Renderer::DrawText(float x, float y, const char *text, uint32_t color, float scale)
{
  ImGui::SetNextWindowPos(ImVec2(x, y));

  ImGui::Begin("TextOverlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);

  ImGui::TextColored(ImVec4(((color >> 16) & 0xFF) / 255.0f, ((color >> 8) & 0xFF) / 255.0f, (color & 0xFF) / 255.0f, ((color >> 24) & 0xFF) / 255.0f), "%s", text);
  ImGui::SetWindowFontScale(scale);

  ImGui::End();
}