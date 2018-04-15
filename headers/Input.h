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
	void update(int ms);
	void newFrame();
    private:
	const int bounceTime = 200; //High value because chinese buttons
	void setupButtons();
	void setupTimers();
	void handleButtonPress(Key key, int pin);
	void updateTimers(int ms);
	void updateTimer(Key key, int ms);
	std::map<Key, bool> pressedKeys;
	std::map<Key, bool> heldKeys;
	std::map<Key, bool> releasedKeys;
	std::map<Key, int> bounceTimers;


};

#endif
