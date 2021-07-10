#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <windows.h>

#include "nHeader.h"



void player::timer(int milseconds)
{
	Sleep(milseconds);
}

void player::displaydice() // these show the dice in a nice easy to understand ASCII display
{

	std::cout << "YOUR ROLLED DICE" << std::endl;
	for (int pass = 0; pass < 4; pass++)
	{
		for (int i = 0; i < numdice; i++) // output row 1 of all dice l > r
		{
			switch (alldice[i])
			{
			case 1:
				switch (pass) {
				case 0:
					std::cout << "  _____  ";
					break;
				case 1:
					std::cout << " |     | ";
					break;
				case 2:
					std::cout << " |  o  | ";
					break;
				default:
					std::cout << " |_____| ";
					break;
				}
				break;
			case 2:
				switch (pass) {
				case 0:
					std::cout << "  _____  ";
					break;
				case 1:
					std::cout << " |o    | ";
					break;
				case 2:
					std::cout << " |     | ";
					break;
				default:
					std::cout << " |____o| ";
					break;
				}
				break;
			case 3:
				switch (pass) {
				case 0:
					std::cout << "  _____  ";
					break;
				case 1:
					std::cout << " |o    | ";
					break;
				case 2:
					std::cout << " |  o  | ";
					break;
				default:
					std::cout << " |____o| ";
					break;
				}
				break;
			case 4:
				switch (pass) {
				case 0:
					std::cout << "  _____  ";
					break;
				case 1:
					std::cout << " |o   o| ";
					break;
				case 2:
					std::cout << " |     | ";
					break;
				default:
					std::cout << " |o___o| ";
					break;
				}
				break;
			case 5:
				switch (pass) {
				case 0:
					std::cout << "  _____  ";
					break;
				case 1:
					std::cout << " |o   o| ";
					break;
				case 2:
					std::cout << " |  o  | ";
					break;
				default:
					std::cout << " |o___o| ";
					break;
				}
				break;
			case 6:
				switch (pass) {
				case 0:
					std::cout << "  _____  ";
					break;
				case 1:
					std::cout << " |o   o| ";
					break;
				case 2:
					std::cout << " |o   o| ";
					break;
				default:
					std::cout << " |o___o| ";
					break;
				}
			default: // 6
				break;

			}
		}
		std::cout << std::endl;
	}
}

void player::displayhelddice() // these show the dice in a nice easy to understand ASCII display
{
	// std::sort(helddice,helddice + 5);
	std::cout << "YOUR HELD DICE " << std::endl;
	for (int pass = 0; pass < 4; pass++)
	{
		for (int i = 0; i < numdice; i++) // output row 1 of all dice l > r
		{
			switch (helddice[i])
			{
			case 1:
				switch (pass) {
				case 0:
					color("red"); std::cout << "  _____  "; color("default");
					break;
				case 1:
					color("red"); std::cout << " |     | "; color("default");
					break;
				case 2:
					color("red"); std::cout << " |  o  | "; color("default");
					break;
				default:
					color("red"); std::cout << " |_____| "; color("default");
					break;
				}
				break;
			case 2:
				switch (pass) {
				case 0:
					color("red"); std::cout << "  _____  "; color("default");
					break;
				case 1:
					color("red"); std::cout << " |o    | "; color("default");
					break;
				case 2:
					color("red"); std::cout << " |     | "; color("default");
					break;
				default:
					color("red"); std::cout << " |____o| "; color("default");
					break;
				}
				break;
			case 3:
				switch (pass) {
				case 0:
					color("red"); std::cout << "  _____  "; color("default");
					break;
				case 1:
					color("red"); std::cout << " |o    | "; color("default");
					break;
				case 2:
					color("red"); std::cout << " |  o  | "; color("default");
					break;
				default:
					color("red"); std::cout << " |____o| "; color("default");
					break;
				}
				break;
			case 4:
				switch (pass) {
				case 0:
					color("red"); std::cout << "  _____  "; color("default");
					break;
				case 1:
					color("red"); std::cout << " |o   o| "; color("default");
					break;
				case 2:
					color("red"); std::cout << " |     | "; color("default");
					break;
				default:
					color("red"); std::cout << " |o___o| "; color("default");
					break;
				}
				break;
			case 5:
				switch (pass) {
				case 0:
					color("red"); std::cout << "  _____  "; color("default");
					break;
				case 1:
					color("red"); std::cout << " |o   o| "; color("default");
					break;
				case 2:
					color("red"); std::cout << " |  o  | "; color("default");
					break;
				default:
					color("red"); std::cout << " |o___o| "; color("default");
					break;
				}
				break;
			case 6:
				switch (pass) {
				case 0:
					color("red"); std::cout << "  _____  "; color("default");
					break;
				case 1:
					color("red"); std::cout << " |o   o| "; color("default");
					break;
				case 2:
					color("red"); std::cout << " |o   o| "; color("default");
					break;
				default:
					color("red"); std::cout << " |o___o| "; color("default");
					break;
				}
			default: // 6
				break;

			}
		}
		std::cout << std::endl;
	}
}

