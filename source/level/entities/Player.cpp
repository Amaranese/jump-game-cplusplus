#include <cmath>

#include "../../input/InputManager.hpp"
#include "../Level.hpp"

#include "Player.hpp"

Player::Player() :
    directionSign(1),
    maxAirVelocityX(MAX_WALKING_SPEED),
    wasAtSurfaceOfWaterLastFrame(false)
{
}

bool Player::isAtSurfaceOfWater() const
{
    return !(getLevel().isUnderwaterAt(getCenterX(), getTop())) && isUnderwater();
}

void Player::onButtonPress(InputButton buttonId)
{
    if (buttonId == InputButton::A)
    {
        // Jump if we are on the ground or underwater
        if (isUnderwater())
        {
            float swimPower = getVelocityY() - SWIM_POWER_MODIFIER;
            if (swimPower < MIN_SWIM_POWER)
            {
                swimPower = MIN_SWIM_POWER;
            }
            else if (swimPower > MAX_SWIM_POWER)
            {
                swimPower = MAX_SWIM_POWER;
            }
            setVelocityY(swimPower);
        }
        else if (isOnGround())
        {
            float velocityX = std::fabs(getVelocityX());
            if (velocityX > JUMP_VELOCITY_THRESHOLD_3)
            {
                setVelocityY(-1 * JUMP_VELOCITY_3);
            }
            else if (velocityX > JUMP_VELOCITY_THRESHOLD_2)
            {
                setVelocityY(-1 * JUMP_VELOCITY_2);
            }
            else
            {
                setVelocityY(-1 * JUMP_VELOCITY_1);
            }
            setAccelerationY(JUMP_GRAVITY_1);
        }
    }
}

void Player::onUpdate()
{
    InputManager& input = InputManager::getInstance();

    // Determine which direction we are facing
    bool stopping = false;
    if (input.isButtonPressed(InputButton::LEFT))
    {
        directionSign = -1;
    }
    else if (input.isButtonPressed(InputButton::RIGHT))
    {
        directionSign = 1;
    }
    else
    {
        stopping = true;
    }

    bool atSurfaceOfWaterThisFrame = false;
    if (isUnderwater()) // Underwater physics
    {
        // Cap x velocity
        float maximumVelocityX;
        if (isOnGround()) // Walking underwater
        {
            maximumVelocityX = MAX_UNDERWATER_WALKING_SPEED;
        }
        else // Swimming
        {
            maximumVelocityX = MAX_SWIMMING_SPEED;
        }
        if (std::fabs(getVelocityX()) > maximumVelocityX)
        {
            setVelocityX(maximumVelocityX * sgn(getVelocityX()));
        }

        // Determine x acceleration
        if (stopping)
        {
            if (std::fabs(getVelocityX()) > UNDERWATER_DECELERATION)
            {
                setAccelerationX(-1 * sgn(getVelocityX()) * UNDERWATER_DECELERATION);
            }
            else
            {
                setAccelerationX(0);
                setVelocityX(0);
            }
        }
        else if (directionSign != sgn(getVelocityX()))
        {
            setAccelerationX(directionSign * UNDERWATER_TURN_ACCELERATION);
        }
        else
        {
            setAccelerationX(directionSign * UNDERWATER_ACCELERATION);
        }

        if (isAtSurfaceOfWater())
        {
            atSurfaceOfWaterThisFrame = true;
            if (!wasAtSurfaceOfWaterLastFrame)
            {
                // If we are holding up, jump out of the water
                if (input.isButtonPressed(InputButton::UP) && input.isButtonPressed(InputButton::A))
                {
                    setVelocityY(-1 * UNDERWATER_JUMP_VELOCITY);
                }
                else
                {
                    // Stop when we first hit the surface of the water
                    setVelocityY(0);
                }
            }
        }

        // Cap y velocity
        if (getVelocityY() > MAX_UNDERWATER_DOWNWARD_VELOCITY)
        {
            setVelocityY(MAX_UNDERWATER_DOWNWARD_VELOCITY);
        }

        // Determine gravity (y acceleration)
        if (atSurfaceOfWaterThisFrame)
        {
            setAccelerationY(UNDERWATER_GRAVITY_AT_SURFACE);
        }
        else if (getVelocityY() < 0)
        {
            setAccelerationY(UNDERWATER_GRAVITY_MOVING_UPWARD);
        }
        else
        {
            setAccelerationY(UNDERWATER_GRAVITY_MOVING_DOWNWARD);
        }
    }
    else // Regular physics
    {
        if (isOnGround())
        {
            // Cap x velocity
            float maximumVelocityX = MAX_WALKING_SPEED;
            if (input.isButtonPressed(InputButton::B))
            {
                maximumVelocityX = MAX_RUNNING_SPEED;
            }
            if (std::fabs(getVelocityX()) > maximumVelocityX)
            {
                setVelocityX(maximumVelocityX * sgn(getVelocityX()));
            }

            // Store our momentum as the max velocity when we become airborne again
            maxAirVelocityX = maximumVelocityX;
        }
        else // In the air physics
        {
            // Cap x velocity
            if (std::fabs(getVelocityX() > maxAirVelocityX))
            {
                setVelocityX(maxAirVelocityX * sgn(getVelocityX()));
            }
        }

        // Determine x acceleration
        if (stopping)
        {
            if (std::fabs(getVelocityX()) > STOP_DECELERATION)
            {
                setAccelerationX(-1 * sgn(getVelocityX()) * STOP_DECELERATION);
            }
            else
            {
                setAccelerationX(0);
                setVelocityX(0);
            }
        }
        else if (directionSign != sgn(getVelocityX()))
        {
            setAccelerationX(directionSign * SKID_DECELERATION);
        }
        else
        {
            setAccelerationX(directionSign * RUN_ACCELERATION);
        }

        // Cap y velocity
        if (getVelocityY() > MAX_DOWNWARD_VELOCITY)
        {
            setVelocityY(MAX_DOWNWARD_VELOCITY);
        }

        // Determine gravity (y acceleration)
        if (input.isButtonPressed(InputButton::A) && getVelocityY() < JUMP_GRAVITY_THRESHOLD_2)
        {
            setAccelerationY(JUMP_GRAVITY_1);
        }
        else
        {
            setAccelerationY(JUMP_GRAVITY_2);
        }
    }

    // Store whether we were at the surface of a body of water this frame
    wasAtSurfaceOfWaterLastFrame = atSurfaceOfWaterThisFrame;
}
