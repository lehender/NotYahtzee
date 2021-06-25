/* Levi Henderson
Started: 6-10-2021
Not Yahtzee*/

#include "Classes.cpp"

int validateNumbers(int, scorecard&);
void choosehand(scorecard&, int, int&);
bool rerollorEnterScore(scorecard&, int&);
void goofyrollsremaining(scorecard, int);
void fillscore(scorecard&);

int numberofx(scorecard&, int); // for score validation
void xOfaKind(scorecard&, int);

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

	int holding[] = { 0, 0, 0, 0, 0, 0};

	while (inc <= 5 && rolls != 0)
	{

		player.displaydice();
		if (inc >= 1 || rolls < 2) // check if first roll, aka No held dice to show only blank space
			player.displayhelddice();

		std::cout << "\nINPUT: "; // ask user for input
		std::cin >> holding[inc]; // inc 0, default first position

		if (holding[inc] == 0) // if holding inc is 0, we dont enter any more values
			break; // exits while (inc <= 5) and returns to parent function, playertaketurn while loop
		else {
			holding[inc] = validateNumbers(holding[inc], player); // this makes sure the number is valid
			if (holding[inc] != 0) {
				player.sethelddice(holding[inc], inc);
			}
			inc++;
		}
	}
	if (rolls == 0)
	{
		for (int i = 0; i < 5; i++)
			if (player.getdice()[i] != 0)
				for (int j = 0; j < 5; j++)
					if (player.gethelddice()[j] == 0) {
						player.sethelddice(player.getdice()[i], j);
						player.setdice(i);
					}
		player.displayhelddice();
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
	int score;
	while (choosing)
	{
		pl.displayscorecard();
		std::cout << "Enter the corresponding character for the score you want to fill\nINPUT: ";
		std::cin >> choice;
		switch (tolower(choice))
		{
		case '1': // Number of 1s is:
			score = numberofx(pl, 1);
			if (score != 99) {
				choosing = false;
				pl.setscoretop(0, score);
			}
			break;
		case '2': // Number of 2s is:
			score = numberofx(pl, 2);
			if (score != 99) {
				choosing = false;
				pl.setscoretop(1, score);
			}
			break;
		case '3': // Number of 3s is:
			score = numberofx(pl, 3);
			if (score != 99) {
				choosing = false;
				pl.setscoretop(2, score);
			}
			break;
		case '4': // Number of 4s is:
			score = numberofx(pl, 4);
			if (score != 99) {
				choosing = false;
				pl.setscoretop(3, score);
			}
			break;
		case '5': // Number of 5s is:
			score = numberofx(pl, 5);
			if (score != 99) {
				choosing = false;
				pl.setscoretop(4, score);
			}
			break;
		case '6': // Number of 6s is:
			score = numberofx(pl, 6);
			if (score != 99) {
				choosing = false;
				pl.setscoretop(5, score);
			}
			break;
		case 'a': // 3 of a kind
			xOfaKind(pl, 3);
			if (score != 99) {
				choosing = false;
				pl.setscoretop(6, score);
			}
			break;
		case 'b': // 4 of a kind
			xOfaKind(pl, 4);
			if (score != 99)
				choosing = false;
			break;
		case 'c': // full house
			if (score != 99)
				choosing = false;
			break;
		case 'd': // sm straight
			if (score != 99)
				choosing = false;
			break;
		case 'e': // lg straight
			if (score != 99)
				choosing = false;
			break;
		case 'f': // YAHTZEE
			if (score != 99)
				choosing = false;
			break;
		case 'g': // chance
			if (score != 99)
				choosing = false;
			break;
		default:
			std::cout << "Please make a valid entry" << std::endl;
			break;
		}
	}
}

int numberofx(scorecard& pl, int num)
{
	int score = 0, inc = 0;
	char choice;
	bool confirm = true;

	for (int i = 0; i < 5; i++)
	{
		if (pl.gethelddice()[i] == num || pl.getdice()[i] == num){	 // this check if held OR REMAINING dice are equal to the score being checked against. 
			score += num;
			inc++;
		}
	}

	while (confirm) {
		std::cout << "You have " << inc << " " << num << "'s\nYou want to enter " << score << " as your score ? (y / n) : ";
		std::cin >> choice;
		switch (tolower(choice))
		{
		case 'y':
			std::cout << score << " added to " << num << std::endl;
			return score;
		case 'n':
			std::cout << "Returning to score card." << std::endl;
			return 99;
		default:
			std::cout << "Please enter a valid entry" << std::endl;
			break;
		}
	}
}

void xOfaKind(scorecard& pl, int num)
{
	int count;

	if (num == 3)
	{
		for (int i = 0; i < 5; i++)
		{
			std::cout << "COUNT!" << std::count(pl.getdice(), pl.getdice() + 5, i) << std::endl;
			count = std::count(pl.getdice(), pl.getdice() + 5, i);
			if (count >= 3) {
				std::cout << "Youre GOOD WIth a TOTAL of " << i * count << std::endl;
				break;
			}
			else
				std::cout << "Youre NOT good!" << std::endl;
		}

	}
	else if (num == 4)
	{

	}
}

int validateNumbers(int held, scorecard& player)
{
	bool valid = false;

	for (int i = 0; i < 5; i++)
		if (held == player.getdice()[i]) { // if the number the player chooses, is a number that is in the dice then its true
			valid = true;
			player.setdice(i); // this sets the dice in the position that matches the number the player holds to 0
			break; // if we find 1, we dont want to continue going through and finding duplicates, only 1
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
		return held; // returns value since it is in the rolled dice array
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
