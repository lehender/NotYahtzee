#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>

class player
{
private:

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int alldice[5] = {0,0,0,0,0};
	int const numdice = sizeof(alldice)/ sizeof(alldice[0]); // This gets us the actual size of our array alldice (dividing the size in bytes by position of 0 byte)
	std::string name;

public:

	void timer(int milseconds)
	{
		Sleep(milseconds);
	}

	void displaydice() // these show the dice in a nice easy to understand ASCII display
	{

		for (int i = 0; i < numdice; i++) // output dice top
		{
			std::cout << "  _____  ";
		}

		std::cout << std::endl;
		for (int pass = 0; pass < 3; pass++)
		{
			for (int i = 0; i < numdice; i++) // output row 1 of all dice l > r
			{
				switch (alldice[i])
				{
				case 1:
					switch (pass) {
					case 0:
						std::cout << " |     | ";
						break;
					case 1:
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
						std::cout << " |o    | ";
						break;
					case 1:
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
						std::cout << " |o    | ";
						break;
					case 1:
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
						std::cout << " |o   o| ";
						break;
					case 1:
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
						std::cout << " |o   o| ";
						break;
					case 1:
						std::cout << " |  o  | ";
						break;
					default:
						std::cout << " |o___o| ";
						break;
					}
					break;
				default: // 6
					switch (pass) {
					case 0:
						std::cout << " |o   o| ";
						break;
					case 1:
						std::cout << " |o   o| ";
						break;
					default:
						std::cout << " |o___o| ";
						break;
					}
					break;
				}
			}
			std::cout << std::endl;
		}
	}


	void roll()
	{
		srand(time(NULL));

		for (int i = 0; i < numdice; i++) {
			//if(alldice[i] == 0)
				alldice[i] = (rand() % 6) + 1;
		}
	}

	int* getdice()
	{
		return alldice;
	}

	void setdice(int numd)
	{
		//std::cout << "REMOVED" << alldice[numd];
		alldice[numd] = 0;
		std::cout << "\n";

	}

	void getname()
	{
		std::cout << name;
	}
	void setname(std::string pname)
	{
		name = pname;
	}
	void color(std::string col)
	{
		if(col == "default")
			SetConsoleTextAttribute(hConsole, 7);
		if (col == "black")
			SetConsoleTextAttribute(hConsole, 0);
		if (col == "yellow")
			SetConsoleTextAttribute(hConsole, 14);
		if (col == "red")
			SetConsoleTextAttribute(hConsole, 4);
		if (col == "teal")
			SetConsoleTextAttribute(hConsole, 11);
		if (col == "goldback")
			SetConsoleTextAttribute(hConsole, 96);
		if (col == "blueback")
			SetConsoleTextAttribute(hConsole, 31);
		if (col == "tanback")
			SetConsoleTextAttribute(hConsole, 224);
		if (col == "greenback")
			SetConsoleTextAttribute(hConsole, 160);
		if(col == "test")
			for (int i = 0; i < 255; i++)
			{
				SetConsoleTextAttribute(hConsole, i);
				std::cout << i << "THIS IS a test!!!"<< std::endl;
			}
	}
};

class scorecard:public player
{
private:
	int totalup = 0, totallow = 0;

