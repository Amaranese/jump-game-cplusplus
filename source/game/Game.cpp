#include "../input/InputManager.hpp"
#include "../video/VideoManager.hpp"
#include "states/StartupState.hpp"

#include "Game.hpp"

Game::Game(InputManager& inputManager, VideoManager& videoManager) :
    inputManager(inputManager),
    videoManager(videoManager)
{
    // Run the StartupState initially
    gameStateManager.pushState(new StartupState);
}

void Game::run()
{
    while (!inputManager.shutdownReceived() && gameStateManager.isRunning())
    {
        // Render
        videoManager.clearScreen();
        gameStateManager.render(videoManager);
        videoManager.updateScreen();

        // Handle input
        inputManager.update();

        // Update
        gameStateManager.update();
    }
}
