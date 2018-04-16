#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>

class TFT_ST7735;
class GameObject;

class Scene {
    public:
	Scene();
	~Scene();

	void update(int ms);
	void draw(TFT_ST7735& tft);
	void addGameObject(GameObject* gameObject);
	
    private:
	std::vector<GameObject*> gameObjects;

};

#endif
