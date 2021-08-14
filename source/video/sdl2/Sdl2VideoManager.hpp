#ifndef SDL2VIDEOMANAGER_HPP
#define SDL2VIDEOMANAGER_HPP

#include <SDL2/SDL.h>

#include "../VideoManager.hpp"

/**
 * Graphics system powered by SDL2/OpenGL.
 */
class Sdl2VideoManager : public VideoManager
{
public:
    /**
     * Constructor.
     *
     * @param window the window to render to.
     * @param virtualScreenWidth the width of the virtual screen, in pixels.
     * @param virtualScreenHeight the height of the virtual screen, in pixels.
     */
    Sdl2VideoManager(SDL_Window* window, int virtualScreenWidth, int virtualScreenHeight);

    void clearScreen();
    void drawLine(int x0, int y0, int x1, int y1);
    void drawRectangle(int x, int y, int width, int height);
    void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2);
    int getScreenHeight() const;
    int getScreenWidth() const;
    void setColor(unsigned color);
    void updateScreen();

private:
    SDL_Window* window;
    int screenWidth;
    int screenHeight;
};

#endif // SDL2GRAPHICSMANAGER_HPP
