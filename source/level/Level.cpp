#include <cmath>
#include <set>

#include "../video/VideoManager.hpp"

#include "Block.hpp"
#include "Entity.hpp"
#include "Layer.hpp"
#include "Level.hpp"

Level::Level()
{
}

Level::~Level()
{
    // Free all layers
    for (auto layer : layers)
    {
        delete layer;
    }

    // Free all entities
    for (auto entity : entities)
    {
        delete entity;
    }
}

void Level::addEntity(Entity* entity)
{
    entity->level = this;
    entities.push_back(entity);
}

void Level::addLayer(Layer* layer)
{
    layers.push_back(layer);
}

bool Level::canEntityMoveDown(Entity& entity) const
{
    // Check for blocks below
    for (auto layer : layers)
    {
        if (layer->hasSlopeCollision(entity.getCenterX(), entity.getBottom() + 1))
        {
            return false;
        }
        // TODO: does this have to be every x coordinate?
        for (int x = 0; x < entity.width; x++)
        {
            if (layer->hasTopCollision(entity.getLeft() + x, entity.getBottom() + 1))
            {
                return false;
            }
        }
    }
    return true;
}

bool Level::canEntityMoveLeft(Entity& entity) const
{
    // Check for blocks to the left
    for (auto layer : layers)
    {
        // TODO: this doesn't have to be every single y coordinate. Just once every 16 pixels
        for (int y = 0; y < entity.height; y++)
        {
            if (layer->hasRightCollision(entity.getLeft() - 1, entity.getTop() + y))
            {
                return false;
            }
        }
    }

    return true;
}

bool Level::canEntityMoveRight(Entity& entity) const
{
    // Check for blocks to the right
    for (auto layer : layers)
    {
        // TODO: this doesn't have to be every single y coordinate. Just once every 16 pixels
        for (int y = 0; y < entity.height; y++)
        {
            if (layer->hasLeftCollision(entity.getRight() + 1, entity.getTop() + y))
            {
                return false;
            }
        }
    }

    return true;
}

bool Level::canEntityMoveUp(Entity& entity) const
{
    // Check for blocks above
    for (auto layer : layers)
    {
        // TODO: does this have to be every x coordinate?
        for (int x = 0; x < entity.width; x++)
        {
            if (layer->hasBottomCollision(entity.getLeft() + x, entity.getTop() - 1))
            {
                return false;
            }
        }
    }
    return true;
}

bool Level::isEntityOnGround(const Entity& entity) const
{
    for (auto layer : layers)
    {
        if (isEntityStandingOnLayer(*layer, entity))
        {
            return true;
        }
    }
    return false;
}

bool Level::isEntityStandingOnLayer(const Layer& layer, const Entity& entity) const
{
    // Check the bottom pixels of the entity's bounding box
    // TODO: we can probably only check every 16 pixels/the center to save time here
    if (layer.hasSlopeCollision(entity.getCenterX(), entity.getBottom() + 1))
    {
        return true;
    }
    for (int x = 0; x < entity.width; x++)
    {
        if (layer.hasTopCollision(entity.getLeft() + x, entity.getBottom() + 1))
        {
            return true;
        }
    }
    return false;
}

bool Level::isUnderwaterAt(int x, int y) const
{
    for (auto layer : layers)
    {
        const Block* block = layer->getBlockAt(x, y);
        if (block != nullptr && block->collisionType == Block::CollisionType::WATER)
        {
            return true;
        }
    }
    return false;
}

bool Level::moveEntityDown(Entity& entity)
{
    if (canEntityMoveDown(entity))
    {
        moveEntityY(entity, 1.0f);
        return true;
    }
    return false;
}

bool Level::moveEntityLeft(Entity& entity)
{
    if (canEntityMoveLeft(entity))
    {
        moveEntityX(entity, -1.0f);
        return true;
    }
    return false;
}

bool Level::moveEntityRight(Entity& entity)
{
    if (canEntityMoveRight(entity))
    {
        moveEntityX(entity, 1.0f);
        return true;
    }
    return false;
}

bool Level::moveEntityUp(Entity& entity)
{
    if (canEntityMoveUp(entity))
    {
        moveEntityY(entity, -1.0f);
        return true;
    }
    return false;
}

void Level::moveEntityX(Entity& entity, float dx)
{
    int newCenterX;
    if (dx > 0)
    {
        newCenterX = entity.getCenterX() + 1;
    }
    else
    {
        newCenterX = entity.getCenterX() - 1;
    }

    // Go up/down slopes
    for (auto layer : layers)
    {
        // Are we standing on the layer with our center pixel?
        if (!isEntityStandingOnLayer(*layer, entity))
        {
            // If not, ignore it since this doesn't apply
            continue;
        }

        // Go up slopes that we run into
        if (layer->hasSlopeCollision(newCenterX, entity.getBottom()))
        {
            entity.positionX += dx;
            moveEntityUp(entity);
            return;
        }

        // Go down slopes that we run into
        if (layer->hasSlopeCollision(newCenterX, entity.getBottom() + 2))
        {
            entity.positionX += dx;
            moveEntityY(entity, 1.0f); // Intentional: forced sinking. This may become a bug.
            return;
        }
    }

    entity.positionX += dx;
}

