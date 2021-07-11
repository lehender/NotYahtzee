#include "nHeader.h"


void player::displaydice(int select) // these show the dice in a nice easy to understand ASCII display
{
	int temparray[5];
	// std::sort(helddice,helddice + 5);
	if (select == 0)
	{
		std::cout << "YOUR ROLLED DICE" << std::endl;
		std::copy(std::begin(alldice), std::end(alldice), temparray);
	}
	else
	{
		std::cout << "YOUR HELD DICE " << std::endl;
		std::copy(std::begin(helddice), std::end(helddice), temparray);
	}
	
	for (int pass = 0; pass < 4; pass++)
	{
		for (int i = 0; i < numdice; i++) // output row 1 of all dice l > r
		{
			if(select != 0)
				color("red");
			switch (temparray[i])
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
					std::cout << "  _____  "; color("default");
					break;
				case 1:
					std::cout << " |o   o| "; color("default");
					break;
				case 2:
					std::cout << " |     | "; color("default");
					break;
				default:
					std::cout << " |o___o| "; color("default");
					break;
				}
				break;
			case 5:
				switch (pass) {
				case 0:
					std::cout << "  _____  "; color("default");
					break;
				case 1:
					std::cout << " |o   o| "; color("default");
					break;
				case 2:
					std::cout << " |  o  | "; color("default");
					break;
				default:
					std::cout << " |o___o| "; color("default");
					break;
				}
				break;
			case 6:
				switch (pass) {
				case 0:
					std::cout << "  _____  "; color("default");
					break;
				case 1:
					std::cout << " |o   o| "; color("default");
					break;
				case 2:
					std::cout << " |o   o| "; color("default");
					break;
				default:
					std::cout << " |o___o| "; color("default");
					break;
				}
			default: // 6
				break;

			}
		}
		std::cout << std::endl;
	}
	color("default");
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

std::string player::getname()
{
	return name;
}

void player::setname(std::string pname)
{
	name = pname;
}

void player::randcolor()
{
	SetConsoleTextAttribute(hConsole, (rand() % 255) + 1);
}

