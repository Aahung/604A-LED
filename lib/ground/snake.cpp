#include "snake.h"

Snake::Snake(Vector *_body, int _body_length, Vector *_direction, int _speed) {
    body_length = _body_length;
    // initialize body
    for (int i = 0; i < body_length; ++i) {
        body[i].x = _body[i].x;
        body[i].y = _body[i].y;
    }

    direction = *_direction;
    last_direction = *_direction;

    speed = _speed;

    // flash is false
    flash = 0;
}

void Snake::turn_left() {
    if (last_direction.y == 0) {
        direction.x = 0;
        direction.y = -last_direction.x;
    } else {
        direction.x = last_direction.y;
        direction.y = 0;
    }
}

void Snake::turn_right() {
    if (last_direction.y == 0) {
        direction.x = 0;
        direction.y = last_direction.x;
    } else {
        direction.x = -last_direction.y;
        direction.y = 0;
    }
}

void Snake::move(Vector *dimension) {
    last_direction = direction;
    Vector head = body[0];
    head.x += direction.x;
    head.y += direction.y;
    if (head.x < 0) head.x += dimension->x;
    if (head.y < 0) head.y += dimension->y;
    if (head.x >= dimension->x) head.x -= dimension->x;
    if (head.y >= dimension->y) head.y -= dimension->y;
    for (int i = body_length; i > 0; --i) {
        body[i] = body[i - 1];
    }
    body[0] = head;
}

int Snake::collide(Vector *_body, int _body_length) {
    for (int i = 0; i < _body_length; ++i) {
        if (body[0].x == _body[i].x && body[0].y == _body[i].y) {
            return i;
        }
    }

    return -1;
}