void Level::moveEntityY(Entity& entity, float dy)
{
    entity.positionY += dy;
}

void Level::moveLayerDown(Layer& layer)
{
    // Move any entities that are standing on this layer or colliding with the bottom edge of it
    for (auto entity : entities)
    {
        if (isEntityStandingOnLayer(layer, *entity))
        {
            // A bit of a hack here: we need to move the layer "out of the way"
            // to move the entity down (otherwise the layer will get in the way
            // of the entity's movement). So we temporarily adjust the layer's
            // position and change it back after we move the entity.
            float positionY = layer.positionY++;
            moveEntityDown(*entity);
            layer.positionY = positionY;
            continue;
        }
        for (int x = 0; x < entity->width; x++)
        {
            if (layer.hasBottomCollision(entity->getLeft() + x, entity->getTop() - 1))
            {
                moveEntityDown(*entity);
                break;
            }
        }
    }
    layer.positionY++;
}

void Level::moveLayerLeft(Layer& layer)
{
    // Move any entities that are standing on this layer or colliding with the left edge of it
    for (auto entity : entities)
    {
        if (isEntityStandingOnLayer(layer, *entity))
        {
            if (canEntityMoveLeft(*entity))
            {
                // Simply move to the left (no need to handle slopes)
                entity->positionX--;
            }
            continue;
        }
        for (int y = 0; y < entity->height; y++)
        {
            if (layer.hasLeftCollision(entity->getRight() + 1, entity->getTop() + y))
            {
                moveEntityLeft(*entity);
                break;
            }
        }
    }
    layer.positionX--;

    // Catch any entities that got shoved into a slope (very rare)
    // Usually happens when an entity is on a slope that moves into another layer
    for (auto entity : entities)
    {
        if (layer.hasSlopeCollision(entity->getCenterX(), entity->getBottom()))
        {
            moveEntityUp(*entity);
        }
    }
}

void Level::moveLayerRight(Layer& layer)
{
    // Move any entities that are standing on this layer or colliding with the right edge of it
    for (auto entity : entities)
    {
        if (isEntityStandingOnLayer(layer, *entity))
        {
            if (canEntityMoveRight(*entity))
            {
                // Simply move to the right (no need to handle slopes)
                entity->positionX++;
            }
            continue;
        }
        for (int y = 0; y < entity->height; y++)
        {
            if (layer.hasRightCollision(entity->getLeft() - 1, entity->getTop() + y))
            {
                moveEntityRight(*entity);
                break;
            }
        }
    }
    layer.positionX++;

    // Catch any entities that got shoved into a slope (very rare)
    // Usually happens when an entity is on a slope that moves into another layer
    for (auto entity : entities)
    {
        if (layer.hasSlopeCollision(entity->getCenterX(), entity->getBottom()))
        {
            moveEntityUp(*entity);
        }
    }
}

void Level::moveLayerUp(Layer& layer)
{
    // Move any entities that are standing on this layer
    for (auto entity : entities)
    {
        if (isEntityStandingOnLayer(layer, *entity))
        {
            moveEntityUp(*entity);
        }
    }
    layer.positionY--;
}

void Level::render(VideoManager& video, int left, int right, int top, int bottom) const
{
    // Render all blocks
    for (auto layer : layers)
    {
        std::set<Block*> blocks;
        for (int x = left; x < right + TILE_SIZE; x += TILE_SIZE)
        {
            for (int y = top; y < bottom + TILE_SIZE; y += TILE_SIZE)
            {
                auto block = layer->getBlockAt(x, y);
                if (block != nullptr)
                {
                    blocks.insert(block);
                }
            }
        }

        int xOffset = layer->getX() - left;
        int yOffset = layer->getY() - top;
        for (auto block : blocks)
        {
            video.setColor(0x00ff00);
            switch (block->collisionType)
            {
            case Block::CollisionType::SLOPE_LEFT:
                video.drawLine(
                    block->getRight() + 1 + xOffset, block->getBottom() + 1 + yOffset,
                    block->getLeft() + xOffset, block->getTop() + yOffset
                );
                break;
            case Block::CollisionType::SLOPE_RIGHT:
                video.drawLine(
                    block->getLeft() + xOffset, block->getBottom() + 1 + yOffset,
                    block->getRight() + 1 + xOffset, block->getTop() + yOffset
                );
                break;
            case Block::CollisionType::SOLID:
                video.drawRectangle(
                    block->getX() + xOffset,
                    block->getY() + yOffset,
                    block->getWidth(),
                    block->getHeight()
                );
                break;
            case Block::CollisionType::PLATFORM:
                video.drawLine(
                    block->getLeft() + xOffset, block->getTop() + yOffset,
                    block->getRight() + 1 + xOffset, block->getTop() + yOffset);
                break;
            case Block::CollisionType::WATER:
                video.setColor(0x0000ff);
                video.drawRectangle(
                    block->getX() + xOffset,
                    block->getY() + yOffset,
                    block->getWidth(),
                    block->getHeight()
                );
                break;

            default:
                break;
            }
        }
    }

    // Render all entities
    for (auto entity : entities)
    {
        video.setColor(0xff0000);
        video.drawRectangle(entity->getX(), entity->getY(), entity->width, entity->height);
    }
}

