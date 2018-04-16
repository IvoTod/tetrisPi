#include <iostream>
#include <Vector2D.h>
#include <Button.h>
#include <tft_st7735.h>


Button::Button(int x, int y, int w, int h, std::string bText, eventFunction functionPointer, unsigned int foreground, unsigned int background) :
    GameObject(x, y),
    size(Vector2D(w, h)),
    text(bText),
    pressFunctionPointer(functionPointer),
    fgColor(foreground),
    bgColor(background),
    selected(false),
    canDraw(true)
{}

void Button::update(int ms) {}

void Button::draw(TFT_ST7735& tft) {
    if(!canDraw) {
	return;
    }
    unsigned char yTextStart;
    tft.fillRect(pos.x, pos.y, size.x, size.y, bgColor);

    tft.drawRect(pos.x, pos.y, size.x, size.y, fgColor);

    tft.setBackground(bgColor);
    yTextStart = pos.y + (size.y-(FONT_HEIGHT*1)) / 2;
    tft.drawString(pos.x+OFFSET_TEXT, yTextStart, text.c_str(), fgColor, 1);
    canDraw = false;
}

void Button::setSize(int newWidth, int newHeight) {
    size = Vector2D(newWidth, newHeight);
}

void Button::onPress() {
    (pressFunctionPointer)();
}

void Button::onSelect() {
    std::cout << "Selected button " << text << std::endl;
    selected=true;
    canDraw=true;
}

void Button::onDeselect() {
    selected=false;
    canDraw=true;
}

Button* Button::getNextButtonUp() {
    return nextButtonUp;
}

Button* Button::getNextButtonDown() {
    return nextButtonDown;
}

Button* Button::getNextButtonLeft() {
    return nextButtonLeft;
}

Button* Button::getNextButtonRight() {
    return nextButtonRight;
}

void Button::setNextButtonUp(Button* newButton) {
    nextButtonUp = newButton;
}
void Button::setNextButtonDown(Button* newButton) {
    nextButtonDown = newButton;
}
void Button::setNextButtonLeft(Button* newButton) {
    nextButtonLeft = newButton;
}
void Button::setNextButtonRight(Button* newButton) {
    nextButtonRight = newButton;
}
