/* Levi Henderson
Started: 6-10-2021
Not Yahtzee*/

#include "nHeader.h"


void playertaketurn(scorecard& player, int& turn, int numOfPlayers)
{
	int rolls = 2;
	int  inc = 0;
	bool inroll = true;

	player.resethelddice();

	player.color("green");
	std::cout << "\nInput the number of YOUR ROLLED DICE to move it to YOUR HELD DICE. Input 0 to advance to next roll or score entry.\n"; Sleep(100); std::cout << "EXAMPLE: 1[ENTER] 2[ENTER] 0[ENTER] end of turn.\n"; Sleep(100); std::cout << "EXAMPLE : 1 2 3 0[ENTER] end of turn\n";
	player.color("default"); std::cout << std::endl;
	Sleep(1000);

	while (rolls >= 0 && inroll) {
		player.roll();
		goofyrollsremaining(player, rolls);
		choosehand(player, rolls, inc);
		inroll = rerollorEnterScore(player, rolls);

	}
	forcealldiceheld(player);
	std::sort(player.gethelddice(), player.gethelddice() + 5);

	fillscore(player);

	switch (turn) // sets to next person
	{
	case 0:
	case 1:
	case 2:
		// std::cout << "TURN " << turn << " numofplayers = " << numOfPlayers << "\n"; // DEBUG
		if (turn < (numOfPlayers - 1))
			turn++;
		else
			turn = 0;
		break;
	default:
		turn = 0;
	}

}
//---------------------DEBUG FORCE HAND------####//---------------DEBUG FORCE HAND------####
void setDiceDEBUG(scorecard& pl)
{
	pl.debugdice(0, 5);
	pl.debugdice(1, 5);
	pl.debugdice(2, 5);
	pl.debugdice(3, 5);
	pl.debugdice(4, 5);

}
//---------------------DEBUG FORCE HAND------####//---------------DEBUG FORCE HAND------####
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

void showalldice(scorecard& player)
{
	for (int i = 0; i < 5; i++) {// check if first roll, aka No held dice to show only blank space
		if (player.getdice()[i] != 0) // as long as the hand is not all 0s we will see rolled dice.
		{
			player.displaydice(0);
			break;
		}
	}
	for (int i = 0; i < 5; i++) {// check if first roll, aka No held dice to show only blank space
		if (player.gethelddice()[i] != 0) 
		{
			player.displaydice(1);
			break;
		}
	}
}

void choosehand(scorecard& player, int rolls, int& inc)
{

	int holding[] = { 0, 0, 0, 0, 0, 0 };

	while (inc <= 5 && rolls != 0)
	{
		showalldice(player);

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
		forcealldiceheld(player);
		showalldice(player);
	}
}

void forcealldiceheld(scorecard& player)
{
	for (int i = 0; i < 5; i++) // looping all 5 dice
		if (player.getdice()[i] != 0) // checking each dice that does not equal 0
			for (int j = 0; j < 5; j++) // if a dice does NOT equal 0, we loop again 5 times
				if (player.gethelddice()[j] == 0) { // we get a specific held dice that equals 0 (they are in sequential order)
					player.sethelddice(player.getdice()[i], j); // we set the 0 dice to the number we caught with the for loop
					player.setdice(i); // we set the unheld dice to 0 so it is not taken into account / shown
				}
}

void noRollsLeft(scorecard player)
{
	player.color("red");  std::cout << "No rolls left. Must enter score."; player.color("default"); std::cout << std::endl;
	Sleep(500);
}

void validchoice(scorecard player)
{
	player.color("red");  std::cout << "Please enter a valid choice."; player.color("default"); std::cout << std::endl;
	Sleep(500);
}

bool rerollorEnterScore(scorecard& player, int& rolls) // main menu for most of the game. checks for rolls left and gives appropriate messages if none are. calls other functions based on selection
{
	char choice;

	while (true) {
		player.color("green");
		std::cout << "\n1. Roll Again\n2. Enter your rolled dice as a score\n3. Return held dice to rolled dice"; player.color("default"); std::cout << "\n";
		std::cout << "INPUT: ";
		std::cin >> choice;

		switch (choice)
		{
		case '1':
			if (rolls <= 0) 
				noRollsLeft(player);
			else
			{
				rolls--;
				return true;
			}
			break;
		case '2':
			// setDiceDEBUG(player); // DEBUG FORCE HAND DEBUG
			return false;
			break;
		case '3':
			if (rolls <= 0) 
				noRollsLeft(player);
			else
				removeDiceHeld(player);
			break;
		default:
			validchoice(player);
			break;
		}
	}
	return true;
}

