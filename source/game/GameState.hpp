#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

class GameStateManager;
class VideoManager;

/**
 * Represents a state of execution in the Game.
 */
class GameState
{
    friend class GameStateManager;
public:
    /**
     * Constructor.
     */
    GameState();

    virtual ~GameState() {}

protected:
    /**
     * Change the current game state to a different state.
     */
    void changeState(GameState* state);

    /**
     * Event called whenever the state is requested to render to the screen.
     */
    virtual void onRender(VideoManager& video) const =0;

    /**
     * Event called once per frame to have the state update itself.
     */
    virtual void onUpdate()=0;

    /**
     * Pop the current state off the state stack.
     */
    void popState();

    /**
     * Push a new state onto the top of the state stack and start executing.
     */
    void pushState(GameState* state);

private:
    GameStateManager* gameStateManager;
};

#endif // GAMESTATE_HPP
