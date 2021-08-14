#ifndef STARTUPSTATE_HPP
#define STARTUPSTATE_HPP

#include "../GameState.hpp"

/**
 * The game state that is initially run at program startup.
 */
class StartupState : public GameState
{
private:
    void onRender(VideoManager& video) const;
    void onUpdate();
};

#endif // STARTUPSTATE_HPP
