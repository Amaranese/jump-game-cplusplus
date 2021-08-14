#include "../../input/InputManager.hpp"
#include "../../level/Entity.hpp"
#include "../../level/Level.hpp"
#include "../../level/entities/Player.hpp"
#include "../../test/TestLevels.hpp"
#include "../../video/VideoManager.hpp"

#include "LevelState.hpp"

LevelState::LevelState()
{
    level = createTestLevel();

    player = new Player();
    InputManager::getInstance().addListener(player);
    player->setX(Level::TILE_SIZE);
    player->setY(Level::TILE_SIZE);
    level->addEntity(player);
}

LevelState::~LevelState()
{
    InputManager::getInstance().removeListener(player);
    delete level;
}

void LevelState::onRender(VideoManager& video) const
{
    level->render(video, 0, video.getScreenWidth(), 0, video.getScreenHeight());
}

void LevelState::onUpdate()
{
    level->update();
}
