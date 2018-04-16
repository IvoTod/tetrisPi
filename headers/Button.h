#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <cstddef>
#include <GameObject.h>
#include <string>
#define OFFSET_TEXT 3
class TFT_ST7735;

class Button : public  GameObject {
    public:
	typedef  void(*eventFunction)();

	Button(int x, int y, int w, int h, std::string bText, eventFunction functionPointer, unsigned int foreground, unsigned int background);

	virtual void update(int ms);
	virtual void draw(TFT_ST7735& tft);

	void setSize(int newWidth, int newHeight);

	void onPress();
	
	void onSelect();
	
	void onDeselect();

	Button* getNextButtonUp();
	Button* getNextButtonDown();
	Button* getNextButtonLeft();
	Button* getNextButtonRight();

	void setNextButtonUp(Button* newButton);
	void setNextButtonDown(Button* newButton);
	void setNextButtonLeft(Button* newButton);
	void setNextButtonRight(Button* newButton);

    protected:
	bool canDraw;
	eventFunction pressFunctionPointer;
	
	Button* nextButtonUp = NULL;
	Button* nextButtonDown = NULL;
	Button* nextButtonLeft = NULL;
	Button* nextButtonRight = NULL;

	Vector2D size;
	std::string text;
	bool selected;

	unsigned int fgColor;
	unsigned int bgColor;
	unsigned int selectedBorderColor;

};

#endif
