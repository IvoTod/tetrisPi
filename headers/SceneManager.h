#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include <Scene.h>

class SceneManager {
    public:
	SceneManager();

	static SceneManager& getInstance() {
	    static SceneManager instance;
	    return instance;

	}

	void loadMainMenuScene();
	void loadInGameScene();
	void loadScoreboardScene();

	Scene& getCurrentScene();

	SceneManager(SceneManager const&)   = delete;
	void operator=(SceneManager const&) = delete;

    private:
	
	Scene currentScene;
};

#endif
