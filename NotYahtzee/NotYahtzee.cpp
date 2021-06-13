/* Levi Henderson
Started: 6-10-2021 
Not Yahtzee*/

#include "Classes.cpp"
int validateNumbers(int , scorecard);

void playertaketurn(scorecard player)
{
	int rolls = 2, inc = 0;
	int held[] = { 0, 0, 0, 0, 0 };
	int* importdice[5] = { 0, 0, 0, 0, 0 };
	std::cout << "\nYOU ROLLED: \n";
	player.roll();
	player.displaydice();
	player.setname("kyle"); std::cout << "\n";
	player.getname(); std::cout << "\n";

	std::cout << "\nRolls remaining: " << rolls;
	std::cout << "\n\nEnter a number you want to keep from your dice, press enter to keep that number\nIf you want to stop entering numbers, enter 0\n";
	Sleep(1000);

	while(rolls > 0 && inc < 5)
	{
		importdice = player.getdice();

		for (int i = 0; i < 5; i++)
			std::cout << player.getdice()[i];
		player.displaydice();
		for (int i = 0; i < 5; i++)
			std::cout << player.getdice()[i];

		std::cout << "\nINPUT: ";
		std::cin >> held[inc];

		if (held[inc] == 0)
			break;
		held[inc] = validateNumbers(held[inc], player);
		if (held[inc] != 0)
			inc++;
	}

	std::cout << "YOU HELD ";
	for (int i = 0; i < 5; i++)
		if (held[i] == 0)
			break;
		else
			std::cout << held[i] << " ";
	

}

int validateNumbers(int held, scorecard player)
{
	bool valid = false;
	player.getname(); std::cout << "\n";
	for(int i = 0; i < 5; i++)
		if (held == player.getdice()[i]) {
			valid = true;
			player.setdice(i);
			break;
		}
	if (valid == false){
		std::cout << "\nEnter a number that matches one of your dice\n"; 
		Sleep(250);
		return 0;
	}
	if (valid == true) {
		std::cout << held << " added to kept dice\n";
		Sleep(250);
		return held;
	}
}
void playerkeep()
{

}

int main()
{
	bool playing = true;
	int choice;
	player:scorecard play1;
	play1.setname("coolio");
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
