#pragma once

#include "../vendor/glfw/include/glfw3.h"

#include <cstdint>
#include <vector>

class Renderer
{
public:
  void DrawRectangle(float x, float y, float width, float height, uint32_t color);
  void DrawRectangle(float x, float y, float width, float height, std::vector<float> color);

  void DrawLine(float x1, float y1, float x2, float y2, uint32_t color);

  void DrawText(float x, float y, const char *text, uint32_t color, float scale = 1.0f);
  void DrawCenteredText(float x, float y, const char *text, uint32_t color, float scale = 1.0f);

  void DrawGridLines();
};