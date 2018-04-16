#ifndef __BUTTON_MANAGER_H__
#define __BUTTON_MANAGER_H__

#include <Button.h>
#include <Input.h>
class TFT_ST7735;

class ButtonManager : public GameObject {
    public:
	ButtonManager(Button* firstButton);

	virtual void update(int ms);
	virtual void draw(TFT_ST7735& tft);

    private:
	void buttonInput(Key key);
	Input* input;
	Button* currentButton;

};

#endif
