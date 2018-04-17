#include <NamePicker.h>
#include <ali_colors.h>
#include <SceneManager.h>
#include <iostream>
#include <fstream>
#include <map>

#include <tft_st7735.h>

NamePicker::NamePicker(int score) :
    GameObject(),
    scoreToSave(score),
    selectedLetter(0)
{
    letters[0] = 26;
    letters[1] = 26;
    letters[2] = 26;
    input = input->getInstance(); 
}

void NamePicker::update(int ms) {
    if(input->isKeyPressed(UP)) {
	scrollLetterUp();
    }
    if(input->isKeyPressed(DOWN)) {
	scrollLetterDown();
    }
    if(input->isKeyPressed(LEFT)) {
	previousLetter();
    }
    if(input->isKeyPressed(RIGHT)) {
	nextLetter();
    }
    if(input->isKeyPressed(ACCEPT)) {
	saveScore();
	SceneManager* sm;
	sm = sm->getInstance();
	sm->loadMainMenuScene();
	input->newFrame();
    }
}

void NamePicker::draw(TFT_ST7735& tft) {
    if(!canDraw) {
	return;
    }
    std::string text = "What is your name?";
    tft.setBackground(ALI_BLACK);
    tft.drawString(16, 50, text.c_str(), ALI_WHITE, 1);
    std::string name = getCurrentName();

    for(int i = 0; i < 3; i++) {
	tft.drawString(37 + i*10 , 65, std::string(1, name[i]).c_str(), selectedLetter == i ? ALI_YELLOW : ALI_WHITE, 1);
    }

    canDraw = false;
}

void NamePicker::saveScore() {
    if(letters[0] == 26 && letters[1] == 26 && letters[2] == 26) {
	return;
    }
    std::map<std::string, int> scores;
    std::ifstream iScoresFile("highscores.txt");
    std::string temp;
    while(iScoresFile >> temp) {
	std::string name = temp.substr(0, 3);
	std::string score = temp.substr(4);
	scores[name] = std::stoi(score);
	std::cout << name << " : " << score << std::endl;
    }
    iScoresFile.close();
    std::string name = getCurrentName();
    scores[name] = scoreToSave;
    std::ofstream oScoresFiles("highscores.txt", std::ios::trunc);
    for(const auto& kv : scores) {
	oScoresFiles << kv.first << ":" << kv.second << "\n";
    }
    oScoresFiles.close();

}

void NamePicker::scrollLetterUp() {
    letters[selectedLetter] -= 1;
    if(letters[selectedLetter] <= -1) {
	letters[selectedLetter] = 26;
    }
    canDraw = true;
}

void NamePicker::scrollLetterDown() {
    letters[selectedLetter] += 1;
    if(letters[selectedLetter] >= 27) {
	letters[selectedLetter] = 0;
    }
    canDraw = true;
}

void NamePicker::nextLetter() {
    selectedLetter++;
    if(selectedLetter >= 3) {
	selectedLetter = 0;
    }
    canDraw = true;
}

void NamePicker::previousLetter() {
    selectedLetter--;
    if(selectedLetter <= -1) {
	selectedLetter = 2;
    }
    canDraw = true;
}

std::string NamePicker::getCurrentName() {
    std::string name;
    if(letters[0] == 26) {
	name.push_back('_');
    }
    else {
	name.push_back((char)('a' + letters[0]));
    }
    if(letters[1] == 26) {
	name.push_back('_');
    }
    else {
	name.push_back((char)('a' + letters[1]));
    }
    if(letters[2] == 26) {
	name.push_back('_');
    }
    else {
	name.push_back((char)('a' + letters[2]));
    }
    return name;
}
