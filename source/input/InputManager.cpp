#include "InputListener.hpp"
#include "InputManager.hpp"

InputManager* InputManager::instance = nullptr;

void InputManager::addListener(InputListener* listener)
{
    listeners.push_back(listener);
}

InputManager& InputManager::getInstance()
{
    return *instance;
}

void InputManager::notifyButtonPress(InputButton buttonId)
{
    for (auto listener : listeners)
    {
        listener->onButtonPress(buttonId);
    }
}

void InputManager::removeListener(InputListener* listener)
{
    listeners.remove(listener);
}

void InputManager::setInstance(InputManager* newInstance)
{
    instance = newInstance;
}
