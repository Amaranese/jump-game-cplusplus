#include <cmath>

#include "Entity.hpp"
#include "Level.hpp"

Entity::Entity() :
    level(nullptr),
    width(Level::TILE_SIZE),
    height(Level::TILE_SIZE),
    positionX(0.0f),
    positionY(0.0f),
    velocityX(0.0f),
    velocityY(0.0f),
    accelerationX(0.0f),
    accelerationY(0.0f)
{
}

int Entity::getBottom() const
{
    return getY() + height - 1;
}

int Entity::getCenterX() const
{
    return getX() + width / 2;
}

int Entity::getCenterY() const
{
    return getY() + height / 2;
}

int Entity::getLeft() const
{
    return getX();
}

Level& Entity::getLevel()
{
    return *level;
}

const Level& Entity::getLevel() const
{
    return *level;
}

int Entity::getRight() const
{
    return getX() + width - 1;
}

int Entity::getTop() const
{
    return getY();
}

float Entity::getVelocityX() const
{
    return velocityX;
}

float Entity::getVelocityY() const
{
    return velocityY;
}

int Entity::getX() const
{
    return static_cast<int>(std::floor(positionX));
}

int Entity::getY() const
{
    return static_cast<int>(std::floor(positionY));
}

bool Entity::isOnGround() const
{
    return level->isEntityOnGround(*this);
}

bool Entity::isUnderwater() const
{
    return level->isUnderwaterAt(getCenterX(), getCenterY());
}

void Entity::setAccelerationX(float ax)
{
    accelerationX = ax;
}

void Entity::setAccelerationY(float ay)
{
    accelerationY = ay;
}

void Entity::setVelocityX(float vx)
{
    velocityX = vx;
}

void Entity::setVelocityY(float vy)
{
    velocityY = vy;
}

void Entity::setX(float x)
{
    positionX = x;
}

void Entity::setY(float y)
{
    positionY = y;
}
