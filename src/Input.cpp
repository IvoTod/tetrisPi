#include <Input.h>
#include <iostream>
#include <wiringPi.h>

#define UP_BUTTON_PIN 13
#define LEFT_BUTTON_PIN 5
#define RIGHT_BUTTON_PIN 19
#define DOWN_BUTTON_PIN 6
#define ACCEPT_BUTTON_PIN 26

Input::Input() {
    setupButtons();
}

bool Input::isKeyPressed(Key key) {
    return pressedKeys[key];
}

bool Input::isKeyHeld(Key key) {
    return heldKeys[key];
}

bool Input::isKeyReleased(Key key) {
    return releasedKeys[key];
}
//TODO Handle input
void Input::update() {
    
}

void Input::newFrame() {
    pressedKeys.clear();
    releasedKeys.clear();
}

void Input::setupButtons() {
    pinMode(UP_BUTTON_PIN, INPUT);
    pinMode(LEFT_BUTTON_PIN, INPUT);
    pinMode(RIGHT_BUTTON_PIN, INPUT);
    pinMode(DOWN_BUTTON_PIN, INPUT);
    pinMode(ACCEPT_BUTTON_PIN, INPUT);
}
