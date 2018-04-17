#include <ButtonManager.h>
#include <cstddef>

ButtonManager::ButtonManager(Button* firstButton) :
    GameObject(),
    currentButton(firstButton)
{
    currentButton->onSelect();
    input = input->getInstance();
}

void ButtonManager::update(int ms) {
    if(!currentButton) {
	return;
    }

    if(input->isKeyPressed(UP)) {
	buttonInput(UP);
    }
    if(input->isKeyPressed(DOWN)) {
	buttonInput(DOWN);
    }
    if(input->isKeyPressed(LEFT)) {
	buttonInput(LEFT);
    }
    if(input->isKeyPressed(RIGHT)) {
	buttonInput(RIGHT);
    }
    if(input->isKeyPressed(ACCEPT)) {
	currentButton->onPress();
    }
}

void ButtonManager::buttonInput(Key key) {
    Button* nextButton = NULL;
    switch(key) {
    case UP:
	nextButton = currentButton->getNextButtonUp();
	break;
    case DOWN:
	nextButton = currentButton->getNextButtonDown();
	break;
    case LEFT:
	nextButton = currentButton->getNextButtonLeft();
	break;
    case RIGHT:
	nextButton = currentButton->getNextButtonRight();
	break;
    default:
	break;
    }
    if(nextButton) {
	currentButton->onDeselect();
	currentButton = nextButton;
	currentButton->onSelect();
    }
}

void ButtonManager::draw(TFT_ST7735& tft) {return;}


