#ifndef VIDEOMANAGER_HPP
#define VIDEOMANAGER_HPP

/**
 * Interface for graphical routines.
 */
class VideoManager
{
public:
    virtual ~VideoManager() {}

    /**
     * Clear the screen.
     */
    virtual void clearScreen()=0;

    /**
     * Draw a line.
     */
    virtual void drawLine(int x0, int y0, int x1, int y1)=0;

    /**
     * Draw a rectangle.
     *
     * @param x the left coordinate.
     * @param y the top coordinate.
     * @param width the width of the rectangle.
     * @param height the height of the rectangle.
     */
    virtual void drawRectangle(int x, int y, int width, int height)=0;

    /**
     * Draw a triangle.
     */
    virtual void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2)=0;

    /**
     * Get the height of the screen in pixels.
     */
    virtual int getScreenHeight() const =0;

    /**
     * Get the width of the screen in pixels.
     */
    virtual int getScreenWidth() const =0;

    /**
     * Set the color used for drawing primitives.
     *
     * @param color the color, as a 32-bit ARGB value. If the A component
     * is zero, then it will be treated as 255 unless all other components
     * are zero as well.
     */
    virtual void setColor(unsigned color)=0;

    /**
     * Render any changes to the screen.
     */
    virtual void updateScreen()=0;
};

#endif // VIDEOMANAGER_HPP
