#include <SDL2/SDL_opengl.h>

#include "Sdl2VideoManager.hpp"

Sdl2VideoManager::Sdl2VideoManager(SDL_Window* window, int virtualScreenWidth, int virtualScreenHeight) :
    window(window),
    screenWidth(virtualScreenWidth),
    screenHeight(virtualScreenHeight)
{
}

void Sdl2VideoManager::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenWidth, screenHeight, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Sdl2VideoManager::drawLine(int x0, int y0, int x1, int y1)
{
    glBegin(GL_LINES);
        glVertex2i(x0, y0);
        glVertex2i(x1, y1);
    glEnd();
}

void Sdl2VideoManager::drawRectangle(int x, int y, int width, int height)
{
    glBegin(GL_LINE_LOOP);
        glVertex2i(x, y);
        glVertex2i(x + width, y);
        glVertex2i(x + width, y + height);
        glVertex2i(x, y + height);
    glEnd();
}

void Sdl2VideoManager::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINE_LOOP);
        glVertex2i(x0, y0);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
    glEnd();
}

int Sdl2VideoManager::getScreenHeight() const
{
    return screenHeight;
}

int Sdl2VideoManager::getScreenWidth() const
{
    return screenWidth;
}

void Sdl2VideoManager::setColor(unsigned color)
{
    Uint8 r = (color >> 16) & 0xff;
    Uint8 g = (color >> 8) & 0xff;
    Uint8 b = color & 0xff;
    Uint8 a = (color >> 24) & 0xff;
    if (a == 0 && (r != 0 || g != 0 || b != 0))
    {
        a = 0xff;
    }
    glColor4ub(r, g, b, a);
}

void Sdl2VideoManager::updateScreen()
{
    SDL_GL_SwapWindow(window);
}
