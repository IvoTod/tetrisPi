#include <SceneManager.h>
#include <ButtonManager.h>
#include <iostream>
#include <ali_colors.h>
#include <Button.h>

void scoreboardPress() {
    std::cout << "Scoreboard button pressed!" << std::endl;
}

void playPress() {
    std::cout << "Play button pressed!" << std::endl;
    SceneManager* sceneManager;
    sceneManager = sceneManager->getInstance();
    sceneManager->loadInGameScene();
    clear = true;
}

SceneManager::SceneManager() {}

void SceneManager::loadMainMenuScene() {
    Button* playButton = new Button(29, 40, 66, 20, "PLAY", &playPress, ALI_WHITE, ALI_BLUE);
    Button* scoreboardButton = new Button(29, 70, 66, 20, "SCOREBOARD", &scoreboardPress, ALI_WHITE, ALI_BLUE);
    playButton->setNextButtonUp(scoreboardButton);
    playButton->setNextButtonDown(scoreboardButton);
    scoreboardButton->setNextButtonUp(playButton);
    scoreboardButton->setNextButtonDown(playButton);
    ButtonManager* buttonManager = new ButtonManager(playButton);

    currentScene = Scene();
    currentScene.addGameObject(playButton);
    currentScene.addGameObject(scoreboardButton);
    currentScene.addGameObject(buttonManager);
}

void SceneManager::loadInGameScene() {
    currentScene = Scene();
}

void SceneManager::loadScoreboardScene() {

}

void SceneManager::update(int ms) {
    currentScene.update(ms);
}

void SceneManager::draw(TFT_ST7735& tft) {
    if(clear) {
	clear = false;
	tft.setBackground(TFT_BLACK);
	tft.clearScreen();
    }
    currentScene.draw(tft);
}

Scene& SceneManager::getCurrentScene() {
    return currentScene;
}

SceneManager* SceneManager::instance;

