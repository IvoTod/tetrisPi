#include <Scene.h>
#include <GameObject.h>

Scene::Scene() {}

void Scene::update(int ms) {
    for(int i = 0; i < gameObjects.size(); i++) {
	gameObjects[i]->update(ms);
    }
}

void Scene::draw(TFT_ST7735& tft) {
    for(int i = 0; i < gameObjects.size(); i++) {
	gameObjects[i]->draw(tft);
    }
}

void Scene::addGameObject(GameObject* gameObject) {
    gameObjects.push_back(gameObject);
}
