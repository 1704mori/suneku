@echo off
set SRC_DIR=src
set BUILD_DIR=build
set VENDOR_DIR=vendor

rem Ensure the build directory exists
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

taskkill /f /im snake.exe

rem Compiler and linker flags
set CXX=g++
set CXXFLAGS=-std=c++17 -I%VENDOR_DIR%/glfw/include -I%VENDOR_DIR%/imgui
set LDFLAGS=-L%VENDOR_DIR%/glfw/lib -lglfw3 -lopengl32 -lgdi32 -limm32

rem List of source files
set SOURCES=%SRC_DIR%/main.cpp %SRC_DIR%/Game.cpp %SRC_DIR%/Snake.cpp %SRC_DIR%/Entity.cpp %SRC_DIR%/Renderer.cpp %SRC_DIR%/common/Logger.cpp vendor/imgui/imgui.cpp vendor/imgui/imgui_draw.cpp vendor/imgui/imgui_impl_glfw.cpp vendor/imgui/imgui_impl_opengl3.cpp vendor/imgui/imgui_widgets.cpp vendor/imgui/imgui_tables.cpp

rem Output executable file
set OUTPUT=%BUILD_DIR%/snake.exe

echo Building Snake Game...

rem Compile and link the project
%cxx% %CXXFLAGS% %SOURCES% %LDFLAGS% -o %OUTPUT%

if %errorlevel% neq 0 (
  echo Build failed.
  exit /b %errorlevel%
)

echo Build succeeded. Executable: %OUTPUT%

start /d %BUILD_DIR% snake.exe

rem Pause to keep the console window open for viewing build results
@REM pause
