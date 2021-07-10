#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <windows.h>


class player
{
private:

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int alldice[5] = { 0,0,0,0,0 };
	int helddice[5] = { 0,0,0,0,0 };
	int const numdice = sizeof(alldice) / sizeof(alldice[0]); // This gets us the actual size of our array alldice (dividing the size in bytes by position of 0 byte)
	std::string name;

public:

	void timer(int);

	void displaydice(); // these show the dice in a nice easy to understand ASCII display

	void displayhelddice();

	void roll();

	int* getdice();

	int* gethelddice();

	void setdice(int);

	void sethelddice(int, int);

	void resethelddice();

	void getname();

	void setname(std::string);

	void color(std::string);

};

class scorecard :public player
{
private:
	int totalup = 0, totallow = 0;

	int tops[7] = { 'u', 'u', 'u', 'u', 'u', 'u', '0' };	// 1 2 3 4 5 6 bonus
	int bottoms[7] = { 'u', 'u', 'u', 'u', 'u', 'u', 'u' };// 3of, 4of, fullH, smallStr, lrgStr, yaht, chance

public:

	void displayscorecard();

	int addtop();

	int addbottom();

	int topbonus();

	void setscoretop(int, int);

	void setscorebot(int, int);

	bool getscore(int, int);

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