	char tops[7] = { 'u', 'u', 'u', 'u', 'u', 'u', '0'};
	char bottoms[7] = { 'u', 'u', 'u', 'u', 'u', 'u', 'u'};

public:
	void displayscorecard()
	{
		int sleept = 10;
		color("blueback"); std::cout << "\nNumber of 1s is: "; if (tops[0] == 'u') { std::cout << std::setw(17) << std::right << "Open"; }else { std::cout << tops[0]; }color("black"); Sleep(sleept); std::cout << " " << std::endl;
		color("blueback"); std::cout << "Number of 2s is: "; if (tops[1] == 'u') { std::cout << std::setw(17) << std::right << "Open"; }else { std::cout << tops[1]; }color("default"); Sleep(sleept); std::cout << std::endl;
		color("blueback"); std::cout << "Number of 3s is: "; if (tops[2] == 'u') { std::cout << std::setw(17) << std::right << "Open"; }else { std::cout << tops[2]; }color("default"); Sleep(sleept); std::cout << std::endl;
		color("blueback"); std::cout << "Number of 4s is: "; if (tops[3] == 'u') { std::cout << std::setw(17) << std::right << "Open"; }else { std::cout << tops[3]; }color("default"); Sleep(sleept); std::cout << std::endl;
		color("blueback"); std::cout << "Number of 5s is: "; if (tops[4] == 'u') { std::cout << std::setw(17) << std::right << "Open"; }else { std::cout << tops[4]; }color("default"); Sleep(sleept); std::cout << std::endl;
		color("blueback"); std::cout << "Number of 6s is: "; if (tops[5] == 'u') { std::cout << std::setw(17) << std::right << "Open"; }else { std::cout << tops[5]; }color("default"); Sleep(sleept); std::cout << std::endl;
		color("tanback"); std::cout << "BONUS if upper score is over 63: " << topbonus(); color("default"); Sleep(sleept); std::cout << std::endl;
		color("tanback"); std::cout << "Total Upper Score: " << std::setw(15) << std::right << addtop(); color("default"); Sleep(sleept); std::cout << std::endl;
		
		color("blueback"); std::cout << "\nThree of a kind is: ";	if (bottoms[0] == 'u') { std::cout << std::setw(14) << std::right << "Open"; }else { std::cout << bottoms[0]; }color("black"); Sleep(sleept); std::cout << " "; color("default"); std::cout << std::endl;
		color("blueback"); std::cout << "Four of a kind is: ";		if (bottoms[1] == 'u') { std::cout << std::setw(15) << std::right << "Open"; }else { std::cout << bottoms[1]; }color("default"); Sleep(sleept); std::cout << std::endl;
		color("blueback"); std::cout << "Full House is: ";			if (bottoms[2] == 'u') { std::cout << std::setw(19) << std::right << "Open"; }else { std::cout << bottoms[2]; }color("default"); Sleep(sleept); std::cout << std::endl;
		color("blueback"); std::cout << "Small(4) straight is: ";	if (bottoms[3] == 'u') { std::cout << std::setw(12) << std::right << "Open"; }else { std::cout << bottoms[3]; }color("default"); Sleep(sleept); std::cout << std::endl;
		color("blueback"); std::cout << "Large(5) straight is: ";	if (bottoms[4] == 'u') { std::cout << std::setw(12) << std::right << "Open"; }else { std::cout << bottoms[4]; }color("default"); Sleep(sleept); std::cout << std::endl;
		color("greenback"); std::cout << "YAHTZEE"; color("blueback"); std::cout << " (5 of a kind) is: ";	if (bottoms[5] == 'u') { std::cout << std::setw(8) << std::right << "Open"; }else { std::cout << bottoms[5]; }color("default"); Sleep(sleept); std::cout << std::endl;
		color("blueback"); std::cout << "Chance (Add all 5 dice) is: "; if (bottoms[6] == 'u') { std::cout << std::setw(6) << std::right << "Open"; }else { std::cout << bottoms[6]; }color("default"); Sleep(sleept); std::cout << std::endl;

		color("tanback"); std::cout << "\nTotal of Lower Section is: " << std::setw(7) << std::right << addbottom(); color("black"); std::cout << " "; color("black"); Sleep(sleept); std::cout << std::endl;
		color("tanback"); std::cout << "Total of Upper Section is: " << std::setw(7) << std::right << addtop(); color("default"); Sleep(sleept); std::cout << std::endl;
		color("goldback"); std::cout << "GRAND TOTAL is: " << std::setw(10) << std::right << (addtop() + addbottom()); color("default"); Sleep(sleept); std::cout << std::endl << std::endl;
	}

	int addtop()
	{
		for (int i = 0; i < 7; i++)
		{
			if (tops[i] != 'u' && tops[i] != '0' )
				totalup += tops[i];
		}
		return totalup;
	}

	int addbottom()
	{
		for (int i = 0; i < 7; i++)
		{
			if (bottoms[i] != 'u')
				totallow += bottoms[i];
		}
		return totallow;
	}

	int topbonus()
	{
		if (addtop() > 63){
			tops[6] = 35;
			return 35;
		}
			
		else
			return 0;
	}
};