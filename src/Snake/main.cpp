#include <Arduino.h>
#include <Wire.h>
#include "ground.h"

#define LOOP_SIZE 1000;

Ground *ground;
int count;

void setup() {
    ground = new Ground();
    count = 0;
}

void loop() {
    ground->display();
    ground->scan();
    ground->move();
    ground->sound();

    if (++count == 1000) count = 0;
}