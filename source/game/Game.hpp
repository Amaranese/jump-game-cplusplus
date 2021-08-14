#ifndef GAME_HPP
#define GAME_HPP

#include "GameStateManager.hpp"

class InputManager;
class VideoManager;

/**
 * Main class that manages the flow of the program.
 */
class Game
{
public:
    /**
     * Constructor.
     */
    Game(InputManager& inputManager, VideoManager& videoManager);

    /**
     * Run the game.
     */
    void run();

private:
    GameStateManager gameStateManager;
    InputManager& inputManager;
    VideoManager& videoManager;
};

#endif // GAME_HPP
