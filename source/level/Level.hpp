#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <list>

class Entity;
class Layer;
class VideoManager;

/**
 * Handles interactions between all Layers, Blocks, and Entities.
 */
class Level
{
public:
    /**
     * The size of a tile unit, in pixels.
     */
    static constexpr int TILE_SIZE = 16;

    Level();
    ~Level();

    /**
     * Add an entity to the level.
     */
    void addEntity(Entity* entity);

    /**
     * Add a layer to the level.
     */
    void addLayer(Layer* layer);

    /**
     * Check if an entity is standing on the ground of the level (i.e. not in the air).
     */
    bool isEntityOnGround(const Entity& entity) const;

    /**
     * Check if a position in the level is underwater.
     */
    bool isUnderwaterAt(int x, int y) const;

    /**
     * Render the level.
     *
     * @param video the VideoManager to use for drawing.
     * @param left the left coordinate for the camera rectangle, in pixels.
     * @param right the right coordinate for the camera rectangle, in pixels.
     * @param top the top coordinate for the camera rectangle, in pixels.
     * @param bottom the bottom coordinate for the camera rectangle, in pixels.
     */
    void render(VideoManager& video, int left, int right, int top, int bottom) const;

    /**
     * Update the level by one frame.
     */
    void update();

private:
    std::list<Entity*> entities;
    std::list<Layer*> layers;

    bool canEntityMoveDown(Entity& entity) const;
    bool canEntityMoveLeft(Entity& entity) const;
    bool canEntityMoveRight(Entity& entity) const;
    bool canEntityMoveUp(Entity& entity) const;
    bool isEntityStandingOnLayer(const Layer& layer, const Entity& entity) const;
    bool moveEntityDown(Entity& entity);
    bool moveEntityLeft(Entity& entity);
    bool moveEntityRight(Entity& entity);
    bool moveEntityUp(Entity& entity);
    void moveEntityX(Entity& entity, float dx);
    void moveEntityY(Entity& entity, float dy);
    void moveLayerDown(Layer& layer);
    void moveLayerLeft(Layer& layer);
    void moveLayerRight(Layer& layer);
    void moveLayerUp(Layer& layer);
    void updateEntity(Entity& entity);
    void updateEntityMotionX(Entity& entity);
    void updateEntityMotionY(Entity& entity);
    void updateLayer(Layer& layer);
    void updateLayerMotionX(Layer& layer);
    void updateLayerMotionY(Layer& layer);
};

#endif // LEVEL_HPP
