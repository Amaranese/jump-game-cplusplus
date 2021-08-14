#ifndef INPUTBUTTON_HPP
#define INPUTBUTTON_HPP

/**
 * Type of virtual input buttons that can be tracked.
 */
enum class InputButton : int
{
    A = 0,
    B,
    DOWN,
    LEFT,
    RIGHT,
    UP,
    START
};

/**
 * The number of input buttons.
 */
constexpr int NUM_INPUT_BUTTONS = 7;

#endif // INPUTBUTTON_HPP
