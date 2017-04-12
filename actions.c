#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "operations.h"
#include "actions.h"

/*	This file defines the functions necessary to run the game  */

char *titles[2] = {
	"Noble ",
	"Honourable "
};

char *questions[6] = {
	"life has offered you lemons. What shall thou do with them?",
	"how shalt thou directeth thy fate?",
	"what shall be thy decision?",
	"quickly now! What will you do?",
	"thy wish is the algorithm's command!",
	"the enemy is upon thy borders and knows no mercy! Thou must act quickly!"
};

void runGame(struct slot **board, struct player players[], int playerCount){
	int choice, counter = 0;
	bool rungame = true;
	srand(time(NULL));
	
	while (rungame){
		printf("%s %s, %s\n", titles[rand() % 2], players[counter].name, questions[rand() % 6]);
		puts("[1] - Move");
		puts("[2] - Attack");
		puts("[5] - Do nothing");
		puts("[0] - Leave game");
		scanf("%d", &choice);
		
		switch (choice){
			case 1:	//Move
				move(board, players[counter]);
				counter++;
				break;
			//case 2: Attack - does not exist yet
			case 5:
				puts("You passive coward!");
				counter++;
				break;
			//case 0: Leave game - does not exist yet
			default:
				puts("I'm sorry? I do not understand!");
				break;
		}
		
		if (counter == playerCount)
			rungame = false;
	}
}

void move(struct slot **board, struct player *name){
	puts("Hello");
}