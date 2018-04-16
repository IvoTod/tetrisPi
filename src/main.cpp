#include <iostream>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <chrono>
#include <Input.h>
#include <tft_st7735.h>
#include <Scene.h>
#include <SceneManager.h>


void initializeScreen(TFT_ST7735& tft);
void update(int ms);
void draw(TFT_ST7735& tft);
void clear(TFT_ST7735& tft);


int main () {
    using Clock = std::chrono::high_resolution_clock;
    auto OLD_FRAME_TIME = Clock::now();

    TFT_ST7735 tft      = *new TFT_ST7735(0, 24, 25, 32000000);

    wiringPiSetupGpio();      // initialize wiringPi and wiringPiGpio

    initializeScreen(tft);

    Input* input;
    input = input->getInstance();
    SceneManager* sceneManager;
    sceneManager = sceneManager->getInstance();
    sceneManager->loadMainMenuScene();
    while(true) {
	auto CURRENT_FRAME_TIME = Clock::now();    

	int ELAPSED_TIME_MS = std::chrono::duration_cast<std::chrono::milliseconds>(CURRENT_FRAME_TIME - OLD_FRAME_TIME).count();
	input->update(ELAPSED_TIME_MS);
	Scene& currentScene = sceneManager->getCurrentScene();

	currentScene.update(ELAPSED_TIME_MS);

	currentScene.draw(tft);


	//Doing this because the difference is way too small when code is being executed fast and therefore time appears "frozen"
	if(ELAPSED_TIME_MS != 0) { 
	    OLD_FRAME_TIME = CURRENT_FRAME_TIME;
	}
	input->newFrame();
    }
}


void initializeScreen(TFT_ST7735& tft) {
    tft.commonInit();         // initialize SPI and reset display
    tft.initR();              // initialize display
    tft.setRotation(true);
    tft.setBackground(TFT_BLACK);
    tft.clearScreen();        // reset Display
}

void clear(TFT_ST7735& tft) {
    tft.setBackground(TFT_BLACK);
    tft.clearScreen();
}
