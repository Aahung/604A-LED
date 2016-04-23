#ifndef SNAKE_GROUND
#define SNAKE_GROUND




#include <Arduino.h>
#include "snake.h"
#include "vector.h"
#include "display.h"
#include "control.h"
#include "sound.h"

#define FOOD_FLASH 5
#define SNAKE_FLASH 20
#define SNAKE_HEAD_FLASH 25

class Ground {

    public:

        Ground();

        void display();
        void scan();
        void check_result();
        void move();

        void init();

        void sound();

    private:

        Snake *snakes;
        unsigned char dots[32]; // |  7 -  0 | 23 - 16 |
                                // | 15 -  8 | 31 - 24 |
        Display displayer;

        Control control;
        int *button_pressed;

        Vector dimension;

        // food
        Vector food;
        void generate_food();

        // sound
        Sound sounder;
        int sound_timer;
        int sound_point;
        int sound_divide;
        void set_sound(int time, int divide);

        // game status
        int over;
        int winner; // left is 1, right is 0
        
};

#endif