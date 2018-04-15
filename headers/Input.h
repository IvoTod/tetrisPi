#ifndef __INPUT_H__
#define __INPUT_H__

#include <map>
#include <Key.h>

class Input {
    public:
	Input();
	bool isKeyPressed(Key key);
	bool isKeyHeld(Key key);
	bool isKeyReleased(Key key);
	void update();
	void newFrame();
    private:
	void setupButtons();
	std::map<Key, bool> pressedKeys;
	std::map<Key, bool> heldKeys;
	std::map<Key, bool> releasedKeys;


};

#endif
