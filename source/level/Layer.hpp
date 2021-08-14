#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>

class Block;

/**
 * A grid of Blocks in a Level.
 */
class Layer
{
    friend class Level;
public:
    /**
     * Create a new layer.
     *
     * @param width the width of the layer, int tiles.
     * @param height the height of the layer, in tiles.
     */
    Layer(int width, int height);

    ~Layer();

    /**
     * Add a block to the layer.
     *
     * @param x the left position of the block, in tiles.
     * @param y the top position of the block, in tiles.
     * @param block the Block to add.
     */
    void addBlock(int x, int y, Block* block);

    /**
     * Get a block located at a tile position.
     */
    Block* getBlock(int x, int y);
    const Block* getBlock(int x, int y) const;

    /**
     * Get a block located at a pixel position, taking into account the layer's position.
     */
    Block* getBlockAt(int x, int y);
    const Block* getBlockAt(int x, int y) const;

    /**
     * Get the x position of the layer, in pixels.
     */
    int getX() const;

    /**
     * Get the y position of the layer, in pixels.
     */
    int getY() const;

    /**
     * Check if the layer causes a collision from the bottom at a particular pixel.
     */
    bool hasBottomCollision(int x, int y) const;

    /**
     * Check if the layer causes a collision from the left at a particular pixel.
     */
    bool hasLeftCollision(int x, int y) const;

    /**
     * Check if the layer causes a collision from the right at a particular pixel.
     */
    bool hasRightCollision(int x, int y) const;

    /**
     * Check if the layer has a top collision from a slope tile.
     */
    bool hasSlopeCollision(int x, int y) const;

    /**
     * Check if the layer causes a collision from the top at a particular pixel.
     */
    bool hasTopCollision(int x, int y) const;

    /**
     * Set the x velocity of the layer.
     */
    void setVelocityX(float vx);

    /**
     * Set the y velocity of the layer.
     */
    void setVelocityY(float vy);

    /**
     * Set the x position of the layer.
     */
    void setX(float x);

    /**
     * set the y position of the layer.
     */
    void setY(float y);

private:
    int width;  /**< Width, in tiles. */
    int height; /**< Height, in tiles. */
    float positionX; /**< X position, in pixels. */
    float positionY; /**< Y position, in pixels. */
    float velocityX; /**< X velocity, in pixels/frame. */
    float velocityY; /**< Y velocity, in pixels/frame. */
    std::vector<Block*> blocks;
};

#endif // LAYER_HPP
