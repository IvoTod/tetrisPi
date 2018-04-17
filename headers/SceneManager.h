#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include <Scene.h>
#include <Input.h>

class TFT_ST7735;
class Input;

class SceneManager {
    public:
	SceneManager();

	static SceneManager* instance;
	static SceneManager* getInstance() {
	    if(!instance) {
		instance = new SceneManager();
	    }
	    return instance;
	}

	void loadMainMenuScene();
	void loadInGameScene();
	void loadScoreboardScene();
	void loadRecordScoreScene(int finalScore);

	void clearScreen(TFT_ST7735& tft);

	void setClear();

	Scene& getCurrentScene();

	SceneManager(SceneManager const&)   = delete;
	void operator=(SceneManager const&) = delete;
    private:
	Scene currentScene;
	bool clear = false;
};

#endif
