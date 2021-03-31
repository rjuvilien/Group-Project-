/*
	Alejandro Carvajal
	Naijian Xie
	Rejy Juvilien

	evergladesRPG.cpp

	An RPG where the player tries to rescue tourists from the everglades.

	Input:	user menu selection
			user movement
			user action

	Processing:	1. Display Menu & prompt for input
					1) Show Rules
						Display Rules and display menu again
					2) Play Game
						a) Generate random danger spawns
						b) Display Grid at starting position
						c) prompt user for move
						d) Verify validity of user move
								If invlaid - display error & prompt again
						e) Check space for danger
								If no danger:
									update and display grid
									update users last position for vailidation check
									-1 gong
									checkGongs
								If danger:
									Determine Danger type
									Display warning and prompt user for action (wait or fight)
										If wait:
											update and display grid
											-5 Gongs
											checkGongs
											update users last position for vailidation check
										If fight:
												If win:
													Remove danger from grid
													update and display grid
													-2 gongs
													checkGongs
													update users last position for vailidation check
												If lose:
													do not move ranger
													update and display grid
													-3 gongs
													checkGongs
													update users last position for vailidation check
						f) Check if Ranger has reached the tourists
							If yes:
								Congrats, victory screen!
							If no:
								back to c)

					3) Quit

	Output:	menu
			rules
			the entire game
*/

//Header Files
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

//Function Prototypes
void displayRules();
void setDangers(char[5][5]);
void showGrid(char[5][5], int, int, int, int, int);
int rangerDanger(string[4], int);
bool combat();
void checkGongs(int);
void gameOver();
void victory();

