/* Levi Henderson
Started: 6-10-2021
Not Yahtzee*/

#include "Classes.cpp"

int validateNumbers(int, scorecard&);
void choosehand(scorecard&, int, int&);
bool rerollorEnterScore(scorecard&, int&);
void goofyrollsremaining(scorecard, int);
void fillscore(scorecard&);
void removeDiceHeld(scorecard&);

void PlayerGame(scorecard[], int&, int);

int numberofx(scorecard&, int); // for score validation // 1-6 hands
int xOfaKind(scorecard&, int); // 3 and 4 of a kind
int fullhouse(scorecard&); // fullhouse

void titleshow();

void playertaketurn(scorecard& player, int& turn, int numOfPlayers)
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

	switch (turn) // sets to next person
	{
	case 0:
	case 1:
	case 2:
		if (turn < (numOfPlayers - 1))
			turn++;
		break;
	default:
		turn = 0;
	}
		
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
	if (rolls == 0) // on the last roll, we dont want to decide what to hold and not hold. It can all be used towards score. This moves all new dice into player hands (red)
	{
		for (int i = 0; i < 5; i++) // looping all 5 dice
			if (player.getdice()[i] != 0) // checking each dice that does not equal 0
				for (int j = 0; j < 5; j++) // if a dice does NOT equal 0, we loop again 5 times
					if (player.gethelddice()[j] == 0) { // we get a specific held dice that equals 0 (they are in sequential order)
						player.sethelddice(player.getdice()[i], j); // we set the 0 dice to the number we caught with the for loop
						player.setdice(i); // we set the unheld dice to 0 so it is not taken into account / shown
					}
		player.displayhelddice();
	}
}

