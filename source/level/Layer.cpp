#include <cmath>
#include <set>

#include "Block.hpp"
#include "Layer.hpp"
#include "Level.hpp"

Layer::Layer(int width, int height) :
    width(width),
    height(height),
    positionX(0.0f),
    positionY(0.0f),
    velocityX(0.0f),
    velocityY(0.0f)
{
    blocks.resize(width * height, nullptr);
}

Layer::~Layer()
{
    // Find all blocks in the layer
    std::set<Block*> blockSet;
    for (auto block : blocks)
    {
        if (block != nullptr)
        {
            blockSet.insert(block);
        }
    }

    // And then free them
    for (auto block : blockSet)
    {
        delete block;
    }
}

void Layer::addBlock(int x, int y, Block* block)
{
    if (block == nullptr)
    {
        return;
    }

    block->positionX = x;
    block->positionY = y;

    for (int yIndex = 0; yIndex < block->height; yIndex++)
    {
        for (int xIndex = 0; xIndex < block->width; xIndex++)
        {
            int xOffset = x + xIndex;
            int yOffset = y + yIndex;
            if (xOffset < 0 || xOffset >= width || yOffset < 0 || yOffset >= height)
            {
                // TODO: should this be an error if we try to insert a block out of bounds?
                continue;
            }

            blocks[yOffset * width + xOffset] = block;
        }
    }
}

Block* Layer::getBlock(int x, int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        return nullptr;
    }
    return blocks[y * width + x];
}

const Block* Layer::getBlock(int x, int y) const
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        return nullptr;
    }
    return blocks[y * width + x];
}

Block* Layer::getBlockAt(int x, int y)
{
    // Convert to local coordinates
    x -= getX();
    y -= getY();
    if (x < 0 || y < 0)
    {
        return nullptr;
    }
    return getBlock(x / Level::TILE_SIZE, y / Level::TILE_SIZE);
}

const Block* Layer::getBlockAt(int x, int y) const
{
    // Convert to local coordinates
    x -= getX();
    y -= getY();
    if (x < 0 || y < 0)
    {
        return nullptr;
    }
    return getBlock(x / Level::TILE_SIZE, y / Level::TILE_SIZE);
}

int Layer::getX() const
{
    return static_cast<int>(std::floor(positionX));
}

int Layer::getY() const
{
    return static_cast<int>(std::floor(positionY));
}

bool Layer::hasBottomCollision(int x, int y) const
{
    auto block = getBlockAt(x, y);
    if (block == nullptr)
    {
        return false;
    }

    // Translate to local coordinates
    x -= getX();
    y -= getY();

    // Translate to block coordinates
    return block->hasBottomCollision(x - block->getX(), y - block->getY());
}

bool Layer::hasLeftCollision(int x, int y) const
{
    auto block = getBlockAt(x, y);
    if (block == nullptr)
    {
        return false;
    }

    // Translate to local coordinates
    x -= getX();
    y -= getY();

    // Translate to block coordinates
    return block->hasLeftCollision(x - block->getX(), y - block->getY());
}

bool Layer::hasRightCollision(int x, int y) const
{
    auto block = getBlockAt(x, y);
    if (block == nullptr)
    {
        return false;
    }

    // Translate to local coordinates
    x -= getX();
    y -= getY();

    // Translate to block coordinates
    return block->hasRightCollision(x - block->getX(), y - block->getY());
}

bool Layer::hasSlopeCollision(int x, int y) const
{
    auto block = getBlockAt(x, y);
    if (block == nullptr)
    {
        return false;
    }

    // Translate to local coordinates
    x -= getX();
    y -= getY();

    // Translate to block coordinates
    return block->hasSlopeCollision(x - block->getX(), y - block->getY());
}

bool Layer::hasTopCollision(int x, int y) const
{
    auto block = getBlockAt(x, y);
    if (block == nullptr)
    {
        return false;
    }

    // Translate to local coordinates
    x -= getX();
    y -= getY();

    // Translate to block coordinates
    return block->hasTopCollision(x - block->getX(), y - block->getY());
}

void Layer::setVelocityX(float vx)
{
    velocityX = vx;
}

void Layer::setVelocityY(float vy)
{
    velocityY = vy;
}

void Layer::setX(float x)
{
    positionX = x;
}

void Layer::setY(float y)
{
    positionY = y;
}
