#ifndef SNAKE_SOUND
#define SNAKE_SOUND

#include <Arduino.h>

//IO
#define SOUND_PORT 12


class Sound {
public:

    int s_count;

    Sound() {
        pinMode(SOUND_PORT, OUTPUT);
        s_count = 0;
    }

    void play() {
        if (s_count % 2 == 0) {
            digitalWrite(SOUND_PORT, HIGH); 
        } else {
            digitalWrite(SOUND_PORT, LOW); 
        }
        s_count++;
    }
};

#endif