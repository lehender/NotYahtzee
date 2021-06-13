/* Levi Henderson
Started: 6-10-2021
Not Yahtzee*/

#include "Classes.cpp"

int validateNumbers(int, scorecard&);
void choosehand(scorecard&, int, int&);
bool rerollorEnterScore(scorecard&, int&);
void goofyrollsremaining(scorecard, int);
void fillscore(scorecard&);

int numberofx(scorecard, int num); // for score validation

void playertaketurn(scorecard& player)
{
	int rolls = 2;
	int  inc = 0;
	bool inroll = true;

	player.resethelddice();

	player.color("green");
	std::cout << "\nEnter a number you want to keep from your dice, either one at a time, or a number separated by a space. \nPress enter to keep the number(s)\nEnter 0 to keep your hand and re-roll if you have spare dice not held";
	player.color("default"); std::cout << std::endl;
	Sleep(1000);

	while (rolls >= 0 && inroll) {
		player.roll();
		goofyrollsremaining(player, rolls);
		choosehand(player, rolls, inc);
		inroll = rerollorEnterScore(player, rolls);

	}
	fillscore(player);
}
void goofyrollsremaining(scorecard pl, int rolls)
{
	switch (rolls)
	{
	case 2:
		pl.color("greenback"); std::cout << "\nFirst roll is!"; pl.color("default"); std::cout << std::endl;
		Sleep(100);
		break;
	case 1:
		pl.color("goldback"); std::cout << "\nSecond roll!"; pl.color("default"); std::cout << std::endl;
		Sleep(500);
		break;
	case 0:
		pl.color("redback"); std::cout << "\nFINAL ROLL"; pl.color("default"); std::cout << std::endl;
		Sleep(1000);
		break;
	}
}

void choosehand(scorecard& player, int rolls, int& inc)
{

	int holding[] = { 0, 0, 0, 0, 0, 0 };

	while (inc <= 5)
	{

		player.displaydice();
		if (inc >= 1 || rolls < 2)
			player.displayhelddice();

		std::cout << "\nINPUT: ";
		std::cin >> holding[inc];

		if (holding[inc] == 0)
			break;
		holding[inc] = validateNumbers(holding[inc], player);
		if (holding[inc] != 0) {
			player.sethelddice(holding[inc], inc);
			inc++;
		}
	}
}

bool rerollorEnterScore(scorecard& player, int& rolls)
{
	char choice;

	while (true) {
		player.color("green");
		std::cout << "\n1. Enter your held hand as a score\n2. Roll again"; player.color("default"); std::cout << "\n";
		std::cout << "INPUT: ";
		std::cin >> choice;

		switch (choice)
		{
		case '1':
			return false;
			break;
		case '2':
			if (rolls <= 0) {
				std::cout << "No rolls left. Must enter score." << std::endl;
				Sleep(500);
			}
			else
			{
				rolls--;
				return true;
			}
			break;
		default:
			std::cout << "\nPlease enter a valid choice. You cannot bypass entering a score.\n";
			Sleep(500);
			break;
		}
	}
	return true;
}

void fillscore(scorecard& pl)
{
	char choice;
	bool choosing = true;
	while (choosing)
	{
		pl.displayscorecard();
		std::cout << "Enter the corresponding character for the score you want to fill\nINPUT: ";
		std::cin >> choice;
		switch (tolower(choice))
		{
		case 'a': // Number of 1s is:
			numberofx(pl, 1);
			break;
		case 'b': // Number of 2s is:
			numberofx(pl, 2);
			break;
		case 'c': // Number of 3s is:
			numberofx(pl, 3);
			break;
		case 'd': // Number of 4s is:
			numberofx(pl, 4);
			break;
		case 'e': // Number of 5s is:
			numberofx(pl, 5);
			break;
		case 'f': // Number of 6s is:
			numberofx(pl, 6);
			break;
		case 'g': // 3 of a kind
			break;
		case 'h': // 4 of a kind
			break;
		case 'i': // full house
			break;
		case 'j': // sm straight
			break;
		case 'k': // lg straight
			break;
		case 'l': // YAHTZEE
			break;
		case 'm': // chance
			break;
		default:
			std::cout << "Please make a valid entry" << std::endl;
			break;
		}
	}
}

int numberofx(scorecard pl, int num)
{
	int score = 0;
	char choice;
	bool confirm = true;

	for (int i = 0; i < 5; i++)
	{
		if (pl.gethelddice()[i] == num)
			score += num;
	}

	while (confirm) {
		std::cout << "You want to enter " << score << " as your score?(y/n): ";
		std::cin >> choice;
		switch (tolower(choice))
		{
		case 'y':
			std::cout << "Please enter a valid entry" << std::endl;
			return score;
		case 'n':
			std::cout << "Please enter a valid entry" << std::endl;
			return 0;
		default:
			std::cout << "Please enter a valid entry" << std::endl;
			break;
		}
	}
}

int validateNumbers(int held, scorecard& player)
{
	bool valid = false;

	for (int i = 0; i < 5; i++)
		if (held == player.getdice()[i]) {
			valid = true;
			player.setdice(i);
			break;
		}
	if (valid == false) {
		std::cout << "\nEnter a number that matches one of your dice\n";
		if (held > 10) {
			std::cout << "Did you mean to enter a space between your numbers?\n";
		}
		Sleep(250);
		return 0;
	}
	if (valid == true) {
		Sleep(250);
		return held;
	}
}


int main()
{
	bool playing = true;
	int choice;

player:scorecard play1;

	play1.setname("Coolio");
	play1.getname(); std::cout << "\n";

	while (playing)
	{
		std::cout << "1. Roll\n2. Check Card\nINPUT: ";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			playertaketurn(play1);
			std::cout << std::endl;
			break;
		case 2:
			play1.displayscorecard();
			break;
		default:
			break;
		}

	}

}
