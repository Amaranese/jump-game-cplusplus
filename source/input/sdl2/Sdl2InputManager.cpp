#include <iostream>

#include <SDL2/SDL.h>

#include "Sdl2InputManager.hpp"

Sdl2InputManager::Sdl2InputManager() :
    shutdownReceivedFlag(false)
{
    for (auto& state : buttonStates)
    {
        state = false;
    }

    // Open all joysticks for use
    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        SDL_Joystick* joystick = SDL_JoystickOpen(i);
        if (joystick)
        {
            std::cout << "Opened joystick " << i << " for use.\n";
        }
        else
        {
            std::cout << "Warning: failed to open joystick " << i << std::endl;
        }
        joysticks.push_back(joystick);
    }

    setInstance(this);
}

Sdl2InputManager::~Sdl2InputManager()
{
    for (auto joystick : joysticks)
    {
        SDL_JoystickClose(joystick);
    }
}

SDL_Joystick* Sdl2InputManager::getJoystick(int index)
{
    if (index < 0 || index >= (int)joysticks.size())
    {
        return NULL;
    }
    return joysticks[index];
}

bool Sdl2InputManager::isButtonPressed(InputButton buttonId) const
{
    return buttonStates[(int)buttonId];
}

void Sdl2InputManager::mapKey(SDL_Scancode key, InputButton buttonId)
{
    ButtonMapping mapping;
    mapping.type = ButtonMappingType::KEY;
    mapping.key = key;
    mapping.buttonId = buttonId;
    buttonMappings.push_back(mapping);
}

void Sdl2InputManager::mapJoystickAxis(int joystick, int joystickAxis, int sign, InputButton buttonId)
{
    ButtonMapping mapping;
    mapping.type = ButtonMappingType::JOYSTICK_AXIS;
    mapping.joystick = joystick;
    mapping.joystickAxis = joystickAxis;
    mapping.joystickAxisSign = sign;
    mapping.buttonId = buttonId;
    buttonMappings.push_back(mapping);
}

void Sdl2InputManager::mapJoystickButton(int joystick, int joystickButton, InputButton buttonId)
{
    ButtonMapping mapping;
    mapping.type = ButtonMappingType::JOYSTICK_BUTTON;
    mapping.joystick = joystick;
    mapping.joystickButton = joystickButton;
    mapping.buttonId = buttonId;
    buttonMappings.push_back(mapping);
}

void Sdl2InputManager::setButtonPressed(InputButton buttonId)
{
    if (!buttonStates[(int)buttonId])
    {
        notifyButtonPress(buttonId);
    }
    buttonStates[(int)buttonId] = true;
}

void Sdl2InputManager::setButtonReleased(InputButton buttonId)
{
    buttonStates[(int)buttonId] = false;
}

bool Sdl2InputManager::shutdownReceived() const
{
    return shutdownReceivedFlag;
}

void Sdl2InputManager::update()
{
    // Poll SDL events
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                shutdownReceivedFlag = true;
                break;
            default:
                break;
            }
            break;

        case SDL_QUIT:
            shutdownReceivedFlag = true;
            break;

        default:
            break;
        }
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    bool buttonStatus[NUM_INPUT_BUTTONS];
    for (auto& b : buttonStatus)
    {
        b = false;
    }

    // Poll input mappings
    for (auto mapping : buttonMappings)
    {
        bool state = false;
        switch(mapping.type)
        {
        case ButtonMappingType::KEY:
            if (keystates[mapping.key])
            {
                state = true;
            }
            break;
        case ButtonMappingType::JOYSTICK_AXIS:
            {
                SDL_Joystick* joystick = getJoystick(mapping.joystick);
                if (!joystick)
                {
                    break;
                }
                Sint16 axisState = SDL_JoystickGetAxis(joystick, mapping.joystickAxis);
                if (mapping.joystickAxisSign < 0)
                {
                    state = (axisState < -16384);
                }
                else
                {
                    state = (axisState > 16384);
                }
            }
            break;
        case ButtonMappingType::JOYSTICK_BUTTON:
            {
                SDL_Joystick* joystick = getJoystick(mapping.joystick);
                if (!joystick)
                {
                    break;
                }
                state = (SDL_JoystickGetButton(joystick, mapping.joystickButton) != 0);
            }
            break;
        }

        buttonStatus[(int)mapping.buttonId] |= state;
    }

    // Update input button states
    for (int i = 0; i < NUM_INPUT_BUTTONS; i++)
    {
        if (buttonStatus[i])
        {
            setButtonPressed((InputButton)i);
        }
        else
        {
            setButtonReleased((InputButton)i);
        }
    }
}
