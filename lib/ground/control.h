#ifndef SNAKE_CONTROL
#define SNAKE_CONTROL

#include <Arduino.h>

//IO

class Control {
public:

    int n;
    int *BUTTON_PINS; 
    int *lock;

    Control() {
        n = 4;
        BUTTON_PINS = new int[n] {8, 9, 10, 11};
        lock = new int[n] {0};

        for (int i = 0; i < n; ++i)
            pinMode(BUTTON_PINS[i], INPUT);
    }

    void scan_buttons(int *pressed) {
        for (int i = 0; i < n; ++i)
            if (digitalRead(BUTTON_PINS[i]) == 0) {
                if (!lock[i]) {
                    pressed[i] = 1;
                    lock[i] = 1;
                } else pressed[i] = 0;
            } else {
                pressed[i] = 0;
                lock[i] = 0;
            }
    }
};

#endif