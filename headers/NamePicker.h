#ifndef __NAME_PICKER_H__
#define __NAME_PICKER_H__

#include <GameObject.h>
#include <Input.h>
#include <string>
class TFT_ST7735;

class NamePicker : public GameObject {
    public:
	NamePicker(int score);
	virtual void update(int ms);
	virtual void draw(TFT_ST7735& tft);
    private:
	void saveScore();
	void scrollLetterUp();
	void scrollLetterDown();
	void nextLetter();
	void previousLetter();
	std::string getCurrentName();

	int scoreToSave;

	Input* input;
	int letters[3];
	int selectedLetter;
	bool canDraw = true;
    
};

#endif