void player::roll()
{
	srand(time(NULL));

	for (int i = 0; i < numdice; i++) {
		// std::cout << "NHELD" << helddice[i] << std::endl; // DEBUG
		if (helddice[i] == 0) {
			alldice[i] = (rand() % 6) + 1;
			std::cin.clear();
			Sleep(5);
		}
		else
			alldice[i] = 0;
	}
	//for (int i = 0; i < numdice; i++) { // DEBUG
	//	std::cout << "OILL" << alldice[i] << std::endl;
}

int* player::getdice()
{
	return alldice;
}

int* player::gethelddice()
{
	return helddice;
}

void player::setdice(int numd)
{
	alldice[numd] = 0;
}

void player::debugdice(int dice, int num)
{
	alldice[dice] = num;
}

void player::sethelddice(int numd, int inc)
{
	helddice[inc] = numd;
}

void player::resethelddice()
{
	for (int i = 0; i < 5; i++)
		helddice[i] = 0;
}

void player::getname()
{
	std::cout << name;
}

void player::setname(std::string pname)
{
	name = pname;
}

void player::color(std::string col)
{
	if (col == "default")
		SetConsoleTextAttribute(hConsole, 7);
	if (col == "black")
		SetConsoleTextAttribute(hConsole, 0);
	if (col == "yellow")
		SetConsoleTextAttribute(hConsole, 14);
	if (col == "red")
		SetConsoleTextAttribute(hConsole, 4);
	if (col == "teal")
		SetConsoleTextAttribute(hConsole, 11);
	if (col == "green")
		SetConsoleTextAttribute(hConsole, 10);
	if (col == "goldback")
		SetConsoleTextAttribute(hConsole, 96);
	if (col == "blueback")
		SetConsoleTextAttribute(hConsole, 31);
	if (col == "tanback")
		SetConsoleTextAttribute(hConsole, 224);
	if (col == "greenback")
		SetConsoleTextAttribute(hConsole, 160);
	if (col == "grayback")
		SetConsoleTextAttribute(hConsole, 129);
	if (col == "redback")
		SetConsoleTextAttribute(hConsole, 71);
	if (col == "test")
		for (int i = 0; i < 255; i++)
		{
			SetConsoleTextAttribute(hConsole, i);
			std::cout << i << "THIS IS a test!!!" << std::endl;
		}
}


//--SCORECARD class functions

int scorecard::addtop()
{
	totalup = 0;
	for (int i = 0; i < 7; i++)
	{
		if (tops[i] != 'u' && tops[i] != '0')
			totalup += (int)tops[i];
	}
	return totalup;
}

