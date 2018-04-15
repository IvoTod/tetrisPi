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
    setupTimers();
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

void Input::update(int ms) {
    handleButtonPress(LEFT, LEFT_BUTTON_PIN);
    handleButtonPress(RIGHT, RIGHT_BUTTON_PIN);
    handleButtonPress(DOWN, DOWN_BUTTON_PIN);
    handleButtonPress(UP, UP_BUTTON_PIN);
    handleButtonPress(ACCEPT, ACCEPT_BUTTON_PIN);
    updateTimers(ms);
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

void Input::setupTimers() {
    bounceTimers[LEFT] = 0;
    bounceTimers[RIGHT] = 0;
    bounceTimers[UP] = 0;
    bounceTimers[DOWN] = 0;
    bounceTimers[ACCEPT] = 0;
}

void Input::handleButtonPress(Key key, int pin) {
    int currentVal = digitalRead(pin);
    if(bounceTimers[key] <= 0) {
	if(currentVal && !isKeyHeld(key)) {
	    std::cout << "Button pressed" << std::endl;
	    heldKeys[key] = true;
	    pressedKeys[key] = true;
	    bounceTimers[key] = bounceTime;
	}
	if(!currentVal && isKeyHeld(key)) {
	    heldKeys[key] = false;
	    releasedKeys[key] = true;
	    std::cout << "Button released" << std::endl;
	}

    }
}

void Input::updateTimers(int ms) {
      updateTimer(LEFT, ms); 
      updateTimer(RIGHT, ms); 
      updateTimer(UP, ms); 
      updateTimer(DOWN, ms); 
      updateTimer(ACCEPT, ms); 
}

void Input::updateTimer(Key key, int ms) {
    if(bounceTimers[key] <= 0) {
	return;
    }
    bounceTimers[key] -= ms;
}
