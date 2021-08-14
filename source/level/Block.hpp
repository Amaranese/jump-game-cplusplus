#ifndef BLOCK_HPP
#define BLOCK_HPP

/**
 * A tiled object that makes up the terrain of a level.
 */
class Block
{
    friend class Layer;
    friend class Level;
public:
    /**
     * Collision mask templates for blocks.
     */
    enum class CollisionType
    {
        NONE,        /**< Block does not cause collisions. */
        PLATFORM,    /**< Block only causes collisions from the top row of pixels from above. */
        SLOPE_LEFT,  /**< Block is slope shaped, increasing in height to the left, and behaves like a platform. */
        SLOPE_RIGHT, /**< Block is slope shaped, increasing in height to the right, and behaves like a platform. */
        SOLID,       /**< Block causes collisions on all 4 sides. */
        WATER        /**< Block triggers water physics. */
    };

    Block(CollisionType collisionType);

    virtual ~Block() {}

    /**
     * Get the bottom y coordinate, in pixels.
     */
    int getBottom() const;

    /**
     * Get the height of the block, in pixels.
     */
    int getHeight() const;

    /**
     * Get the left x coordinate, in pixels.
     */
    int getLeft() const;

    /**
     * Get the right x coordinate, in pixels.
     */
    int getRight() const;

    /**
     * Get the top y coordinate, in pixels.
     */
    int getTop() const;

    /**
     * Get the width of the block, in pixels.
     */
    int getWidth() const;

    /**
     * Get the x position of the block, in pixels.
     */
    int getX() const;

    /**
     * Get the y position of the block, in pixels.
     */
    int getY() const;

    /**
     * Check if the block causes a collision from the bottom at a particular pixel.
     */
    bool hasBottomCollision(int x, int y) const;

    /**
     * Check if the block causes a collision from the left at a particular pixel.
     */
    bool hasLeftCollision(int x, int y) const;

    /**
     * Check if the block causes a collision from the right at a particular pixel.
     */
    bool hasRightCollision(int x, int y) const;

    /**
     * Check if the block causes a slope collision from above at a particular pixel.
     */
    bool hasSlopeCollision(int x, int y) const;

    /**
     * Check if the block causes a collision from the top at a particular pixel.
     */
    bool hasTopCollision(int x, int y) const;

    /**
     * Set the height of the block, in tiles.
     */
    void setHeight(int height);

    /**
     * Set the width of the block, in tiles.
     */
    void setWidth(int width);

private:
    CollisionType collisionType;
    int positionX; /**< Position within a layer, in tiles. */
    int positionY; /**< Position within a layer, in tiles. */
    int width;  /**< Width, in tiles. */
    int height; /**< Height, in tiles. */
};

#endif // BLOCK_HPP
