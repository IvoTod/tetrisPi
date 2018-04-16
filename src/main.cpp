#include <iostream>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <chrono>
#include <Input.h>
#include <tft_st7735.h>
#include <Button.h>
#include <ali_colors.h>


void initializeScreen(TFT_ST7735& tft);
void update(int ms);
void draw(TFT_ST7735& tft);
void clear(TFT_ST7735& tft);

void test() {
    std::cout << "Button pressed!" << std::endl;
}

int main () {
    using Clock = std::chrono::high_resolution_clock;
    auto OLD_FRAME_TIME = Clock::now();

    TFT_ST7735 tft      = *new TFT_ST7735(0, 24, 25, 32000000);

    wiringPiSetupGpio();      // initialize wiringPi and wiringPiGpio

    initializeScreen(tft);

    Input input = Input();
    Button button = Button(0, 0, 50, 20, "Button!", &test, ALI_WHITE, ALI_ORANGE);
    button.draw(tft);
    button.onPress();
    while(true) {
	
	auto CURRENT_FRAME_TIME = Clock::now();    

	int ELAPSED_TIME_MS = std::chrono::duration_cast<std::chrono::milliseconds>(CURRENT_FRAME_TIME - OLD_FRAME_TIME).count();
	input.update(ELAPSED_TIME_MS);
	update(ELAPSED_TIME_MS);
	draw(tft);

	//Doing this because the difference is way too small when code is being executed fast and therefore time appears "frozen"
	if(ELAPSED_TIME_MS != 0) { 
	    OLD_FRAME_TIME = CURRENT_FRAME_TIME;
	}
    }
}


void initializeScreen(TFT_ST7735& tft) {
    tft.commonInit();         // initialize SPI and reset display
    tft.initR();              // initialize display
    tft.setRotation(true);
    tft.setBackground(TFT_BLACK);
    tft.clearScreen();        // reset Display
}

void update(int ms) {

}

void draw(TFT_ST7735& tft) {

}

void clear(TFT_ST7735& tft) {
    tft.setBackground(TFT_BLACK);
    tft.clearScreen();
}
