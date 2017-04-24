/*	init.c defines functions for the creation of the board and the players, as well as 
	printing both to the screen.  */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "operations.h"

/*	Function to set pointers to adjacent slots to all slots on the board and slot types  */
void initBoard(struct slot **board){
	/*	Set pointers to adjacent slots for slots with 4 adjacent slots  */
	for (int i = 1; i < BOARD_SIZE - 1; i++){
		for (int j = 1; j < BOARD_SIZE - 1; j++){
			board[i][j].up = &board[i - 1][j];
			board[i][j].right = &board[i][j + 1];
			board[i][j].down = &board[i + 1][j];
			board[i][j].left = &board[i][j - 1];
		}
	}
	/*	Set pointers to adjacent slots for slots with 3 adjacent slots  */
	for (int j = 0; j < BOARD_SIZE; j++){	// Slots in the top and bottom row, except board corners
		board[0][j].right = &board[0][j + 1];
		board[0][j].left = &board[0][j - 1];
		board[0][j].down = &board[1][j];
		board[0][j].up = NULL;

		board[BOARD_SIZE - 1][j].right = &board[BOARD_SIZE - 1][j + 1];
		board[BOARD_SIZE - 1][j].left = &board[BOARD_SIZE - 1][j - 1];
		board[BOARD_SIZE - 1][j].up = &board[BOARD_SIZE - 2][j];
		board[BOARD_SIZE - 1][j].down = NULL;
	}

	for (int i = 1; i < BOARD_SIZE - 1; i++){	// Slots in the leftmost and rightmost column, except board corners
		board[i][0].right = &board[i][1];
		board[i][0].up = &board[i - 1][0];
		board[i][0].down = &board[i + 1][0];
		board[i][0].left = NULL;

		board[i][BOARD_SIZE - 1].left = &board[i][BOARD_SIZE - 2];
		board[i][BOARD_SIZE - 1].up = &board[i - 1][BOARD_SIZE - 1];
		board[i][BOARD_SIZE - 1].down = &board[i + 1][BOARD_SIZE - 1];
		board[i][BOARD_SIZE - 1].right = NULL;
	}
	/*	Set pointers to adjacent slots for slots with 2 adjacent slots  */
	// Top-left corner of the board
	board[0][0].right = &board[0][1];
	board[0][0].down = &board[1][0];
	board[0][0].left = NULL;
	board[0][0].up = NULL;

	// Top-right corner of the board
	board[0][BOARD_SIZE - 1].left = &board[0][BOARD_SIZE - 2];
	board[0][BOARD_SIZE - 1].down = &board[1][BOARD_SIZE - 1];
	board[0][BOARD_SIZE - 1].right = NULL;
	board[0][BOARD_SIZE - 1].up = NULL;

	// Bottom-left corner of the board
	board[BOARD_SIZE - 1][0].right = &board[BOARD_SIZE - 1][1];
	board[BOARD_SIZE - 1][0].up = &board[BOARD_SIZE - 2][0];
	board[BOARD_SIZE - 1][0].left = NULL;
	board[BOARD_SIZE - 1][0].down = NULL;

	// Bottom-right corner of the board
	board[BOARD_SIZE - 1][BOARD_SIZE - 1].up = &board[BOARD_SIZE - 2][BOARD_SIZE - 1];
	board[BOARD_SIZE - 1][BOARD_SIZE - 1].left = &board[BOARD_SIZE - 1][BOARD_SIZE - 2];
	board[BOARD_SIZE - 1][BOARD_SIZE - 1].right = NULL;
	board[BOARD_SIZE - 1][BOARD_SIZE - 1].down = NULL;
	
	/*	Set slot types  */
	srand(time(NULL));
	int x, i, j;
	for (i = 0; i < BOARD_SIZE; i++){
		for (j = 0; j < BOARD_SIZE; j++){
			x = rand() % 3;
			switch(x){
				case 0:	board[i][j].type = GROUND; break;
				case 1:	board[i][j].type = HILL; break;
				case 2:	board[i][j].type = CITY; break;
			}
		}
	}
}

