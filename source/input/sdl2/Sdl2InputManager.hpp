#ifndef SDL2INPUTMANAGER_HPP
#define SDL2INPUTMANAGER_HPP

#include <vector>

#include "../InputManager.hpp"

/**
 * Input manager using SDL2.
 */
class Sdl2InputManager : public InputManager
{
public:
    Sdl2InputManager();
    ~Sdl2InputManager();

    bool isButtonPressed(InputButton buttonId) const;

    /**
     * Map a joystick axis to an input button.
     */
    void mapJoystickAxis(int joystick, int joystickAxis, int sign, InputButton buttonId);

    /**
     * Map a joystick button to an input button.
     */
    void mapJoystickButton(int joystick, int joystickButton, InputButton buttonId);

    /**
     * Map a keyboard key to an input button.
     */
    void mapKey(SDL_Scancode key, InputButton buttonId);

    bool shutdownReceived() const;
    void update();

private:
    enum class ButtonMappingType
    {
        KEY,
        JOYSTICK_BUTTON,
        JOYSTICK_AXIS
    };

    struct ButtonMapping
    {
        ButtonMappingType type;
        InputButton buttonId;

        int joystick;
        int joystickAxisSign;
        union
        {
            SDL_Scancode key;
            int joystickButton;
            int joystickAxis;
        };
    };

    bool buttonStates[NUM_INPUT_BUTTONS];
    bool shutdownReceivedFlag;
    std::vector<SDL_Joystick*> joysticks;
    std::vector<ButtonMapping> buttonMappings;

    SDL_Joystick* getJoystick(int index);
    void setButtonPressed(InputButton buttonId);
    void setButtonReleased(InputButton buttonId);
};

#endif // SDL2INPUTMANAGER_HPP
