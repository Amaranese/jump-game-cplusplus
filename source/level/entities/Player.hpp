#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Entity.hpp"
#include "../../input/InputListener.hpp"
#include "../../util/Util.hpp"

/**
 * A user-controlled player.
 */
class Player : public Entity, public InputListener
{
public:
    Player();

private:
    // Physics constants:

    static constexpr float MAX_WALKING_SPEED = physicsValueFromHex(0x0180);
    static constexpr float MAX_RUNNING_SPEED = physicsValueFromHex(0x0280);

    static constexpr float RUN_ACCELERATION = physicsValueFromHex(0x000e);
    static constexpr float STOP_DECELERATION = physicsValueFromHex(0x000e);
    static constexpr float SKID_DECELERATION = physicsValueFromHex(0x0020);

    static constexpr float JUMP_VELOCITY_1 = physicsValueFromHex(0x0370);
    static constexpr float JUMP_VELOCITY_2 = physicsValueFromHex(0x0390);
    static constexpr float JUMP_VELOCITY_3 = physicsValueFromHex(0x03b0);

    static constexpr float JUMP_VELOCITY_THRESHOLD_2 = physicsValueFromHex(0x0100);
    static constexpr float JUMP_VELOCITY_THRESHOLD_3 = physicsValueFromHex(0x0200);

    static constexpr float JUMP_GRAVITY_1 = physicsValueFromHex(0x0010);
    static constexpr float JUMP_GRAVITY_2 = physicsValueFromHex(0x0050);

    static constexpr float JUMP_GRAVITY_THRESHOLD_2 = -1 * physicsValueFromHex(0x0200);

    static constexpr float MAX_DOWNWARD_VELOCITY = physicsValueFromHex(0x0450);

    static constexpr float MAX_UNDERWATER_WALKING_SPEED = physicsValueFromHex(0x0100);

    static constexpr float UNDERWATER_GRAVITY_MOVING_UPWARD = physicsValueFromHex(0x0010);
    static constexpr float UNDERWATER_GRAVITY_MOVING_DOWNWARD = physicsValueFromHex(0x0008);
    static constexpr float UNDERWATER_GRAVITY_AT_SURFACE = physicsValueFromHex(0x000c);

    static constexpr float MAX_UNDERWATER_DOWNWARD_VELOCITY = physicsValueFromHex(0x0200);

    static constexpr float MAX_SWIMMING_SPEED = physicsValueFromHex(0x0300);

    static constexpr float UNDERWATER_ACCELERATION = physicsValueFromHex(0x0006);
    static constexpr float UNDERWATER_DECELERATION = physicsValueFromHex(0x0002);
    static constexpr float UNDERWATER_TURN_ACCELERATION = physicsValueFromHex(0x0008);

    static constexpr float UNDERWATER_JUMP_VELOCITY = physicsValueFromHex(0x0330);

    static constexpr float SWIM_POWER_MODIFIER = physicsValueFromHex(0x01f0);
    static constexpr float MAX_SWIM_POWER = physicsValueFromHex(0x0000);
    static constexpr float MIN_SWIM_POWER = -1 * physicsValueFromHex(0x0200);

    int directionSign; /**< Sign that indicates the direction the player is facing. -1 for left, 1 for right. */
    float maxAirVelocityX; /**< Maximum velocity during airborne movement. */
    bool wasAtSurfaceOfWaterLastFrame; /**< Whether the player was at the surface of a body of water last frame. */

    bool isAtSurfaceOfWater() const;
    void onButtonPress(InputButton buttonId);
    void onUpdate();
};

#endif // PLAYER_HPP
