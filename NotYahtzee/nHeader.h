#pragma once

#define NOMINMAX

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <istream>
#include <windows.h>




class player
{
private:

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int alldice[5] = { 0,0,0,0,0 };
	int helddice[5] = { 0,0,0,0,0 };
	int const numdice = 5; 
	std::string name;

public:

	void timer(int);

	void displaydice(int); // these show the dice in a nice easy to understand ASCII display

	void roll();

	int* getdice();

	int* gethelddice();

	void setdice(int);

	void sethelddice(int, int);

	void resethelddice();

	std::string getname();

	void setname(std::string);

	void color(std::string);

	void debugdice(int, int);

	void randcolor();

};

class scorecard :public player
{
private:
	int totalup = 0, totallow = 0, total = 0;

	int tops[7] = { 'u', 'u', 'u', 'u', 'u', 'u', 'u' };	// 1 2 3 4 5 6 bonus
	int bottoms[7] = { 'u', 'u', 'u', 'u', 'u', 'u', 'u' };// 3of, 4of, fullH, smallStr, lrgStr, yaht, chance

	//int tops[7] = { 10,10,10,10,10,15,0 };	// DEBUG
	//int bottoms[7] = { 99,99,99,99,99,99,99 }; // DEBUG

public:

	void displayscorecard();

	int addtop();

	int addbottom();

	int topbonus();

	void setscoretop(int, int);

	void setscorebot(int, int);

	bool checkscore(int, int);

	int getTopScore(int );

	int getBotScore(int );

	void overwritescorebot(int, int);

	void playertotal();

	int getscore();

};


void PlayerGame(scorecard[], int&, int);

int validateNumbers(int, scorecard&);
void choosehand(scorecard&, int, int&);
bool rerollorEnterScore(scorecard&, int&);
void goofyrollsremaining(scorecard, int);
void fillscore(scorecard&);
void removeDiceHeld(scorecard&);
void forcealldiceheld(scorecard&);

int numberofx(scorecard&, int); // for score validation // 1-6 hands
int xOfaKind(scorecard&, int); // 3 and 4 of a kind
int fullhouse(scorecard&); // fullhouse
int chance(scorecard&);
int xStraight(scorecard&, int);

void titleshow(scorecard);

void noRollsLeft(scorecard);
void validchoice(scorecard);

void loadGame(scorecard[], int, int);