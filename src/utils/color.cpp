#include "color.hpp"

Color::Color(char r, char g, char b) : r(r), g(g), b(b)
{
}

std::ostream &operator<<(std::ostream &out, const ColorEffect &colEff)
{
    if (colEff < ColorEffect::CLEAR)
        return out << "\x1b[" << (int)colEff << "m";
    return out << "\033[2J\033[1;1H";
}

std::ostream &operator<<(std::ostream &out, const Color &color)
{
    return out << "\x1b[38;2;" << (unsigned)color.r << ";" << (unsigned)color.g << ";" << (unsigned)color.b << "m";
}

BgColor::BgColor(char r, char g, char b) : r(r), g(g), b(b)
{
}

std::ostream &operator<<(std::ostream &out, const BgColor &color)
{
    return out << "\x1b[48;2;" << (unsigned)color.r << ";" << (unsigned)color.g << ";" << (unsigned)color.b << "m";
}