int main()
{
	//Constants & Variables
	int choice,					//Menu Selection
		row, col,				//User movement input
		gongs = 12;				//Gongs initialized to 12
	const int ROWS = 5, CLMNS = 5;	//Grid size
	//Grid at start position
	char grid[ROWS][CLMNS] = {	{'R', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', 'T'} };
	//Parallel array to store Danger positions
	char dangerGrid[ROWS][CLMNS] = { { 'N', 'N', 'N', 'N', 'N'},
									 { 'N', 'N', 'N', 'N', 'N'},
									 { 'N', 'N', 'N', 'N', 'N'},
									 { 'N', 'N', 'N', 'N', 'N'},
									 { 'N', 'N', 'N', 'N', 'N'} };
	//Array with danger names
	string dangerNames[4] = { "Hungry Alligator", "Swarm of Giant Mosquitos",
							"Venemous Spider", "Python" };
	//Parallel array with danger display Character
	char dangerTypes[4] = { 'A', 'M', 'S', 'P' };
	int danger;		//Stores randomly generated index for danger name/type
	int move;		//Stores the users action when confronting danger
	bool win;		//Stores whether the user wins or loses against danger in a fight
	int oldRow = 0, oldClmn = 0;	//Stores where the user was last

	//Intro
	cout << "\nLost in the Everglades ..." << endl;

	//Menu
	do
	{
		cout << "\nSelect one of the following:" << endl
			<< "\t1) See Rules." << endl
			<< "\t2) Play Game." << endl
			<< "\t3) Quit." << endl
			<< "Option: ";
		cin >> choice;

		switch (choice)
		{
			case 1:	//See Rules
				displayRules();
			break;
			case 2:	//Play Game

				//Generate danger positions
				setDangers(dangerGrid);
				
				//Show starting grid and begin the game
					cout << endl
						<< "     0   1   2   3   4" << endl;		//Grid Header
					for (int r = 0; r < 5; r++)
					{
						cout << r << "  | ";

						for (int c = 0; c < 5; c++)
						{
							cout << grid[r][c] << " | ";
						}
						cout << endl;
					}
					cout << "\nGongs Left: " << gongs << endl;

						do //Checks if Ranger has reached tourists
						{
							do //User input validation
							{
								cout << "\nEnter next cell (row & column seperated by a space): ";
								cin >> row >> col;

								if (row > (oldRow + 1) || row < (oldRow - 1))
									cout << "\nError ... Row must be adjacent to current position. Try again." << endl;
								if (col > (oldClmn + 1) || col < (oldClmn - 1))
									cout << "\nError ... Column must be adjacent to current position. Try again." << endl;
							} while (row > (oldRow + 1) || row < (oldRow - 1) || col >(oldClmn + 1) || col < (oldClmn - 1));
							
							//Check for danger
							if (dangerGrid[row][col] == 'Y')
							{
								//Check if the user has already uncovered danger here
								if (grid[row][col] == '*')
								{
									//Determine what type of danger will spawn
									srand(time(0));

									danger = rand() % 4;
								}
								else	//User previously uncovered danger, what was it?
								{
									if (dangerGrid[row][col] == 'A')
										danger = 0;
									else if (dangerGrid[row][col] == 'M')
										danger = 1;
									else if (dangerGrid[row][col] == 'S')
										danger = 2;
									else if (dangerGrid[row][col] == 'P')
										danger = 3;
								}

								//Call function to determine users next move
								move = rangerDanger(dangerNames, danger);

								//Execute users action
								switch (move)
								{
								case 1:	//Wait
									cout << "\n---> " << dangerNames[danger] << " is gone ... You Advance!" << endl;
									//Update gongs
									gongs -= 5;
									checkGongs(gongs);
								break;
								case 2:	//Fight
									win = combat();

									if (win == true)
									{						
										//Display win message
										cout << "\n---> You fight the " << dangerNames[danger]
											<< " and win ... You Advance!" << endl;
										//Remove danger from grid
										dangerGrid[row][col] = 'N';
										//Update gongs
										gongs -= 2;
										checkGongs(gongs);
									}
									else
									{										
										//Display lose message
										cout << "\n---> You fight the " << dangerNames[danger]
											<< " and lose ... Retreat." << endl;
										//Place danger on grid
										grid[row][col] = dangerTypes[danger];
										//Do not move Ranger
										row = oldRow;
										col = oldClmn;
										//Update gongs
										gongs -= 3;
										checkGongs(gongs);
									}
								break;
								}

							}
							else	//No danger, Ranger moves and loses 1 gong
							{
								cout << "---> Cell (" << row << "," << col << ") is Free ... You Advance!" << endl;
								gongs -= 1;
								checkGongs(gongs);
							}
														
							//Find Ranger in array in order to update the last spot to a blank
							for (int r = 0; r < 5; r++)
							{

								for (int c = 0; c < 5; c++)
								{
									if (grid[r][c] == 'R')
									{
										oldRow = r;
										oldClmn = c;
									}
								}
							}

							//Calls function that updates and shows grid
							showGrid(grid, row, col, oldRow, oldClmn, gongs);

							//Find Ranger in array in order to update the last spot for user validation
							for (int r = 0; r < 5; r++)
							{

								for (int c = 0; c < 5; c++)
								{
									if (grid[r][c] == 'R')
									{
										oldRow = r;
										oldClmn = c;
									}
								}
							}
						} while (grid[4][4] != 'R');
						victory();
			break;
			case 3:			//Quit
				cout << "\nGoodbye ..." << endl;
			break;
			default:		//Input Validation
				cout << "\nError ... Invalid selection. Try Again." << endl;
		}
	} while (choice != 3);

	return 0;
}

/*
	void displayRules()

	This function displays the rules of the game to the user.

	Returns: nothing
*/
void displayRules()
{
	//Variable
	const int BORDER = 100;		//Dash Border length

	//Display Rules
	cout << "\nA group of tourists (T) have been lost in the Everglades!" << endl
		<< "It's up to you, a brave ranger (R), to rescue them before time runs out!" << endl;
			for (int i = 1; i <= BORDER; i++)			//Dash border
				cout << "~";
	cout << endl << "You will start your journey in the North West and head to the South East to find the tourists." << endl
		<< "Time is measured by the strikes of a gong! The tourists will perish after 12 gong strikes!" << endl;
			for (int i = 1; i <= BORDER; i++)			//Dash border
				cout << "~";
			cout << endl << "During your journey you are sure to run into many dangers. You must choose to fight them or hide." << endl
				<< "But beware! If you choose to hide you will lose precious time!" << endl << endl;
}

/*
	void setDangers(char dangers[5][5])

	Randomly place exactly 10 dangers in 10 different spots, excluding Ranger starting
	position and Tourists position

	Returns: nothing
*/
void setDangers(char dangers[5][5])
{
	int row, col;

	//Seeding the random number generator with the internal clock of the CPU
	srand(time(0));

	//This loop sets the position of a random danger with each iteration
	for (int i = 0; i < 10; i++)
	{
		row = rand() % 5;

		//Ensures danger is not placed at rangers starting position
		if (row == 0)
			col = ((rand() % 4) + 1);
		else
		{
			//Ensures danger is not placed at tourists position
			if (row == 4)
				col = rand() % 4;
			else
				col = rand() % 5;
		}

		//Checks if a danger has already been placed in this spot
		if (dangers[row][col] == 'N')
			dangers[row][col] = 'Y';    //Places danger if new
		else
			i--;    //If repeat value, this iteration doesn't count
	}
   
}

/*
	void showGrid(char grid[5][5], int row, int col, int oldRow, int oldCol, int gongs)

	Updates and Displays the grid.

	Returns: nothing
*/
void showGrid(char grid[5][5], int row, int col, int oldRow, int oldCol, int gongs)
{
	
	grid[oldRow][oldCol] = ' ';		//Empties last position
	grid[row][col] = 'R';			//Places ranger in user input

	cout << endl
		<< "     0   1   2   3   4" << endl;		//Grid Header
	for (int r = 0; r < 5; r++)
	{
		cout << r << "  | ";

		for (int c = 0; c < 5; c++)
		{
			cout << grid[r][c] << " | ";
		}
		cout << endl;
	}
	cout << "\nGongs Left: " << gongs << endl;
}

/*
	int rangerDanger(string name[4], int type)

	Gets the users action in the face of danger

	Returns: int
*/
int rangerDanger(string name[4], int type)
{
	int move;	//Users action

	//Display warning & prompt action
	cout << "---> Watch out! Theres a " << name[type] << " ahead!" << endl;
	cout << "\nChoose your next move";
	do
	{
		cout << "\n\t1. Wait until it leaves."
			<< "\n\t2. Fight it."
			<< "\nMove: ";
		cin >> move;
		if (move < 1 || move > 2) //Input validation for move
			cout << "Error ... Please Choose a Valid Option." << endl;
	} while (move < 1 || move > 2);
	return move;
}

/*
	bool combat()

	Calculates odds of winning the fight and determines win or lose.

	Returns: bool
*/
bool combat()
{
	bool win;	//Result of fight
	int fight;	//Random chance of winning

	//Seeding the random number generator with the internal clock of the CPU
	srand(time(0));

	fight = rand() % 10;

	if (fight >= 3)	// 70% chance of winning
		win = true;
	else
		win = false;

	return win;
}

/*
	void checkGongs(int gongs)

	Checks if user has gongs remaining and ends the game if they do not.

	Returns: nothing
*/
void checkGongs(int gongs)
{
	if (gongs > 0)
		return;
	else
		gameOver();
}

/*
	void gameOver()

	Displays GAME OVER screen and kills program

	Returns: nothing
*/
void gameOver()
{
	//Game over message
	cout << "\nYou have failed to rescue the tourists ..." << endl
		<< endl
		<< "You ran out of gongs!" << endl
		<< endl
		<< " _____    ___  ___  ___ _____   _____  _   _ ___________" << endl
		<< "|  __ \\  / _ \\ |  \\/  ||  ___| |  _  || | | |  ___| ___ \\ " << endl
		<< "|  | \\/ / /_\\ \\| .  . || |__   | | | || | | | |__ | |_/ / " << endl
		<< "|  | __ |  _  || |\\/| ||  __|  | | | || | | |  __||   / " << endl
		<< "|  |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ / |___| |\\ \\ " << endl
		<< " \\_____/\\_| |_/\\_|  |_/\\____ /  \\___/  \\___/\\____/\\_| \\_| " << endl;
	//end program
	exit(0);
}

/*
	void victory()

	Displays victory message and ends program

	Returns: nothing
*/
void victory()
{
	//Display Victory message
	cout << "\nYou've rescued the tourists! Congratulations!" << endl
		<< endl
		<< " _   _ _____ _____ _____ _____________   __" << endl
		<< "| | | |_   _/  __ \\_   _|  _  | ___ \\ \\ / /" << endl
		<< "| | | | | | | /  \\/ | | | | | | |_/ /\\ V /" << endl
		<< "| | | | | | | |     | | | | | |    /  \\ /" << endl
		<< "\\ \\_/ /_| |_| \\__/\\ | | \\ \\_/ / |\\ \\  | |" << endl
		<< " \\___/ \\___/ \\____/ \\_/  \\___/\\_| \\_| \\_/" << endl;
	//End program
	exit(0);
}
