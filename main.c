/*	main.c is the first file to be executed in the whole game  */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "operations.h"
#include "actions.h"

int main(void){
	setbuf(stdout, NULL);
	int playerCount, i, j;

	/*	Allocate memory for the board  */
	struct slot **board = malloc(BOARD_SIZE * sizeof(struct slot*));
	for (i = 0; i < BOARD_SIZE; i++){
		board[i] = malloc(BOARD_SIZE * sizeof(struct slot));

		/*	Set the row and column parameters for each slot  */
		for (j = 0; j < BOARD_SIZE; j++){
			board[i][j].row = i;
			board[i][j].column = j;
		}
	}
	/*	Initialise the board, setting all pointers to each slot on the board  */
	initBoard(board);

	/*	Welcome the user and ask for the number of players  */
	puts("Welcome to CrossFire, a game of fantasy, imagination and chance!");
	printf("Enter the number of warriors battling today (2 - 6): ");
	scanf("%d", &playerCount);
	
	/*	Check if the number of players is valid  */
	while (playerCount < 2 || playerCount > 6){
		if (playerCount == 1)
			puts("Playing alone is rather pointless, isn't it?");
		else
			puts("I'm sorry, we cannot accommodate this number of warriors!");
		scanf("%d", &playerCount);
	}

	/*	Create the array of players and generate all players  */
	struct player players[playerCount];
	generatePlayers(board, players, playerCount);
	
	/*	Print out a list of all generated players and the board  */
	puts("Here are all the warriors fighting today:");
	printPlayers(players, playerCount);
	wait();
	printBoard(board, players, playerCount);
	
	/*	Call the function which runs the actual game  */
	runGame(board, players, playerCount);
	
	/*	After the game has ended, show the winning player  */
	i = 0;
	while (players[i].position == NULL)
		i++;
	printf("Warrior %s is victorious!\n\n", players[i].name);
	puts("Thank you for playing CrossFire!");
	wait();
	
	return 0;
}
