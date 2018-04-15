
#include <iostream>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <chrono>

#include <tft_st7735.h>
#include <tft_manager.h>
#include <tft_field.h>


int main () {
    int buffer[3] = {0,0,0};
    int counter   = -10;

    auto begin = std::chrono::high_resolution_clock::now();    

    TFT_ST7735 tft      = *new TFT_ST7735(0, 24, 25, 32000000);

    wiringPiSetupGpio();      // initialize wiringPi and wiringPiGpio

    tft.commonInit();         // initialize SPI and reset display
    tft.initR();              // initialize display
    tft.setRotation(true);
    tft.setBackground(TFT_BLACK);
    tft.clearScreen();        // reset Display

    auto end = std::chrono::high_resolution_clock::now();    
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    std::cout << ms << std::endl;
}