void Level::update()
{
    // Update all layers
    for (auto layer : layers)
    {
        updateLayer(*layer);
    }

    // Update all entities
    for (auto entity : entities)
    {
        updateEntity(*entity);
    }
}

void Level::updateEntity(Entity& entity)
{
    entity.velocityX += entity.accelerationX;
    updateEntityMotionX(entity);
    entity.velocityY += entity.accelerationY;
    updateEntityMotionY(entity);

    entity.onUpdate();
}

void Level::updateEntityMotionX(Entity& entity)
{
    // Move left/right one pixel at a time
    float dx = entity.velocityX;
    while (dx >= 1.0f)
    {
        if (moveEntityRight(entity))
        {
            dx--;
        }
        else
        {
            entity.velocityX = 0.0f;
            return;
        }
    }
    if (dx > 0.0f)
    {
        if (std::floor(entity.positionX + dx) == std::floor(entity.positionX + 1))
        {
            if (canEntityMoveRight(entity))
            {
                moveEntityX(entity, dx);
            }
            else
            {
                entity.velocityX = 0.0f;
                return;
            }
        }
        else
        {
            entity.positionX += dx;
        }
        return;
    }
    while (dx <= -1.0f)
    {
        if (moveEntityLeft(entity))
        {
            dx++;
        }
        else
        {
            entity.velocityX = 0.0f;
            return;
        }
    }
    if (dx < 0.0f)
    {
        if (std::floor(entity.positionX + dx) == std::floor(entity.positionX - 1))
        {
            if (canEntityMoveLeft(entity))
            {
                moveEntityX(entity, dx);
            }
            else
            {
                entity.velocityX = 0.0f;
                return;
            }
        }
        else
        {
            entity.positionX += dx;
        }
        return;
    }
}

void Level::updateEntityMotionY(Entity& entity)
{
    // Move up/down one pixel at a time
    float dy = entity.velocityY;
    while (dy >= 1.0f)
    {
        if (moveEntityDown(entity))
        {
            dy--;
        }
        else
        {
            entity.velocityY = 0.0f;
            return;
        }
    }
    if (dy > 0.0f)
    {
        if (std::floor(entity.positionY + dy) == std::floor(entity.positionY + 1))
        {
            if (canEntityMoveDown(entity))
            {
                moveEntityY(entity, dy);
            }
            else
            {
                entity.velocityY = 0.0f;
                return;
            }
        }
        else
        {
            entity.positionY += dy;
        }
        return;
    }
    while (dy <= -1.0f)
    {
        if (moveEntityUp(entity))
        {
            dy++;
        }
        else
        {
            entity.velocityY = 0.0f;
            return;
        }
    }
    if (dy < 0.0f)
    {
        if (std::floor(entity.positionY + dy) == std::floor(entity.positionY - 1))
        {
            if (canEntityMoveUp(entity))
            {
                moveEntityY(entity, dy);
            }
            else
            {
                entity.velocityY = 0.0f;
                return;
            }
        }
        else
        {
            entity.positionY += dy;
        }
        return;
    }
}

void Level::updateLayer(Layer& layer)
{
    updateLayerMotionX(layer);
    updateLayerMotionY(layer);
}

void Level::updateLayerMotionX(Layer& layer)
{
    // Move left/right one pixel at a time
    float dx = layer.velocityX;
    while (dx >= 1.0f)
    {
        moveLayerRight(layer);
        dx--;
    }
    if (dx > 0.0f)
    {
        if (std::floor(layer.positionX + dx) == std::floor(layer.positionX + 1))
        {
            moveLayerRight(layer);
            layer.positionX--;
        }
        layer.positionX += dx;
        return;
    }
    while (dx <= -1.0f)
    {
        moveLayerLeft(layer);
        dx++;
    }
    if (dx < 0.0f)
    {
        if (std::floor(layer.positionX + dx) == std::floor(layer.positionX - 1))
        {
            moveLayerLeft(layer);
            layer.positionX++;
        }
        layer.positionX += dx;
        return;
    }
}

void Level::updateLayerMotionY(Layer& layer)
{
    // Move up/down one pixel at a time
    float dy = layer.velocityY;
    while (dy >= 1.0f)
    {
        moveLayerDown(layer);
        dy--;
    }
    if (dy > 0.0f)
    {
        if (std::floor(layer.positionY + dy) == std::floor(layer.positionY + 1))
        {
            moveLayerDown(layer);
            layer.positionY--;
        }
        layer.positionY += dy;
        return;
    }
    while (dy <= -1.0f)
    {
        moveLayerUp(layer);
        dy++;
    }
    if (dy < 0.0f)
    {
        if (std::floor(layer.positionY + dy) == std::floor(layer.positionY - 1))
        {
            moveLayerUp(layer);
            layer.positionY++;
        }
        layer.positionY += dy;
        return;
    }
}