void player::color(std::string col)
{
	if (col == "default")
		SetConsoleTextAttribute(hConsole, 7);
	if(col == "gold")
		SetConsoleTextAttribute(hConsole, 6);
	if(col == "blue")
		SetConsoleTextAttribute(hConsole, 3);
	if (col == "bluebb")
		SetConsoleTextAttribute(hConsole, 144);
	if (col == "black")
		SetConsoleTextAttribute(hConsole, 0);
	if (col == "yellow")
		SetConsoleTextAttribute(hConsole, 14);
	if (col == "red")
		SetConsoleTextAttribute(hConsole, 4);
	if (col == "bluetext")
		SetConsoleTextAttribute(hConsole, 9);
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


//--------------------SCORECARD class functions

int scorecard::addtop()
{
	totalup = 0;
	for (int i = 0; i < 6; i++)
	{
		if (tops[i] != 'u' && tops[i] != '0')
			totalup += (int)tops[i];
	}
	if (totalup > 63)
		totalup += 35;
	return totalup;
}

void scorecard::displayscorecard() //MAKE SURE you arent doing any math in the table itself IMPORTANT BUG
{
	int sleept = 10;

	color("bluebb"); std::cout << "\n=UPPER_SECTION====================== "; color("default"); std::cout << " "; Sleep(sleept); std::cout << " ";  color("default");  Sleep(sleept);; color("default"); std::cout << " "; Sleep(sleept); std::cout << " ";  color("default");  Sleep(sleept); std::cout << "\n";
	color("blue"); std::cout << "(1)Number of 1s is: "; if (tops[0] == 'u') { std::cout << std::setw(18) << std::right << "Open|"; } else { std::cout << std::setw(17) << std::right << (int)tops[0] << "|"; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blue"); std::cout << "(2)Number of 2s is: "; if (tops[1] == 'u') { std::cout << std::setw(18) << std::right << "Open|"; }else { std::cout << std::setw(17) << std::right << (int)tops[1] << "|"; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blue"); std::cout << "(3)Number of 3s is: "; if (tops[2] == 'u') { std::cout << std::setw(18) << std::right << "Open|"; }else { std::cout << std::setw(17) << std::right << (int)tops[2] << "|"; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blue"); std::cout << "(4)Number of 4s is: "; if (tops[3] == 'u') { std::cout << std::setw(18) << std::right << "Open|"; }else { std::cout << std::setw(17) << std::right << (int)tops[3] << "|"; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blue"); std::cout << "(5)Number of 5s is: "; if (tops[4] == 'u') { std::cout << std::setw(18) << std::right << "Open|"; }else { std::cout << std::setw(17) << std::right << (int)tops[4] << "|"; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blue"); std::cout << "(6)Number of 6s is: "; if (tops[5] == 'u') { std::cout << std::setw(18) << std::right << "Open|"; }else { std::cout << std::setw(17) << std::right << (int)tops[5] << "|"; }color("default"); Sleep(sleept); std::cout << "\n";
	color("gold"); std::cout << "BONUS if upper score is over 63: "; if (addtop() > 63) { std::cout << "  35|"; } else { std::cout << "   0|"; }color("default"); Sleep(sleept); std::cout << "\n";
	color("gold"); std::cout << "Total Upper Score: " << std::setw(18) << std::right << addtop(); std::cout << "|"; color("default"); Sleep(sleept); std::cout << "\n";
	
	color("bluebb"); std::cout << "=LOWER_SECTION====================== "; color("default"); std::cout << " "; color("default"); std::cout << "\n";
	color("blue"); std::cout << "(a)Three of a kind is: ";	if (bottoms[0] == 'u') { std::cout << std::setw(15) << std::right << "Open|"; }else { std::cout << std::setw(14) << std::right << (int)bottoms[0] << "|"; }color("black"); Sleep(sleept); std::cout << " "; color("default"); std::cout << "\n";
	color("blue"); std::cout << "(b)Four of a kind is: ";		if (bottoms[1] == 'u') { std::cout << std::setw(16) << std::right << "Open|"; }else { std::cout << std::setw(15) << std::right << (int)bottoms[1] << "|"; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blue"); std::cout << "(c)Full House is: ";			if (bottoms[2] == 'u') { std::cout << std::setw(20) << std::right << "Open|"; }else { std::cout << std::setw(19) << std::right << (int)bottoms[2] << "|"; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blue"); std::cout << "(d)Small(4) straight is: ";	if (bottoms[3] == 'u') { std::cout << std::setw(13) << std::right << "Open|"; }else { std::cout << std::setw(12) << std::right << (int)bottoms[3] << "|"; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blue"); std::cout << "(e)Large(5) straight is: ";	if (bottoms[4] == 'u') { std::cout << std::setw(13) << std::right << "Open|"; }else { std::cout << std::setw(12) << std::right << (int)bottoms[4] << "|"; }color("default"); Sleep(sleept); std::cout << "\n";
	color("greenback"); std::cout << "(f)YAHTZEE"; color("blue"); std::cout << " (5 of a kind) is: ";	if (bottoms[5] == 'u') { std::cout << std::setw(9) << std::right << "Open|"; }else { std::cout << std::setw(8) << std::right << (int)bottoms[5] << "|"; }color("default"); Sleep(sleept); std::cout << "\n";
	color("blue"); std::cout << "(g)Chance (Add all 5 dice) is: "; if (bottoms[6] == 'u') { std::cout << std::setw(7) << std::right << "Open|"; }else { std::cout << std::setw(6) << std::right << (int)bottoms[6] << "|"; }color("default"); Sleep(sleept); std::cout << "\n";
	
	color("bluebb"); std::cout << "=TOTALS============================= "; color("default"); std::cout << " "; color("default"); std::cout << "\n";
	color("gold"); std::cout << "Total of Lower Section is: " << std::setw(10) << std::right << addbottom(); std::cout << "|"; color("default"); std::cout << " "; color("default"); Sleep(sleept); std::cout << "\n";
	color("gold"); std::cout << "Total of Upper Section is: " << std::setw(10) << std::right << addtop(); std::cout << "|"; color("default"); Sleep(sleept); std::cout << "\n";
	color("gold"); std::cout << "GRAND TOTAL is: " << std::setw(21) << std::right << (addtop() + addbottom()); std::cout << "|"; color("default"); Sleep(sleept); std::cout << std::endl;
	color("bluebb"); std::cout << "_                                    "; color("default"); std::cout << " "; color("default"); std::cout << "\n";
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
	{
		if (bottoms[5] == 'u')
			bottoms[5] = 0;
		bottoms[pos] += score;
	}
	else
		bottoms[pos] = score;
}

void scorecard::overwritescorebot(int pos, int score)
{
	bottoms[pos] = score;
}

bool scorecard::checkscore(int topbot, int pos)
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
	case 7:
		if (topbot == 1)
			if (bottoms[pos] == 'u')
				return true;
	default:
		color("red"); std::cout << "You cannot enter a score in that position"; color("default"); std::cout << std::endl;
		Sleep(500);
		return false;
	}
}

void scorecard::playertotal()
{
	total = addbottom() + addtop();
}
int scorecard::getscore()
{
	return addbottom() + addtop();
}

int scorecard::getTopScore(int pos)
{
	return tops[pos];
}

int scorecard::getBotScore(int pos)
{
	return bottoms[pos];
}