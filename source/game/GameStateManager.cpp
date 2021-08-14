#include "GameState.hpp"
#include "GameStateManager.hpp"

GameStateManager::~GameStateManager()
{
    // Free all game states
    for (auto state : stateStack)
    {
        delete state;
    }
}

bool GameStateManager::isRunning() const
{
    return !stateStack.empty();
}

void GameStateManager::popState()
{
    if (!stateStack.empty())
    {
        GameState* state = stateStack.back();
        deadStates.insert(state);
        stateStack.pop_back();
    }
}

void GameStateManager::pushState(GameState* state)
{
    state->gameStateManager = this;
    stateStack.push_back(state);
}

void GameStateManager::render(VideoManager& videoManager) const
{
    if (!stateStack.empty())
    {
        GameState* state = stateStack.back();
        state->onRender(videoManager);
    }
}

void GameStateManager::update()
{
    if (!stateStack.empty())
    {
        GameState* state = stateStack.front();
        state->onUpdate();
    }

    // Remove any dead game states
    for (auto state : deadStates)
    {
        delete state;
    }
    deadStates.clear();
}