/*	Function to set all players' name, type and attributes  */
void generatePlayers(struct slot **board, struct player players[], int playerCount){
	char tmp[50];
	int choice;
	for (int i = 0; i < playerCount; i++){
		gets(tmp);
		memset(tmp, 0, 50);

		/*	Get each player's name, calculate the length of the string and allocate sufficient
			memory to players[i].name  */
		printf("Player %d\nWhat is your name? ", i + 1);
		fgets(tmp, 50, stdin);
		strtok(tmp, "\n");	// Ensure that the newline character is removed from the string  
		players[i].name = malloc(strlen(tmp) * sizeof(char));
		strcpy(players[i].name, tmp);
		
		/*	Get each player's type  */
		puts("What race art thou of?");
		puts("[1] Human");
		puts("[2] Elf");
		puts("[3] Wizard");
		puts("[4] Ogre");
		scanf("%d", &choice);
		/*	Check if the input is valid  */
		while (choice < 1 || choice > 4){
			printf("Most honourable %s, I know not of such race!\n", players[i].name);
			scanf("%d", &choice);
		}
		players[i].type = choice - 1;	// The first number in choice list is 1 but the first number in the enumerator is 0

		/*	Initialise each player, set attributes  */
		switch(players[i].type){
		case HUMAN:	setHumanValues(&players[i]); break;
		case ELF:	setElfValues(&players[i]); break;
		case WIZARD:setWizardValues(&players[i]); break;
		case OGRE:	setOgreValues(&players[i]); break;
		}
		
		/*  Set each player's position on the board  */
		srand(time(NULL));
		int row = rand() % BOARD_SIZE;
		int col = rand() % BOARD_SIZE;
		players[i].position = &board[row][col];
	}
	/*	Flush the input buffer  */
	getchar();
}

/*	Function to assign attributes to elves according to preset rules  */
void setElfValues(struct player *name){
	int j;

	j = rand() % 42 + 59;
	(*name).luck = j;

	j = rand() % 32 + 69;
	(*name).smartness = j;

	j = rand() % 50 + 1;
	(*name).strength = j;

	j = rand() % 30 + 50;
	(*name).magic = j;

	j = rand() % 100 + 1;
	(*name).dexterity = j;

	(*name).life = 100;
}

/*	Function to assign attributes to humans according to preset rules  */
void setHumanValues(struct player *name){
	int j, total = 301;

	/*	While the total is greater than 300, keep setting new values to the
		corresponding variable in the struct.  */
	while(total > 300){
		j = rand() % 100 + 1;
		(*name).luck = j;

		j = rand() % 100 + 1;
		(*name).smartness = j;

		j = rand() % 100 + 1;
		(*name).strength = j;

		j = rand() % 100 + 1;
		(*name).dexterity = j;

		j = rand() % 100 + 1;
		(*name).magic = j;

		(*name).life = 100;
		total = 0;
		total = ( (*name).luck + (*name).smartness + (*name).strength + (*name).dexterity + (*name).magic );
	}
}

/*	Function to assign attributes to ogres according to preset rules  */
void setOgreValues(struct player *name){
	int j, total;

	j = rand() % 49 + 1;
	(*name).luck = j;

	j = rand() % 20 + 1;
	(*name).smartness = j;

	j = rand() % 22 + 79;
	(*name).strength = j;

	j = rand() % 22 + 79;
	(*name).dexterity = j;

	(*name).magic = 0;

	(*name).life = 100;

	total = ( ((*name).luck) + ((*name).smartness) );
	/*	If the total is greater than 50, loop around and generate new
	random numbers to assign the corresponding variable in the struct.  */
	if(total > 50){
		while(total > 50){
			j = rand() % 49 + 1;
			(*name).luck = j;

			j = rand() % 20 + 1;
			(*name).smartness = j;

			total = ( ((*name).luck) + ((*name).smartness) );
		}
	}
}

