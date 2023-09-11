# Sunēku

Just playing around with C++ and OpenGL, and decided to make a Snake Game. Never really made a game before, so this is a learning experience.

## Prerequisites

Before building you'll need the following:

- C++ compiler

## Build and Run

Follow these steps to build and run the Snake Game:

```bash
git clone https://github.com/mori1704/snek.git
cd snek
.\build.bat
```

Note: When running the build script, it will automatically start the game after building.

## Todo
- [ ] Test on Linux
- [ ] A better build script, maybe CMake or something, idk.
 - [ ] There are some bugs that I need to fix, like the key input not working properly, eg. when
  you press two keys at the same time, the snake just die and triggers game over. Also, the
  food sometimes spawn inside the snake, or used to. I think I fixed it, but I'm not sure.

## Features to Implement
- [ ] Powerups
- [ ] Highscore
- [ ] Display the score and highscore while playing
- [ ] Pause
- [ ] Multiplayer?
- [ ] Levels
- [ ] Obstacles
- [ ] Portals
- [ ] Colors?

## Acknowledgements

- [GLFW](https://www.glfw.org/)
- [ImGui](https://github.com/ocornut/imgui)
- And Chat GPT of course, asked him a lot of questions lol (and some code too).