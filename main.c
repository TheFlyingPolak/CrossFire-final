#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "operations.h"
#include "actions.h"

int main(void){
	setbuf(stdout, NULL);
	int playerCount, i, j;

	/*	Generate board  */
	struct slot **board = malloc(BOARD_SIZE * sizeof(struct slot*));
	for (i = 0; i < BOARD_SIZE; i++){
		board[i] = malloc(BOARD_SIZE * sizeof(struct slot));

		/*	Set the row and column parameters for each slot  */
		for (j = 0; j < BOARD_SIZE; j++){
			board[i][j].row = i;
			board[i][j].column = j;
		}
	}
	/*	Initialise the board  */
	initBoard(board);

	
	puts("Welcome to CrossFire, a game of fantasy, imagination and chance!");
	printf("Enter the number of warriors battling today (2 - 6): ");
	scanf("%d", &playerCount);
	while (playerCount < 2 || playerCount > 6){
		if (playerCount == 1)
			puts("Playing alone is rather pointless, isn't it?");
		else
			puts("I'm sorry, we cannot accommodate this number of warriors!");
		scanf("%d", &playerCount);
	}

	struct player players[playerCount];
	generatePlayers(players, playerCount);
	printPlayers(players, playerCount);
	printBoard(board, players, playerCount);
	
	runGame(board, players, playerCount);

	return 0;
}
