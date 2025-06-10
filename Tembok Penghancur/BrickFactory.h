#ifndef BRICK_FACTORY_H
#define BRICK_FACTORY_H

#include "header.h"
#include <vector>

class BrickFactory {
public:
    static Brick createBrick(int type, float x, float y) {
        Color color = WHITE;

        switch (type) {
        case B_LIGHTGRAY: color = LIGHTGRAY; break;
        case B_GRAY: color = GRAY; break;
        case B_YELLOW: color = YELLOW; break;
        case B_ORANGE: color = ORANGE; break;
        case B_PINK: color = PINK; break;
        case B_RED: color = RED; break;
        case B_MAROON: color = MAROON; break;
        case B_GREEN: color = GREEN; break;
        case B_LIME: color = LIME; break;
        case B_DARKGREEN: color = DARKGREEN; break;
        case B_SKYBLUE: color = SKYBLUE; break;
        case B_BLUE: color = BLUE; break;
        case B_DARKBLUE: color = DARKBLUE; break;
        case B_PURPLE: color = PURPLE; break;
        case B_VIOLET: color = VIOLET; break;
        case B_DARKPURPLE: color = DARKPURPLE; break;
        case B_BEIGE: color = BEIGE; break;
        case B_BROWN: color = BROWN; break;
        case B_DARKBROWN: color = DARKBROWN; break;
        case B_MAGENTA: color = MAGENTA; break;
        default: break;
        }

        return Brick(x, y, 46.0f, 22.0f, color);
    }
};


#endif
