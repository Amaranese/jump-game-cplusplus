#include "../level/Block.hpp"
#include "../level/Layer.hpp"
#include "../level/Level.hpp"

#include "TestLevels.hpp"

Level* createTestLevel()
{
    Level* level = new Level();

    // Main layer
    Layer* mainLayer = new Layer(256, 15);
    for (int x = 0; x < 256; x++)
    {
        mainLayer->addBlock(x, 14, new Block(Block::CollisionType::SOLID));
        mainLayer->addBlock(x, 0, new Block(Block::CollisionType::SOLID));
    }
    for (int y = 0; y < 15; y++)
    {
        mainLayer->addBlock(0, y, new Block(Block::CollisionType::SOLID));
        mainLayer->addBlock(255, y, new Block(Block::CollisionType::SOLID));
    }
    mainLayer->addBlock(5, 13, new Block(Block::CollisionType::SLOPE_RIGHT));
    mainLayer->addBlock(6, 13, new Block(Block::CollisionType::SLOPE_LEFT));
    mainLayer->addBlock(9, 10, new Block(Block::CollisionType::SOLID));

    Block* water = new Block(Block::CollisionType::WATER);
    water->setWidth(4);
    water->setHeight(4);
    mainLayer->addBlock(15, 10, water);

    level->addLayer(mainLayer);

    return level;
}
