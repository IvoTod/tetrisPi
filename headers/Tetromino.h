#ifndef __TETROMINO_H__
#define __TETROMINO_H__

#include <Vector2D.h>
#include <vector>
#include <Block.h>

class TFT_ST7735;

class Tetromino {
    public:
	Tetromino();
	Tetromino(int shape[5][5]);
	void moveDown();
	void moveLeft();
	void moveRight();
	void rotate();
	void copyTetromino(Tetromino& other);
	void copyTetromino(Tetromino* other);
	
	const Vector2D& getPos();
	void setPos(int x, int y);

	std::vector<std::vector<Block*> > getBlocks();
	
    private:
	Vector2D pos;
	std::vector<std::vector<Block*> > blocks;
	Vector2D pivotBlock;
	

};

#endif
