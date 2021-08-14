#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <list>

#include "InputButton.hpp"

class InputListener;

/**
 * Interface for abstracting user input.
 */
class InputManager
{
public:
    virtual ~InputManager() {}

    /**
     * Add an input listener that subscribes to input events.
     */
    void addListener(InputListener* listener);

    /**
     * Get the singleton instance of the Input Manager.
     */
    static InputManager& getInstance();

    /**
     * Get the state of a button.
     *
     * @return true if the button is pressed.
     */
    virtual bool isButtonPressed(InputButton buttonId) const =0;

    /**
     * Remove an input listener from event subscriptions.
     */
    void removeListener(InputListener* listener);

    /**
     * Check if the user requested to close/kill the program.
     */
    virtual bool shutdownReceived() const =0;

    /**
     * Update the input system's state.
     */
    virtual void update()=0;

protected:
    /**
     * Notify listeners that a button was pressed.
     */
    void notifyButtonPress(InputButton buttonId);

    /**
     * Set the singleton instance of the Input Manager.
     */
    static void setInstance(InputManager* newInstance);

private:
    static InputManager* instance;
    std::list<InputListener*> listeners;
};

#endif // INPUTMANAGER_HPP