/*	Function to assign attributes to wizards according to preset rules  */
void setWizardValues(struct player *name){
	int j;

	j = rand() % 52 + 49;
	(*name).luck = j;

	j = rand() % 12 + 89;
	(*name).smartness = j;

	j = rand() % 20 + 1;
	(*name).strength = j;

	j = rand() % 100 + 1;
	(*name).dexterity = j;

	j = rand() % 22 + 79;
	(*name).magic = j;

	(*name).life = 100;
}

/*	Function to print a list of players remaining in the game  */
void printPlayers(struct player players[], int playerCount){
	int i;
	printf("Name      ");
	for (i = 0; i < playerCount; i++){
		if (players[i].life > 0){
			if (strlen(players[i].name) <= 20)
				printf("|%-20s", players[i].name);
			else
				printf("|%.17s...", players[i].name);
		}
	}
	printf("\n");
	printf("Race      ");
	for (i = 0; i < playerCount; i++){
		if (players[i].life > 0){
			switch(players[i].type){
				case HUMAN:	printf("|Human               "); break;
				case ELF:	printf("|Elf                 "); break;
				case WIZARD:printf("|Wizard              "); break;
				case OGRE:	printf("|Ogre                "); break;
			}
		}
	}
	printf("\n");
	printf("Health    ");
	for (i = 0; i < playerCount; i++){
		if (players[i].life > 0)
			printf("|%-20d", players[i].life);
	}
	printf("\n");
	printf("----------");
	for (i = 0; i < playerCount; i++){
		if (players[i].life > 0)
			printf("|--------------------");
	}
	printf("\n");
	printf("Strength  ");
	for (i = 0; i < playerCount; i++){
		if (players[i].life > 0)
			printf("|%-20d", players[i].strength);
	}
	printf("\n");
	printf("Dexterity ");
	for (i = 0; i < playerCount; i++){
		if (players[i].life > 0)
			printf("|%-20d", players[i].dexterity);
	}
	printf("\n");
	printf("Smartness ");
	for (i = 0; i < playerCount; i++){
		if (players[i].life > 0)
			printf("|%-20d", players[i].smartness);
	}
	printf("\n");
	printf("Magic     ");
	for (i = 0; i < playerCount; i++){
		if (players[i].life > 0)
			printf("|%-20d", players[i].magic);
	}
	printf("\n");
	printf("Luck      ");
	for (i = 0; i < playerCount; i++){
		if (players[i].life > 0)
			printf("|%-20d", players[i].luck);
	}
	printf("\n");
}

/*	Function to print the board with all remaining players on it  */
void printBoard(struct slot **board, struct player players[], int playerCount){
	int i, j, k;
	
	/*	Print column numbers  */
	printf("  ");
	for (i = 0; i < BOARD_SIZE; i++){
		printf("|%d             ", i + 1);
	}
	
	/*	Print horizontal line under column numbers  */
	printf("\n--");
	for (i = 0; i < BOARD_SIZE; i++)
		printf("---------------");
	
	
	printf("\n");
	/*	Loop for all rows on the board  */
	for (i = 0; i < BOARD_SIZE; i++){
		/*	Print row numbers  */
		printf("%d  ", i + 1);
		for (j = 0; j < BOARD_SIZE; j++){
			/*	Print slot type  */
			switch(board[i][j].type){
				case GROUND: printf("|____Ground____"); break;
				case HILL:	 printf("|^^^^^Hill^^^^^"); break;
				case CITY:	 printf("|/ / /City/ / /"); break;
			}
		}
		/*	Print player(s) (if any) located on the slot  */
 		for (j = 0; j < playerCount; j++){
			printf("\n  ");
			for (k = 0; k < BOARD_SIZE; k++){
				if (players[j].position == &board[i][k]){
					printf("|%d. ", j + 1);
					if (strlen(players[j].name) <= 10)
						printf("%-11s", players[j].name);
					else
						printf("%.7s... ", players[j].name);
				}
				else
					printf("|              ");
			}
		}
		/*	Print horizontal line between each row  */
		printf("\n--");
		for (j = 0; j < BOARD_SIZE; j++)
			printf("|--------------");
		printf("\n");
	}
}