void removeDiceHeld(scorecard& pl) // method uses a loop to find specific dice and dice placement in array, removes the dice and shifts dice after forward, placing a 0 at the end to lower the total count by 1
{
	int removal;
	bool found = false, sfound;

	showalldice(pl);

	while (true) {
		sfound = false;

		std::cout << "\nEnter a number of 1 dice you want to remove from your held dice or enter 0 to return\nINPUT: ";
		std::cin >> removal;
		
		if (removal != 0) {
			for (int i = 0; i < 6; i++) {
				if (removal == pl.gethelddice()[i]) {
					found = true;
					sfound = true;
					for (int c = i; c < 5; ++c) {
						if (c == 4)
							pl.gethelddice()[c] = 0;
						else
							pl.gethelddice()[c] = pl.gethelddice()[c + 1]; // https://stackoverflow.com/questions/879603/remove-an-array-element-and-shift-the-remaining-ones
						// std::cout << "your i " << i << " your c " << c << "\n"; // DEBUG
					}
					std::cout << removal << " removed..." << std::endl;
					showalldice(pl);
					break;
				}
			}
			if (sfound == false)
				validchoice(pl);

		}
		else {
			if (found == false)
				validchoice(pl);
			else
				std::cout << "Returning...\n";
			break;
		}
	}
}

void fillscore(scorecard& pl) // Switch responsible for allowing user to select the score to enter
{
	char choice;
	bool choosing = true;
	int score;

	while (choosing)
	{
		showalldice(pl);
		pl.displayscorecard();
		std::cout << "Enter the corresponding character for the score you want to fill\nINPUT: ";
		std::cin >> choice;
		switch (tolower(choice))
		{
		case '1': // Number of 1s,2s,3s etc is:
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
			if (pl.checkscore(0, ((int)choice - 48))) { // function prevents entering a score twice
				score = numberofx(pl, ((int)choice - 48)); // function that counts number user wants to count for score
				if (score != 99) {
					choosing = false;
					pl.setscoretop(((int)choice - 49), score);
				}
			}
			break;

		case 'a': // 3 of a kind
			if (pl.checkscore(1, 1)) { // needs to be 1 because by default we remove 1 in checkscore function
				score = xOfaKind(pl, 3);
				if (score != 99) {
					choosing = false;
					pl.setscorebot(0, score);
				}
			}
			break;
		case 'b': // 4 of a kind
			if (pl.checkscore(1, 2)) {
				score = xOfaKind(pl, 4);
				if (score != 99) {
					choosing = false;
					pl.setscorebot(1, score);
				}
			}
			break;
		case 'c': // full house
			if (pl.checkscore(1, 3)) {
				score = fullhouse(pl);
				if (score != 99) {
					choosing = false;
					pl.setscorebot(2, score);
				}
			}
			break;
		case 'd': // sm straight
			if (pl.checkscore(1, 4)) {
				score = xStraight(pl, 4);
				if (score != 99) {
					choosing = false;
					pl.setscorebot(3, score);
				}
			}
			break;
		case 'e': // lg straight
			if (pl.checkscore(1, 5)) {
				score = xStraight(pl, 5);
				if (score != 99) {
					choosing = false;
					pl.setscorebot(4, score);
				}
			}
			break;
		case 'f': // YAHTZEE
			score = xOfaKind(pl, 5);
			if (score != 99) {
				choosing = false;
				pl.setscorebot(5, score);
			}
			break;
		case 'g': // chance
			if (pl.checkscore(1, 7)) {
				score = chance(pl);
				if (score != 99) {
					choosing = false;
					pl.setscorebot(6, score);
				}
			}
			break;
		default:
			validchoice(pl);
			break;
		}
	}
}

