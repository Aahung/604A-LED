#ifndef SNAKE_SNAKE
#define SNAKE_SNAKE



#include <Arduino.h>
#include "vector.h"

#define MAX_BODY_LENGTH 50

class Snake {

    public:

        // constructor, _body[0] is head
        Snake(Vector *_body, int _body_length, Vector *_direction, int _speed);

        // variables
        Vector body[MAX_BODY_LENGTH]; // 0 -> head, back -> tail
        int body_length;
        int speed;
        int flash; // flashing

        void turn_left();
        void turn_right();
        void move(Vector *_dimension);

        // return index of _body of collision of colliding, 
        // return -1 not collide
        int collide(Vector *_body, int _body_length);

    private:

        Vector direction;
        Vector last_direction;

        
};

#endif