#include <Tetris.h>
#include <iostream>
#include <tft_st7735.h>
#include <ali_colors.h>
#include <random>

Tetris::Tetris() :
    GameObject(),
    baseDropTimer(750),
    currentTimer(0),
    currentDifficulty(0),
    maxDifficulty(5),
    currentScore(0),
    scoreForDifficultyIncrement(1000),
    currentTetromino(NULL),
    nextTetromino(NULL)
{
    input = input->getInstance();
    fillTetrominoList();
    field = std::vector<std::vector <Block*> >(12, std::vector<Block*>(8, NULL));
    prepareNewTetromino();
    spawnNextTetromino();
}

void Tetris::update(int ms) {
    if(input->isKeyPressed(DOWN)) {
	if(canMoveDown()) {
	    currentTetromino->moveDown();
	    canDraw = true;
	}
    }
    if(input->isKeyPressed(LEFT)) {
	if(canMoveLeft()) {
	    currentTetromino->moveLeft();
	    canDraw = true;
	}
    }
    if(input->isKeyPressed(RIGHT)) {
	if(canMoveRight()) {
	    currentTetromino->moveRight();
	    canDraw = true;
	}
    }
    if(input->isKeyPressed(ACCEPT)) {
	if(canRotate()) {
	    currentTetromino->rotate();
	    canDraw = true;
	}
    }

    currentTimer+=ms;
    int currentDropTimer = baseDropTimer + currentDifficulty * 50;

    if(currentTimer > currentDropTimer) {
	currentTimer-=currentDropTimer;
	if(canMoveDown()) {
	    currentTetromino->moveDown();
	}
	else {
	    placeTetromino();
	}
	canDraw = true;
    }
}

void Tetris::draw(TFT_ST7735& tft) {
    if(!canDraw) {
	return;
    }
    tft.setBackground(TFT_BLACK);
    tft.clearScreen();
    tft.drawRect(OFFSET, 0, 120, 120, ALI_BLUE);
    for(int i = 0; i < 12; i++) {
	for(int j = 0; j < 8; j++) {
	    if(!field[i][j]) {
		continue;
	    }
	    int x = j * BLOCK_WIDTH + OFFSET;
	    int y = i * BLOCK_HEIGHT;
	    tft.fillRect(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, field[i][j]->bgColor);
	    tft.drawRect(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, field[i][j]->borderColor);
	}
    }

    {//Draw next tetromino
	auto tBlocks = nextTetromino->getBlocks();
	for(int i = 0; i < 5; i++) {
	    for(int j = 0; j < 5; j++) {
		if(!tBlocks[i][j]) {
		    continue;
		}
		int x = j * BLOCK_WIDTH + 2 - BLOCK_WIDTH;
		int y = i * BLOCK_HEIGHT + 120;
		tft.fillRect(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, tBlocks[i][j]->bgColor);
		tft.drawRect(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, tBlocks[i][j]->borderColor);
	    }
	}
    }
    
    {//Draw current tetromino
	auto tBlocks = currentTetromino->getBlocks();
	const Vector2D& tPos = currentTetromino->getPos();
	for(int i = 0; i < 5; i++) {
	    for(int j = 0; j < 5; j++) {
		if(!tBlocks[i][j]) {
		    continue;
		}
		int x = j * BLOCK_WIDTH + tPos.x * BLOCK_WIDTH + OFFSET;
		int y = i * BLOCK_HEIGHT + tPos.y * BLOCK_HEIGHT;
		if(y < 0) {
		    continue;
		}
		tft.fillRect(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, tBlocks[i][j]->bgColor);
		tft.drawRect(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, tBlocks[i][j]->borderColor);
	    }
	}
    }

    canDraw=false;
}

void Tetris::fillTetrominoList() {
    //First Z tetromino
    int z1[5][5] =
    {
	{0,0,0,0,0},
	{0,0,1,0,0},
	{0,0,2,1,0},
	{0,0,0,1,0},
	{0,0,0,0,0}
    };
    tetrominoList.push_back(Tetromino(z1));
    //Second Z tetromino
    int z2[5][5] = 
    {
	{0,0,0,0,0},
	{0,0,1,0,0},
	{0,1,2,0,0},
	{0,1,0,0,0},
	{0,0,0,0,0}
    };
    tetrominoList.push_back(Tetromino(z2));
    //First L tetromino
    int l1[5][5] = 
    {
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,2,1,0},
	{0,0,0,0,0},
	{0,0,0,0,0}
    };
    tetrominoList.push_back(Tetromino(l1));
    //Second L tetromino
    int l2[5][5] = 
    {
	{0,0,0,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,1,2,0,0},
	{0,0,0,0,0}
    };
    tetrominoList.push_back(Tetromino(l2));
    //T tetromino
    int t[5][5] = 
    {
	{0,0,0,0,0},
	{0,0,1,0,0},
	{0,1,2,0,0},
	{0,1,0,0,0},
	{0,0,0,0,0}
    };
    tetrominoList.push_back(Tetromino(t));
    //Box tetromino
    int box[5][5] = 
    {
	{0,0,0,0,0},
	{0,1,1,0,0},
	{0,1,2,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0}
    };
    tetrominoList.push_back(Tetromino(box));
    //Line tetromino
    int line[5][5] = 
    {
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,1,2,1,1},
	{0,0,0,0,0},
	{0,0,0,0,0}
    };
    tetrominoList.push_back(Tetromino(line));
}

