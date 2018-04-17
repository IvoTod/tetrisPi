#include <SceneManager.h>
#include <ButtonManager.h>
#include <iostream>
#include <ali_colors.h>
#include <Button.h>
#include <Tetris.h>
#include <Text.h>
#include <NamePicker.h>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <Input.h>

void scoreboardPress() {
    SceneManager* sceneManager;
    sceneManager = sceneManager->getInstance();
    sceneManager->loadScoreboardScene();
    Input* input;
    input = input->getInstance();
    input->newFrame();
}

void playPress() {
    SceneManager* sceneManager;
    sceneManager = sceneManager->getInstance();
    sceneManager->loadInGameScene();
    Input* input;
    input = input->getInstance();
    input->newFrame();
}

void backPress() {
    SceneManager* sceneManager;
    sceneManager = sceneManager->getInstance();
    sceneManager->loadMainMenuScene();
    Input* input;
    input = input->getInstance();
    input->newFrame();

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

    setClear();
}

void SceneManager::loadInGameScene() {
    currentScene = Scene();
    Tetris* tetris = new Tetris();
    currentScene.addGameObject(tetris);

    setClear();
}

bool compareScores(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
    return a.second > b.second;
}

void SceneManager::loadScoreboardScene() {
    currentScene = Scene();
    std::vector<std::pair<std::string, int> > scores;
    std::ifstream iScoresFile("highscores.txt");
    std::string temp;
    while(iScoresFile >> temp) {
	std::string name = temp.substr(0, 3);
	std::string score = temp.substr(4);
	scores.push_back(std::pair<std::string, int>(name, std::stoi(score)));
    }
    iScoresFile.close();

    std::sort(scores.begin(), scores.end(), compareScores); 

    for(int i = 0; i < scores.size(); i++) {
	std::string scoreString;
	scoreString = scores[i].first + ":" + std::to_string(scores[i].second);
	Text* text = new Text(20, 10+i*10, scoreString, ALI_WHITE);
	currentScene.addGameObject(text);
    }

    Button* backButton = new Button(20, 135, 50, 20, "BACK", &backPress, ALI_WHITE, ALI_BLUE);
    ButtonManager* buttonManager = new ButtonManager(backButton);
    currentScene.addGameObject(backButton);
    currentScene.addGameObject(buttonManager);
    setClear();
}

void SceneManager::loadRecordScoreScene(int finalScore) {
    currentScene = Scene();

    NamePicker* np = new NamePicker(finalScore);

    currentScene.addGameObject(np);

    setClear();
}

void SceneManager::clearScreen(TFT_ST7735& tft) {
    if(clear) {
	clear = false;
	tft.setBackground(TFT_BLACK);
	tft.clearScreen();
    }
}

void SceneManager::setClear() {
    clear=true;
}

Scene& SceneManager::getCurrentScene() {
    return currentScene;
}

SceneManager* SceneManager::instance;

