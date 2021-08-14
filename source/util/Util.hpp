/**
 * @file defines useful utility functions
 */
#ifndef UTIL_HPP
#define UTIL_HPP

/**
 * Takes a hex value in the format 0xABCD where
 *  - A is tiles
 *  - B is pixels
 *  - C is subpixels
 *  - D is subsubpixels
 * and converts it to a float usable by our game engine (where the units are pixels)
 */
constexpr float physicsValueFromHex(int value)
{
    return 16.0f * ((value & 0xf000) >> 12) +
           (float)((value & 0xf00) >> 8) +
           0.0625f * ((value & 0xf0) >> 4) +
           0.00390625f * (float)(value & 0xf);
}

/**
 * Determine the sign of a number.
 * @param val the number.
 * @return the sign of the number (zero is treated as positive).
 */
template <typename T>
constexpr int sgn(T val)
{
    return (T(0) <= val) - (val < T(0));
}

#endif // UTIL_HPP
