#ifndef __ALI_COLORS_H__
#define __ALI_COLORS_H__
#include <tft_st7735.h>
/*
 * Due to some hardware bug in my chinese display, red and blue are swapped
 * so I had to define my own colors that work with BGR
 * pls end my misery
 */

#define ALI_BLACK TFT_BLACK
#define ALI_GRAY TFT_GRAY
#define ALI_WHITE TFT_WHITE
#define ALI_RED TFT_BLUE
#define ALI_BLUE TFT_RED
#define ALI_GREEN TFT_GREEN
#define ALI_YELLOW (Color565(0,255,255))
#define ALI_ORANGE (Color565(0,165,255))
#define ALI_PURPLE TFT_PURPLE

#endif