bool rerollorEnterScore(scorecard& player, int& rolls)
{
	char choice;

	while (true) {
		player.color("green");
		std::cout << "\n1. Enter your rolled dice as a score\n2. Roll again\n3. Return held dice to rolled dice"; player.color("default"); std::cout << "\n";
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
		case '3':
			if (rolls <= 0) {
				std::cout << "No rolls left. Must enter score." << std::endl;
				Sleep(500);
			}
			else
			{
				removeDiceHeld(player);
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

void removeDiceHeld(scorecard& pl)
{
	int removal;
	bool choosing = true;

	while (choosing && pl.gethelddice()[0] != 0) {
		std::cout << "\nEnter a number of 1 dice you want to remove from your held dice or enter 0 to cancel\nINPUT: ";
		std::cin >> removal;
		if (removal != 0) {
			for (int i = 5; i >= 0; i++)
				if (removal == pl.gethelddice()[i]) {
					pl.gethelddice()[i] = 0;
					std::cout << i << " removed..." << std::endl;
					break;
				}
			pl.displayhelddice();
		}
		else {
			break;
		}
	}
	std::cout << "No available dice in held." << std::endl;

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
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
			if (pl.getscore(0, ((int)choice - 48))) {
				score = numberofx(pl, ((int)choice - 48));
				if (score != 99) {
					choosing = false;
					pl.setscoretop(0, score);
				}
			}
			break;
	
		case 'a': // 3 of a kind
			score = xOfaKind(pl, 3);
			if (score != 99) {
				choosing = false;
				pl.setscoretop(6, score);
			}
			break;
		case 'b': // 4 of a kind
			score = xOfaKind(pl, 4);
			if (score != 99)
				choosing = false;
			break;
		case 'c': // full house
			score = fullhouse(pl);
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
			score = xOfaKind(pl, 5);
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

int fullhouse(scorecard& pl)
{
	int count, threeDice;

	for (int i = 1; i < 7; i++) // 1 to 7 to ecompass all dice options
	{
		count = std::count(pl.getdice(), pl.getdice() + 5, i);
		std::cout << "COUNT!" << count << std::endl; // DEBUG
		if (count == 3) {
			threeDice = i;
			for (int c = 1; i < 7; i++)
			{
				count = std::count(pl.getdice(), pl.getdice() + 5, i);
				if (count == 2 && i != threeDice) {
					std::cout << "YOu have FULL HOUSE ON TV?? DVD??";
					return 25;
				}
			}
			
		}

	}
	std::cout << "You don't have a full house" << std::endl;
	return 99;
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

int xOfaKind(scorecard& pl, int num)
{
	int count, score = 0;
	bool confirm = true;
	char choice;

	if (num == 3)
	{
		for (int i = 1; i < 7; i++) // 1 to 7 to ecompass all dice options
		{
			// std::cout << "COUNT!" << std::count(pl.gethelddice(), pl.gethelddice() + 5, i) << std::endl; // DEBUG
			count = std::count(pl.gethelddice(), pl.gethelddice() + 5, i);
			count += std::count(pl.getdice(), pl.getdice() + 5, i);

			if (count >= 3) {
				while (confirm) {
					std::cout << "You have " << count << " " << i << "'s in your hand.\n Add " << count * i << " to your score ? (y / n) : ";
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
		}
		std::cout << "You don't have 3(or more) of a kind" << std::endl;
		return 99;

	}
	else if (num == 4)
	{
		for (int i = 1; i < 7; i++)
		{
			// std::cout << "COUNT!" << std::count(pl.getdice(), pl.getdice() + 5, i) << std::endl; // DEBUG
			count = std::count(pl.gethelddice(), pl.gethelddice() + 5, i);
			count += std::count(pl.getdice(), pl.getdice() + 5, i);

			if (count >= 4) {
				while (confirm) {
					std::cout << "You have " << count << " " << i << "'s in your hand.\n Add " << count * i << " to your score ? (y / n) : ";
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
		}
		std::cout << "You don't have 4(or more) of a kind" << std::endl;
		return 99;
	}
	else if (num == 5)
	{
		for (int i = 1; i < 7; i++)
		{
			// std::cout << "COUNT!" << std::count(pl.getdice(), pl.getdice() + 5, i) << std::endl; // DEBUG
			count = std::count(pl.gethelddice(), pl.gethelddice() + 5, i);
			count += std::count(pl.getdice(), pl.getdice() + 5, i);

			if (count >= 4) {
				while (confirm) {
					std::cout << "You have a YAHTZEE!\n Add " << 50 << " to your score ? (y / n) : ";
					std::cin >> choice;
					switch (tolower(choice))
					{
					case 'y':
						std::cout << score << " added to " << num << std::endl;
						return 50;
					case 'n':
						std::cout << "Returning to score card." << std::endl;
						return 99;
					default:
						std::cout << "Please enter a valid entry" << std::endl;
						break;
					}
				}
			}
		}
		std::cout << "You don't have a Yahtzee" << std::endl;
		return 99;
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

void playercount(scorecard pl[])
{
	int count, turn = 0;
	std::string name;

	while (true) {
		std::cout << "How many players will be playing today? (1,2,3,4)\nINPUT: ";
		std::cin >> count;

		switch (count)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			for (int i = 0; i < count; i++) {
				std::cout << "Enter player " << i + 1 << "'s name\nINPUT: ";
				std::cin >> name;
				pl[i].setname(name);
				std::cout << std::endl;
			}
			PlayerGame(pl, turn, count);
			return;
		default:
			std::cout << "ERROR: Enter an appropriate value";
			break;
		}
	}
}

void PlayerGame(scorecard pl[], int& whosturn, int numOfPlayers )
{
	bool playing = true;
	int choice;

	while (playing)
	{
			pl[whosturn].getname(); std::cout << "'s turn!\n";
			std::cout << "1. Roll\n2. Check Card\nINPUT: ";
			std::cin >> choice;
			switch (choice)
			{
			case 1:
				playertaketurn(pl[whosturn], whosturn, numOfPlayers);
				std::cout << std::endl;
				break;
			case 2:
				pl[whosturn].displayscorecard();
				break;
			default:
				break;
			}
	}
}

void titleshow(scorecard t)
{
	std::cout << "Welcome to, Levi H's..." << std::endl;
	Sleep(500);
	t.color("red"); std::cout << "ooooo      ooo               .   "; t.color("default"); std::cout << std::endl;
	std::cout << "`888b.     `8'             .o8   "; t.color("default"); std::cout << std::endl;
	t.color("red"); std::cout << " 8 `88b.    8   .ooooo.  .o888oo "; t.color("default"); std::cout << std::endl;
	std::cout << " 8   `88b.  8  d88' `88b   888   "; t.color("default"); std::cout << std::endl;
	t.color("red"); std::cout << " 8     `88b.8  888   888   888   "; t.color("default"); std::cout << std::endl;
	std::cout << " 8       `888  888   888   888 . "; t.color("default"); std::cout << std::endl;
	t.color("red"); std::cout << "o8o        `8  `Y8bod8P'   {888/ "; t.color("default"); std::cout << std::endl;
	std::cout << "" << std::endl;
	t.color("red"); std::cout << "oooooo   oooo           oooo            .                                  .o. "; t.color("default"); std::cout << std::endl;
	std::cout << " `888.   .8'            `888          .o8                                  888 "; t.color("default"); std::cout << std::endl;
	t.color("red"); std::cout << "  `888. .8'    .oooo.    888 .oo.   .o888oo   oooooooo  .ooooo.   .ooooo.  888 "; t.color("default"); std::cout << std::endl;
	std::cout << "   `888.8'    `P  )88b   888P^Y88b    888    d'/|7d8P  d88' `88b d88' `88b Y8P "; t.color("default"); std::cout << std::endl;
	t.color("red"); std::cout << "    `888'      .oP^888   888   888    888      .d8P'   888ooo888 888ooo888 `8' "; t.color("default"); std::cout << std::endl;
	std::cout << "     888      d8(  888   888   888    888 .  .d8P'  .P 888    .o 888    .o .o. "; t.color("default"); std::cout << std::endl;
	t.color("red"); std::cout << "    o888o     `Y888/}8o o888o o888o   |888| d8888888P  `Y8bod8P' `Y8bod8P' Y8P "; t.color("default"); std::cout << std::endl;
	std::cout << std::endl;
	Sleep(500);

}

int main()
{

	scorecard play1;
	scorecard play2;
	scorecard play3;
	scorecard play4;
	scorecard title;

	scorecard playerlist[4] = { play1, play2, play3, play4 };

	titleshow(title);
	Sleep(500);

	playercount(playerlist);

}