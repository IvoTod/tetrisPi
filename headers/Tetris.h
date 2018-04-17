#ifndef __TETRIS_H__
#define __TETRIS_H__
/*
 * 128x160
 * 8 blocks wide - 15 width
 * 12 blocks high - 10 height
 */

#define BLOCK_WIDTH 15
#define BLOCK_HEIGHT 10
#define OFFSET 4

#include <GameObject.h>
#include <vector>
#include <Block.h>
#include <Input.h>
#include <Tetromino.h>
class TFT_ST7735;

class Tetris : public GameObject {
    public:
	Tetris();
	virtual void update(int ms);
	virtual void draw(TFT_ST7735& tft);
    private:
	void fillTetrominoList();
	void prepareNewTetromino();
	void spawnNextTetromino();
	void placeTetromino();
	bool canMoveRight();
	bool canMoveLeft();
	bool canMoveDown();
	bool canRotate();
	std::vector<std::vector <Block*> > field;
	std::vector<Tetromino> tetrominoList;
	Tetromino* currentTetromino;
	Tetromino* nextTetromino;
	int baseDropTimer;
	int currentTimer;
	int currentDifficulty;
	int maxDifficulty;
	int currentScore;
	int scoreForDifficultyIncrement;
	Input* input;
	bool canDraw=true;
	

};

#endif