int handChoice(scorecard& pl, std::string hand, int scoreToAdd)
{
	char choice;

	while (true) {
		if (scoreToAdd != 0)
		{
			pl.color("gold"); std::cout << "You have a " << hand << "!"; pl.color("default"); std::cout << "\nAdd " << scoreToAdd << " to your score ? (y / n) : ";
		}
		else
		{
			pl.color("red"); std::cout << "You don't have a " << hand << "."; pl.color("default"); std::cout << "\nAdd " << scoreToAdd << " to your score ? (y / n) : ";
		}
			
		std::cin >> choice;
		switch (tolower(choice))
		{
		case 'y':
			std::cout << scoreToAdd << " added to " << hand << std::endl;
			return scoreToAdd;
		case 'n':
			std::cout << "Returning to score card." << std::endl;
			return 99;
		default:
			validchoice(pl);
			break;
		}
	}
}
// vvv problem
int xStraight(scorecard& pl, int stsize)
{
	int counter = 0, starter, d = 0;

	starter = pl.gethelddice()[0]; // impossible straight if = 4||5||6 // BUG 1 3 4 5 6 does not register small straight

	switch (starter)
	{
	case 1:
	case 2:
	case 3:
		for (int i = starter; i < 7; i++)
		{
			// std::cout << "COUNTER> " << counter << " DICE> " << pl.gethelddice()[d] << " CHECK> " << i << std::endl; // DEBUG
			if (pl.gethelddice()[d] == i)
			{
				// std::cout << "TISEQUAL\n"; // DEBUG
				if (std::count(pl.gethelddice(), pl.gethelddice() + 5, i) > 1) {
					d+= std::count(pl.gethelddice(), pl.gethelddice() + 5, i); // since held dice are sorted, if there is more than 1 then we tell the program to skip the next one so we dont count it twice and throw off the straight ie 1,2,3,3,4 is a straight.
					counter++;
				}
				else {
					d++;
					counter++;
				}
			}
			else
			{
				if(counter < 4)
					counter = 0;
				d++;
			}
		}
		break;
	default:
		break;
	}
	// std::cout << "COUNTERz " << counter << " stsize " << stsize << std::endl;
	if (counter >= stsize)
	{
		if (stsize == 4)
			return handChoice(pl, "small straight", 30);
		else
			return handChoice(pl, "large straight", 40);
	}
	else
	{
		if (stsize == 4)
			return handChoice(pl, "small straight", 0);
		else
			return handChoice(pl, "large straight", 0);
	}
}
// ^^^ problem
int chance(scorecard& pl)
{
	int total = 0;

	for (int i = 0; i < 5; i++)
		total += pl.gethelddice()[i];

	return handChoice(pl, "total of " + std::to_string(total), total);
	
}

int fullhouse(scorecard& pl)
{
	int count;

	for (int i = 1; i < 7; i++) // 1 to 7 to ecompass all dice options
	{
		count = std::count(pl.gethelddice(), pl.gethelddice() + 5, i);
		// std::cout << "COUNT!" << std::count(pl.gethelddice(), pl.gethelddice() + 5, i) << " SEARCHING FOR " << i << std::endl; // DEBUG
		if (count == 3) {
			// std::cout << "YOURE IN!\n"; DEBUG
			for (int c = 1; c < 7; c++)
			{
				count = std::count(pl.gethelddice(), pl.gethelddice() + 5, c);
				// std::cout << "COUNTz!" << std::count(pl.gethelddice(), pl.gethelddice() + 5, c) << " SEARCHING FOR " << c << std::endl; // DEBUG
				if (count == 2) {
					return handChoice(pl, "full house", 25);
					
				}
			}

		}
	}
	return handChoice(pl, "full house", 0);
}

int numberofx(scorecard& pl, int num)
{
	int score = 0, inc = 0;

	for (int i = 0; i < 5; i++)
	{
		if (pl.gethelddice()[i] == num) {	 // this check if held OR REMAINING dice are equal to the score being checked against. 
			score += num;
			inc++;
		}
	}
	if(inc == 0)
		return handChoice(pl, std::to_string(num), score);
	else
		return handChoice(pl, std::to_string(inc) + " " + std::to_string(num) + "'s", score);
}

int xOfaKind(scorecard& pl, int num)
{
	int count;

	for (int i = 1; i < 7; i++) // 1 to 7 to ecompass all dice options
	{
		count = std::count(pl.gethelddice(), pl.gethelddice() + 5, i);
		// std::cout << "COUNT!" << std::count(pl.gethelddice(), pl.gethelddice() + 5, i) << std::endl; // DEBUG
		if (count >= num) {
			if (num == 5) // check for test yahtzee
				return handChoice(pl, "Yahtzee", 50);
			else
				return handChoice(pl, std::to_string(num) + " of a kind", (num * 10));
		}
	}
	if (num == 5) // check for test yahtzee
		return handChoice(pl, "Yahtzee", 0);
	else
		return handChoice(pl, std::to_string(num) + " of a kind", 0);
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
		validchoice(player);
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
	int turn = 0;
	char count;
	std::string name;

	while (true) {
		std::cout << "How many players will be playing today? (1,2,3,4)\nAlternatively, enter L to load from file\nINPUT: ";
		std::cin >> count;

		switch (count)
		{
		case '1':
		case '2':
		case '3':
		case '4':
			for (int i = 0; i < (count - 48); i++) {
				std::cout << "Enter player " << i + 1 << "'s name\nINPUT: "; // BUG need to use getline here // BUG user cant enter more than 1 name ie Bob Barker
				std::cin >> name;
				pl[i].setname(name);
				std::cout << std::endl;
			}
			PlayerGame(pl, turn, (count - 48));
			return;
		case 'l':
		case 'L':
			loadGame(pl, turn, (count - 48));
			break;
		default:
			validchoice(pl[0]);
			break;
		}
	}
}

