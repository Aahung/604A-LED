#include "ground.h"
#include <time.h>

void light_dot(unsigned char *dots, int x, int y) {
    if (x >= 8) {
        x -= 8;
        y += 16;
    }
    dots[y] &= ~(1 << (7 - x));
}

extern int count;

Ground::Ground() {
    dimension.x = 16;
    dimension.y = 16;

    // first snake
    Vector body1[] = {
        Vector(3, 3),
        Vector(2, 3),
        Vector(1, 3),
        Vector(0, 3)
    };
    Vector direction1(1, 0);

    // second snake
    Vector body2[] = {
        Vector(12, 11),
        Vector(13, 11),
        Vector(14, 11),
        Vector(15, 11)
    };
    
    Vector direction2(-1, 0);


    snakes = new Snake[2] {
        Snake(body1, 4, &direction1, 20),
        Snake(body2, 4, &direction2, 20)
    };

    button_pressed = new int[control.n] {0};

    randomSeed(analogRead(0));
    generate_food();

    // init sound timer to 50
    set_sound(50, 3);

    over = 0;
}

void Ground::init() {
    // first snake
    Vector body1[] = {
        Vector(3, 3),
        Vector(2, 3),
        Vector(1, 3),
        Vector(0, 3)
    };
    Vector direction1(1, 0);

    // second snake
    Vector body2[] = {
        Vector(12, 11),
        Vector(13, 11),
        Vector(14, 11),
        Vector(15, 11)
    };
    
    Vector direction2(-1, 0);
}

void Ground::display() {
    // render snakes into dots

    // reset 
    for (int i = 0; i < 32; ++i) {
        dots[i] = 0xff;
    }

    if (over) {
        // display cross
        for (int i = 0; i < 8; ++i) {
            light_dot(dots, i, i + winner * 16);
            light_dot(dots, 7 - i, i + winner * 16);
            light_dot(dots, i, i + winner * 16 + 8);
            light_dot(dots, 7 - i, i + winner * 16 + 8);
        }
    }

    for (int s = 0; s < 2; ++s) {
        if (snakes[s].flash == 0 || count % (2 * SNAKE_FLASH) < SNAKE_FLASH)
            for (int i = 0; i < snakes[s].body_length; ++i) { 
                int x = snakes[s].body[i].x;
                int y = snakes[s].body[i].y;
                light_dot(dots, x, y);
            }
        else
            snakes[s].flash--;
    }

    if (count % (2 * FOOD_FLASH) < FOOD_FLASH)
        light_dot(dots, food.x, food.y);

    displayer.print(dots);
}

void Ground::move() {
    if (over) return;

    int any_move = 0;
    for (int s = 0; s < 2; ++s) {
        if (count % snakes[s].speed == 0) {
            snakes[s].move(&dimension);
            any_move = 1;
        }
    }

    if (any_move) {
        check_result();
    }
}

void Ground::check_result() {
    // check if eat food
    for (int s = 0; s < 2; ++s) {
        if (snakes[s].body[0].x == food.x && snakes[s].body[0].y == food.y) {
            snakes[s].body_length++;
            generate_food();
            set_sound(10, 1);
        }
    }

    // check if meet any body
    int die[2] = {0};
    for (int s = 0; s < 2; ++s) {
        for (int p = 0; p < 2; ++p) {
            for (int i = 1; i < snakes[p].body_length; ++i) {
                if (snakes[s].body[0].x == snakes[p].body[i].x
                    && snakes[s].body[0].y == snakes[p].body[i].y) {
                    // snake s dies
                    die[s] = 1;
                }
            }
        }
    }

    if (die[0]) {
        snakes[0].body_length = max(4, snakes[0].body_length / 2);
        snakes[0].flash = 50;
        set_sound(20, 2);
    }

    if (die[1]) {
        snakes[1].body_length = max(4, snakes[1].body_length / 2);
        snakes[1].flash = 50;
        set_sound(20, 2);
    }

    if (snakes[0].body_length > 9) {
        over = 1;
        winner = 1;
        set_sound(1000, 10);
    }

    if (snakes[1].body_length > 9) {
        over = 1;
        winner = 0;
        set_sound(1000, 10);
    }
}

void Ground::scan() {
    control.scan_buttons(button_pressed);

    if (button_pressed[0] == 1) {
        // snake 0, turn left
        snakes[0].turn_left();
    }

    if (button_pressed[1] == 1) {
        // snake 0, turn right
        snakes[0].turn_right();
    }

    if (button_pressed[2] == 1) {
        // snake 1, turn left
        snakes[1].turn_left();
    }
    
    if (button_pressed[3] == 1) {
        // snake 1, turn right
        snakes[1].turn_right();
    }
}

void Ground::generate_food() {
    while (true) {
        int x = random(0, dimension.x);
        int y = random(0, dimension.y);
        int is_body = 0;
        for (int s = 0; s < 2; ++s) {
            for (int i = 0; i < snakes[s].body_length; ++i) {
                if (x == snakes[s].body[i].x && y == snakes[s].body[i].y) {
                    is_body = 1;
                }
                if (is_body) break;
            }
            if (is_body) break;
        }
        if (!is_body) {
            food.x = x;
            food.y = y;
            break;
        }
    }
}

void Ground::sound() {
    if (sound_point > 0) {
        if (sound_point * (2 * sound_divide - 1) / sound_timer % 2 == 0) {
            sounder.play();
        }
        sound_point--;
    }
}

void Ground::set_sound(int time, int divide) {
    sound_timer = sound_point = time;
    sound_divide = divide;
}