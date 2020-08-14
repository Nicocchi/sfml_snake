#pragma once
#include <cstdlib>
#include <ctime>
#include "window.hpp"
#include "world.hpp"
#include "snake.hpp"
#include "textbox.hpp"

class Game {
  public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();
    Window *GetWindow();

    sf::Time GetElasped();
    void RestartClock();

  private:
    Window m_window;
    sf::Clock m_clock;
    float m_elapsed;

    World m_world;
    Snake m_snake;
    Textbox m_textbox;
};