void loadGame(scorecard pl[], int turn, int plcount)
{
	std::string holdname;
	int scorevalue;

	std::ifstream input_file("notyahtzeesave.txt");
	if (input_file.fail() == true) {

		pl[1].color("red"); std::cout << "Error opening file.\nCheck file name matches notyahtzeesave.txt and is in the correct directory."; pl[1].color("default"); std::cout << std::endl;
		Sleep(500);
		return;
	}
	else {
		input_file >> plcount;
		input_file.ignore(SIZE_MAX, '\n');
		input_file >> turn;
		input_file.ignore(SIZE_MAX, '\n');

		for (int i = 0; i < plcount; i++)
		{
			input_file >> holdname;
			input_file.ignore(SIZE_MAX, '\n');
			pl[i].setname(holdname);

			for (int t = 0; t < 7; t++) {
				input_file >> scorevalue;
				input_file.ignore(SIZE_MAX, '\n');
				pl[i].setscoretop(t, scorevalue);
			}

			for (int b = 0; b < 7; b++) {
				input_file >> scorevalue;
				input_file.ignore(SIZE_MAX, '\n');
				pl[i].overwritescorebot(b, scorevalue);
			}

		}
		input_file.close();

		PlayerGame(pl, turn, plcount);
	}
	
}

void saveAndQuit(scorecard pl[], int whosturn, int numPlayers)
{
	std::ofstream fout("notyahtzeesave.txt");

	fout << numPlayers << std::endl; // 1st, number of players
	fout << whosturn << std::endl; // whos turn it is

	for (int i = 0; i < numPlayers; i++) // for each player
	{
		fout << pl[i].getname() << std::endl;
		for (int t = 0; t < 7; t++)
			fout << pl[i].getTopScore(t) << std::endl;
		for (int b = 0; b < 7; b++)
			fout << pl[i].getBotScore(b) << std::endl;

	}
	std::cout << "Saved! to notyahtzeesave.txt";
	Sleep(1000);
	fout.close();
}

void checkWin(scorecard pl[], int numPlayers, bool& playing)
{
	bool gamewin = true;
	int topscore = 0;
	static std::string winnername;

	for (int i = 0; i < numPlayers; i++) // for each player
	{
		for (int t = 0; t < 7; t++)
			if (pl[i].getTopScore(t) == 'u' || pl[i].getBotScore(t) == 'u')
				gamewin = false;
	}
	if (gamewin == true) {
		for (int i = 0; i < 4; i++)
		{
			if (pl[i].getscore() > topscore) {
				winnername = pl[i].getname();
				topscore = pl[i].getscore();
			}
				
		}
		for (int i = 0; i < 40; i++) {
			pl[0].randcolor();
			std::cout << "Congratulations " << winnername << " you won the game!";
			pl[0].color("default");
			Sleep(25);
			std::cout << std::endl;
		}
		pl[0].color("default"); pl[0].color("default"); pl[0].color("default");
		playing = false;
		Sleep(2000);
	}
		

}

void PlayerGame(scorecard pl[], int& whosturn, int numOfPlayers)
{
	bool playing = true;
	int choice;

	while (playing)
	{
		checkWin(pl, numOfPlayers, playing);
		if (playing == false)
			break;
		std::cout << pl[whosturn].getname() << "'s turn!\n";
		std::cout << "1. Roll\n2. Check Score Card\n3. Save and Quit\nINPUT: ";
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
		case 3:
			saveAndQuit(pl, whosturn, numOfPlayers);
			playing = false;
			break;
		default:
			validchoice(pl[0]);
			break;
		}
	}
}

void titleshow(scorecard t)
{
	std::cout << "Welcome to..." << std::endl;
	Sleep(500);
	t.color("bluetext");
	std::cout << "|# |#  |## |#####  \\#   /#        |#                                   " << std::endl;
	std::cout << "|##\\# |# |#  |#     \\# /#  /###   |#_    |#_  _____  _____  _____        " << std::endl;
	std::cout << "|#\\## |# |#  |#      |#   |#  |#  |###  |### |##### |##### |#####        " << std::endl;
	std::cout << "|# \\# |# |#  |#      |#   |#  |#  |# |#  |#    /#__ |# =__ |# =__        " << std::endl;
	std::cout << "|# |#  |##   |#      |#    \\### # |# |#   |# |##### |##### |#####        " << std::endl;
	std::cout << "==================================================================        " << std::endl; t.color("default");
	Sleep(500);

}

int main()
{

	scorecard play1;
	scorecard play2;
	scorecard play3;
	scorecard play4;
	scorecard title; // needed for color change, tied to a class

	scorecard playerlist[4] = { play1, play2, play3, play4 };

	titleshow(title);
	Sleep(500);

	playercount(playerlist);

}