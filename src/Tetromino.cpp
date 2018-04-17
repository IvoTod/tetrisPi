#include <Tetromino.h>
#include <iostream>

Tetromino::Tetromino() {}

Tetromino::Tetromino(int shape[5][5]) {
    using std::vector;
    blocks = vector<vector<Block*> >(5, vector<Block*>(5, NULL));
    for(int i = 0; i < 5; i++) {
	for(int j = 0; j < 5; j++) {
	    if(shape[i][j] == 0) {
		continue;
	    }
	    blocks[i][j] = new Block();
	    if(shape[i][j] == 2) {
		pivotBlock = Vector2D(j, i);
	    }
	}
    }
}

void Tetromino::moveDown() {
    pos.y += 1;
}

void Tetromino::moveLeft() {
    pos.x -= 1;
}

void Tetromino::moveRight() {
    pos.x += 1;
}

void Tetromino::rotate() {
    using std::vector;
    auto tempBlocks = vector<vector<Block*> >(5, vector<Block*>(5, NULL));
    for(int i = 0; i < 5; i++) {
	for(int j = 0; j < 5; j++) {
	    if(j == pivotBlock.x && i == pivotBlock.y) {
		continue;
	    }
	    if(!blocks[i][j]) {
		continue;
	    }
	    int x = i - pivotBlock.x;
	    int y = j - pivotBlock.y;
	    int newX = -y;
	    int newY = x;
	    newX += pivotBlock.x;
	    newY += pivotBlock.y;
	    

	    tempBlocks[newX][newY] = blocks[i][j];
	}
    }
    tempBlocks[pivotBlock.x][pivotBlock.y] = blocks[pivotBlock.x][pivotBlock.y];
    blocks = tempBlocks;
}

void Tetromino::copyTetromino(Tetromino& other) {
    using std::vector;
    blocks = vector<vector<Block*> >(5, vector<Block*>(5, NULL));
    for(int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++) {
	    if(!other.blocks[i][j]) {
		continue;
	    }
	    blocks[i][j] = new Block();
	}
    }
    pivotBlock = other.pivotBlock;
    pos = other.pos;
}

void Tetromino::copyTetromino(Tetromino* other) {
    using std::vector;
    blocks = vector<vector<Block*> >(5, vector<Block*>(5, NULL));
    for(int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++) {
	    if(!other->blocks[i][j]) {
		continue;
	    }
	    blocks[i][j] = new Block();
	}
    }
    pivotBlock = other->pivotBlock;
    pos = other->pos;
}

const Vector2D& Tetromino::getPos() {
    return pos;
}

void Tetromino::setPos(int x, int y) {
    pos.x = x;
    pos.y = y;
}

std::vector<std::vector<Block*> > Tetromino::getBlocks() {
    return blocks;
}
