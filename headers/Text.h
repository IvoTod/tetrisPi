#ifndef __TEXT_H__
#define __TEXT_H__

#include <GameObject.h>
#include <tft_st7735.h>
#include <string>

class Text : public GameObject {
    public:
	Text(int x, int y, std::string txt, unsigned int fgColor) :
	    GameObject(x, y),
	    text(txt),
	    fg(fgColor)
	{}

	virtual void update(int ms) {}

	virtual void draw(TFT_ST7735& tft) {
	    if(!canDraw) {
		return;
	    }
	    tft.drawString(pos.x, pos.y, text.c_str(), fg, 1);
	    canDraw=false;
	}

	void setDraw() {
	    canDraw = true;
	}

    private:
	std::string text;

	unsigned int fg;

	bool canDraw = true;
    
};

#endif
