#include "game.hpp"

int main(int argc, void** argv[]) {
    // Program entry point
    Game game;

    while (!game.GetWindow()->IsDone()) {
        game.HandleInput();
        game.Update();
        game.Render();
        game.RestartClock();
    }
}