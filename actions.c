/*	actions.c defines the functions necessary to run the game  */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "operations.h"
#include "actions.h"

/*	Array containing randomly chosen titles printed with each player at the beginning of the move.
	e.g. "Noble Aragorn..."  */
char *titles[2] = {
	"Noble",
	"Honourable"
};

/*	Array containing randomly chosen questions printed with each player at the beginning of the move.
	e.g. "Honourable Gandalf, how shalt thou directeth thy fate?"  */
char *questions[6] = {
	"life has offered you lemons. What shall thou do with them?",
	"how shalt thou directeth thy fate?",
	"what shall be thy decision?",
	"quickly now! What will you do?",
	"thy wish is the algorithm's command!",
	"the enemy is upon thy borders and knows no mercy! Thou must act quickly!"
};

/*	Function which accommodates the running of the game and defines game logic  */
void runGame(struct slot **board, struct player players[], int playerCount){
	int choice, counter = 0, remainingPlayers = playerCount;
	bool rungame = true;
	char c;
	srand(time(NULL));
	
	/*	Loop running for the whole duration of the game. When the number of remaining players if 1, the loop is terminated  */
	while (rungame){
		/*	Run the loop for the current player only if that player is still in the game, i.e. if
			the player's health is greater than 0  */
		if (players[counter].life > 0){
			/*	Ask the user to choose an action  */
			printf("%s %s, %s\n", titles[rand() % 2], players[counter].name, questions[rand() % 6]);
			puts("[1] - Move");
			puts("[2] - Attack");
			puts("[5] - Do nothing");
			puts("[0] - Leave game");
			scanf("%d", &choice);
		
			switch (choice){
				case 1:	// Move to an adjacent slot
					move(board, &players[counter]);
					wait();
					printPlayers(players, playerCount);
					printBoard(board, players, playerCount);
					counter++;
					break;
				//case 2: Attack - does not exist yet
				case 5:	// Skip turn
					puts("You passive coward!\n");
					getchar();	// Flush input stream
					wait();
					printPlayers(players, playerCount);
					printBoard(board, players, playerCount);
					counter++;
					break;
				case 0:	// Exit game
					/*	Ask the user to confirm leaving the game  */
					puts("Are you sure you wish to leave with such hasty abandon?");
					puts("Press Y to flee!");
					puts("Press any other key to turn back and fight!");
					scanf("%c", &c);	// Flush input stream
					scanf("%c", &c);
					/*	Allow user to leave the game only if the key 'y' is pressed  */
					if (c == 'y' || c == 'Y'){
						puts("Fare thee well, traitor!\n");
						/*	Eliminate the player from the game by setting health to 0 and position to NULL  */
						players[counter].life = 0;	
						players[counter].position = NULL;
						remainingPlayers--;		// Decrement the number of remaining players
						getchar();		// Flush input stream
						wait();
						printPlayers(players, playerCount);
						printBoard(board, players, playerCount);
						counter++;
					}
					/*	Otherwise allow him/her to choose an action again  */
					else{
						puts("Sir, it is good to have you back on our side!\n");
						getchar();		// Flush input stream
						wait();
					}
					break;
				default:	// Invalid input
					puts("I'm sorry? I do not understand!");
					break;
			}
			/*	End the game if the number of remaining players is down to 1  */
			if (remainingPlayers == 1)
				rungame = false;
		}
		else
			counter++;	// Increment game counter to move on to next player on the list
		
		/*	Revert game counter to 0 if the last player on the list had a turn  */
		if (counter == playerCount)
			counter = 0;
		
		printf("\n");
	}
}

/*	Function to accommodate movement to an adjacent slot  */
void move(struct slot **board, struct player *name){
	bool up = false, right = false, down = false, left = false, loop = true;
	int choice;
	
	/*	Check the slots around the player for possibility of movement  */
	if ((*name).position->up != NULL)
		up = true;
	if ((*name).position->right != NULL)
		right = true;
	if ((*name).position->down != NULL)
		down = true;
	if ((*name).position->left != NULL)
		left = true;

	puts("You may move in the following directions:");
	if (down == true)
		puts("[2] - down");
	if (left == true)
		puts("[4] - left");
	if (right == true)
		puts("[6] - right");
	if (up == true)
		puts("[8] - up");
	
	/*	Ask the user to choose direction  */
	while (loop){
		scanf("%d", &choice);
		switch (choice){
			case 2:	// Move down
				if (down == true){
					(*name).position = (*name).position->down;
					printf("Moved down to position (%d, %d)\n", (*name).position->row, (*name).position->column);
					loop = false;
				}
				else
					puts("Cannot move down");
				break;
			case 4:	// Move left
				if (left == true){
					(*name).position = (*name).position->left;
					printf("Moved left to position (%d, %d)\n", (*name).position->row, (*name).position->column);
					loop = false;
				}
				else
					puts("Cannot move left");
				break;
			case 6:	// Move right
				if (right == true){
					(*name).position = (*name).position->right;
					printf("Moved right to position (%d, %d)\n", (*name).position->row, (*name).position->column);
					loop = false;
				}
				else
					puts("Cannot move right");
				break;
			case 8:	// Move up
				if (up == true){
					(*name).position = (*name).position->up;
					printf("Moved up to position (%d, %d)\n", (*name).position->row, (*name).position->column);
					loop = false;
				}
				else
					puts("Cannot move up");
				break;
			default:	// Invalid input
				puts("Invalid input! Try again");
				break;
		}
	}
	/*	Flush the input buffer  */
	getchar();
}

/*	Function to ask the user to press ENTER to continue  */
void wait(void){
	puts("Press ENTER to continue\n");
	getchar();
}