#ifndef COLOR_HPP
#define COLOR_HPP

#include "../includes.hpp"

enum ColorEffect
{
    RESET,
    BOLD,
    FAINT,
    UNDERLINE,
    BLINK,
    CLEAR
};

std::ostream &operator<<(std::ostream &out, const ColorEffect &colEff);

class Color
{
    char r, g, b;

public:
    Color(char r, char g, char b);

    friend std::ostream &operator<<(std::ostream &out, const Color &color);
};

class BgColor
{
    char r, g, b;

public:
    BgColor(char r, char g, char b);

    friend std::ostream &operator<<(std::ostream &out, const BgColor &color);
};

#endif