void scorecard::displayscorecard()
{
	int sleept = 10;
	color("blueback"); std::cout << "\n(1)Number of 1s is: "; if (tops[0] == 'u') { std::cout << std::setw(17) << std::right << "Open"; }
	else { std::cout << (int)tops[0]; }color("black"); Sleep(sleept); std::cout << "\n";
	color("blueback"); std::cout << "(2)Number of 2s is: "; if (tops[1] == 'u') { std::cout << std::setw(17) << std::right << "Open"; }
	else { std::cout << (int)tops[1]; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blueback"); std::cout << "(3)Number of 3s is: "; if (tops[2] == 'u') { std::cout << std::setw(17) << std::right << "Open"; }
	else { std::cout << (int)tops[2]; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blueback"); std::cout << "(4)Number of 4s is: "; if (tops[3] == 'u') { std::cout << std::setw(17) << std::right << "Open"; }
	else { std::cout << (int)tops[3]; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blueback"); std::cout << "(5)Number of 5s is: "; if (tops[4] == 'u') { std::cout << std::setw(17) << std::right << "Open"; }
	else { std::cout << (int)tops[4]; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blueback"); std::cout << "(6)Number of 6s is: "; if (tops[5] == 'u') { std::cout << std::setw(17) << std::right << "Open"; }
	else { std::cout << (int)tops[5]; }color("default"); Sleep(sleept); std::cout << "\n";
	color("tanback"); std::cout << "BONUS if upper score is over 63: " << topbonus(); color("default"); Sleep(sleept); std::cout << "\n";
	color("tanback"); std::cout << "Total Upper Score: " << std::setw(15) << std::right << addtop(); color("default"); Sleep(sleept); std::cout << "\n";

	color("blueback"); std::cout << "\n(a)Three of a kind is: ";	if (bottoms[0] == 'u') { std::cout << std::setw(14) << std::right << "Open"; }
	else { std::cout << (int)bottoms[0]; }color("black"); Sleep(sleept); std::cout << " "; color("default"); std::cout << "\n";
	color("blueback"); std::cout << "(b)Four of a kind is: ";		if (bottoms[1] == 'u') { std::cout << std::setw(15) << std::right << "Open"; }
	else { std::cout << (int)bottoms[1]; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blueback"); std::cout << "(c)Full House is: ";			if (bottoms[2] == 'u') { std::cout << std::setw(19) << std::right << "Open"; }
	else { std::cout << (int)bottoms[2]; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blueback"); std::cout << "(d)Small(4) straight is: ";	if (bottoms[3] == 'u') { std::cout << std::setw(12) << std::right << "Open"; }
	else { std::cout << (int)bottoms[3]; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blueback"); std::cout << "(e)Large(5) straight is: ";	if (bottoms[4] == 'u') { std::cout << std::setw(12) << std::right << "Open"; }
	else { std::cout << (int)bottoms[4]; }color("default"); Sleep(sleept); std::cout << "\n";
	color("greenback"); std::cout << "(f)YAHTZEE"; color("blueback"); std::cout << " (5 of a kind) is: ";	if (bottoms[5] == 'u') { std::cout << std::setw(8) << std::right << "Open"; }
	else { std::cout << (int)bottoms[5]; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blueback"); std::cout << "(g)Chance (Add all 5 dice) is: "; if (bottoms[6] == 'u') { std::cout << std::setw(6) << std::right << "Open"; }
	else { std::cout << (int)bottoms[6]; }color("default"); Sleep(sleept); std::cout << "\n";

	color("tanback"); std::cout << "\nTotal of Lower Section is: " << std::setw(7) << std::right << addbottom(); color("black"); std::cout << " "; color("black"); Sleep(sleept); std::cout << "\n";
	color("tanback"); std::cout << "Total of Upper Section is: " << std::setw(7) << std::right << addtop(); color("default"); Sleep(sleept); std::cout << "\n";
	color("goldback"); std::cout << "GRAND TOTAL is: " << std::setw(10) << std::right << (addtop() + addbottom()); color("default"); Sleep(sleept); std::cout << std::endl << "\n";
}

int scorecard::addbottom()
{
	totallow = 0;
	for (int i = 0; i < 7; i++)
	{
		if (bottoms[i] != 'u')
			totallow += (int)bottoms[i];
	}
	return totallow;
}

int scorecard::topbonus()
{
	if (addtop() > 63) {
		tops[6] = 35;
		return 35;
	}

	else
		return 0;
}

void scorecard::setscoretop(int pos, int score)
{
	tops[pos] = score;
}

void scorecard::setscorebot(int pos, int score)
{
	if (pos == 5)
		bottoms[pos] += score;
	else
		bottoms[pos] = score;
}

bool scorecard::getscore(int topbot, int pos)
{
	pos--;

	// std::cout << "TOPBOT " << topbot << "POS " << pos << std::endl; // DEBUG

	switch (pos)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		if (topbot == 0)
			if (tops[pos] == 'u')
				return true;
			else {
				std::cout << "You cannot enter a score in that position\n";
				Sleep(500);
				return false;
			}

	case 7:
		if (topbot == 1)
			if (bottoms[pos] == 'u')
				return true;
		if (topbot == 0) {
			std::cout << "You cannot enter a score in that position\n";
			Sleep(500);
			return false;
		}
	default:
		std::cout << "You cannot enter a score in that position\n";
		Sleep(500);
		return false;
	}
}