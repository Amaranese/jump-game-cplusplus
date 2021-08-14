#ifndef INPUTLISTENER_HPP
#define INPUTLISTENER_HPP

#include "InputButton.hpp"

/**
 * Interface for objects interested in user input events.
 */
class InputListener
{
public:
    /**
     * Event handler for button presses.
     */
    virtual void onButtonPress(InputButton buttonId) {}
};

#endif // INPUTLISTENER_HPP
