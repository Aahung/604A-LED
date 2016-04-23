#ifndef SNAKE_POINT
#define SNAKE_POINT




#include <Arduino.h>

typedef struct Vector
{
public:

    int x, y;

    Vector() {
        x = 0;
        y = 0;
    }

    Vector(int _x, int _y) {
        x = _x;
        y = _y;
    }

    
} Vector;

#endif