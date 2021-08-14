#include "LevelState.hpp"
#include "StartupState.hpp"

void StartupState::onRender(VideoManager& video) const
{
}

void StartupState::onUpdate()
{
    changeState(new LevelState);
}
