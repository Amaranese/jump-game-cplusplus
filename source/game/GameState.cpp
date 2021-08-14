#include "GameState.hpp"
#include "GameStateManager.hpp"

GameState::GameState() :
    gameStateManager(nullptr)
{
}

void GameState::changeState(GameState* state)
{
    popState();
    pushState(state);
}

void GameState::popState()
{
    gameStateManager->popState();
}

void GameState::pushState(GameState* state)
{
    gameStateManager->pushState(state);
}