void Tetris::prepareNewTetromino() {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, tetrominoList.size()-1);
    Tetromino chosenTetromino =tetrominoList[distr(eng)];
    nextTetromino = new Tetromino();
    nextTetromino->copyTetromino(chosenTetromino);
}

void Tetris::spawnNextTetromino() {
    delete currentTetromino;
    currentTetromino = NULL;
    currentTetromino = nextTetromino;
    currentTetromino->setPos(1, -3);
    prepareNewTetromino();
}

void Tetris::placeTetromino() {
    auto tBlocks = currentTetromino->getBlocks();
    auto tPos = currentTetromino->getPos();
    for(int i = 0; i < 5; i++) {
	for(int j = 0; j < 5; j++) {
	    if(!tBlocks[i][j]) {
		continue;
	    }
	    int x = tPos.x + j;
	    int y = tPos.y + i;
	    if(y <= 0) {
		continue;
	    }
	    field[y][x] = tBlocks[i][j];
	    std::cout << "PLACING BLOCK" << std::endl;
	    std::cout << x << " " << y << std::endl;
	    std::cout << tPos.x << " " << tPos.y << std::endl;
	    std::cout << i << " " << j << std::endl;
	    std::cout << (tBlocks[i][j] != NULL) << std::endl;
	}
    }
    spawnNextTetromino();
    canDraw=true;
    std::cout << "Placed  tetromino on field, updated field:" << std::endl;
    for(int i = 0; i < 12; i++) {
	for(int j = 0; j < 8; j++) {
	    std::cout << (field[i][j] != NULL);
	}
	std::cout << std::endl;
    }
    
}

bool Tetris::canMoveLeft() {
    auto tBlocks = currentTetromino->getBlocks();
    auto tPos = currentTetromino->getPos();
    for(int i = 0; i < 5; i++) {
	for(int j = 0; j < 5; j++) {
	    if(!tBlocks[i][j]) {
		continue;
	    }
	    int x = j + tPos.x;
	    int y = i + tPos.y;
	    if(x <= 0) {
		return false;
	    }
	    if(field[x-1][y]) {
		return false;
	    }
	}
    }
    return true;
}

bool Tetris::canMoveRight() {
    auto tBlocks = currentTetromino->getBlocks();
    auto tPos = currentTetromino->getPos();
    for(int i = 0; i < 5; i++) {
	for(int j = 0; j < 5; j++) {
	    if(!tBlocks[i][j]) {
		continue;
	    }
	    int x = tPos.x + j;
	    int y = tPos.y + i;
	    if(x >= 7) {
		return false;
	    }
	    if(field[x+1][y]) {
		return false;
	    }
	}
    }
    return true;
}

bool Tetris::canMoveDown() {
    auto tBlocks = currentTetromino->getBlocks();
    auto tPos = currentTetromino->getPos();
    for(int i = 0; i < 5; i++) {
	for(int j = 0; j < 5; j++) {
	    if(!tBlocks[i][j]) {
		continue;
	    }
	    int x = tPos.x + j;
	    int y = tPos.y + i;
	    if(y >= 11) {
		return false;
	    }
	    if((y+1 >= 0) && (field[y+1][x])) {
		//std::cout << "FUCK YOU" << std::endl;
		//std::cout << field[x][y+1]
		return false;
	    }
	}
    }
    return true;
}

bool Tetris::canRotate() {
    Tetromino tempTetromino = Tetromino();
    tempTetromino.copyTetromino(currentTetromino);
    tempTetromino.rotate();
    auto tBlocks = tempTetromino.getBlocks();
    auto tPos = tempTetromino.getPos();
    for(int i = 0; i < 5; i++) {
	for(int j = 0; j < 5; j++) {
	    if(!tBlocks[i][j]) {
		continue;
	    }
	    int x = tPos.x + j;
	    int y = tPos.y + i;
	    if(y >= 12) {
		return false;
	    }
	    if(field[x][y+1] && y+1 >= 0) {
		return false;
	    }
	    if(x >= 8) {
		return false;
	    }
	    if(field[x+1][y]) {
		return false;
	    }
	}
    }
    return true;
}
