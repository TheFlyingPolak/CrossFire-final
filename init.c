#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "operations.h"

/*	This file defines functions for the creation of the board and the players, as well as 
	printing both to the screen.  */

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
	for (int j = 0; j < BOARD_SIZE; j++){	// Slots in the first and last row, except board corners
		board[0][j].right = &board[0][j+1];
		board[0][j].left = &board[0][j-1];
		board[0][j].down = &board[1][j];
		board[0][j].up = NULL;

		board[BOARD_SIZE - 1][j].right = &board[BOARD_SIZE - 1][j + 1];
		board[BOARD_SIZE - 1][j].left = &board[BOARD_SIZE - 1][j - 1];
		board[BOARD_SIZE - 1][j].up = &board[BOARD_SIZE - 2][j];
		board[BOARD_SIZE - 1][j].down = NULL;
	}

	for (int i = 1; i < BOARD_SIZE - 1; i++){	// Slots in the first and last column, except board corners
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

	// Top-right corner of the board
	board[0][BOARD_SIZE - 1].left = &board[0][BOARD_SIZE - 2];
	board[0][BOARD_SIZE - 1].down = &board[1][BOARD_SIZE - 1];

	// Bottom-left corner of the board
	board[BOARD_SIZE - 1][0].right = &board[BOARD_SIZE - 1][1];
	board[BOARD_SIZE - 1][0].up = &board[BOARD_SIZE - 2][0];

	// Bottom-right corner of the board
	board[BOARD_SIZE - 1][BOARD_SIZE - 1].up = &board[BOARD_SIZE - 2][BOARD_SIZE - 1];
	board[BOARD_SIZE - 1][BOARD_SIZE - 1].left = &board[BOARD_SIZE - 1][BOARD_SIZE - 2];

	
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

void generatePlayers(struct player players[], int playerCount){
	char tmp[50];
	int choice;
	for (int i = 0; i < playerCount; i++){
		gets(tmp);
		memset(tmp, 0, 50);

		/*	Get each player's name  */
		printf("Player %d\nWhat is your name? ", i + 1);
		fgets(tmp, 50, stdin);
		strtok(tmp, "\n");
		players[i].name = calloc(strlen(tmp), sizeof(char));
		strcpy(players[i].name, tmp);
		
		/*	Get each player's type  */
		puts("What race art thou of?");
		puts("[1] Human");
		puts("[2] Elf");
		puts("[3] Wizard");
		puts("[4] Ogre");
		scanf("%d", &choice);
		while (choice < 1 || choice > 4){
			printf("Most honourable %s, I know not of such race!\n", players[i].name);
			scanf("%d", &choice);
		}
		players[i].type = choice - 1;

		/*	Initialise each player, set attributes  */
		switch(players[i].type){
		case HUMAN:	setHumanValues(&players[i]); break;
		case ELF:	setElfValues(&players[i]); break;
		case WIZARD:setWizardValues(&players[i]); break;
		case OGRE:	setOgreValues(&players[i]); break;
		}
		
		/*  Set each player's position on the board  */
		srand(time(NULL));
		players[i].posRow = rand() % BOARD_SIZE;
		players[i].posCol = rand() % BOARD_SIZE;
	}
}

void setElfValues(struct player *name){
	int j;

	/*Generates a random number and sets it to the corresponding variable
	in the struct.*/
	j = rand()%42+59;
	(*name).luck = j;

	j = rand()%32+69;
	(*name).smartness = j;

	j = rand()%50+1;
	(*name).strength = j;

	j = rand()%30+50;
	(*name).magic = j;

	j = rand()%100+1;
	(*name).dexterity = j;

	(*name).life = 100;
}

void setHumanValues(struct player *name){
	int j, total=301;

	/*While the total is greater than 300 then keep setting new values to the
	corresponding variable in the struct.*/
	while(total>300){
		j = rand()%100+1;
		(*name).luck = j;

		j = rand()%100+1;
		(*name).smartness = j;

		j = rand()%100+1;
		(*name).strength = j;

		j = rand()%100+1;
		(*name).dexterity = j;

		j = rand()%100+1;
		(*name).magic = j;

		(*name).life = 100;
		total = 0;
		total = ( (*name).luck + (*name).smartness + (*name).strength + (*name).dexterity + (*name).magic );
	}
}

void setOgreValues(struct player *name){
	int j, total;

	/*Generates a random number and sets it to the corresponding variable
	in the struct.*/
	j = rand()%49+1;
	(*name).luck = j;

	j = rand()%20+1;
	(*name).smartness = j;

	j = rand()%22+79;
	(*name).strength = j;

	j = rand()%22+79;
	(*name).dexterity = j;

	(*name).magic = 0;

	(*name).life = 100;

	total = ( ((*name).luck) + ((*name).smartness) );
	/*If the total is greater than 50 then loop around and generate new
	random numbers to assign the corresponding variable in the struct.*/
	if(total>50){
		while(total>50){
			j = rand()%49+1;
			(*name).luck = j;

			j = rand()%20+1;
			(*name).smartness = j;

			total = ( ((*name).luck) + ((*name).smartness) );
		}
	}
}

void setWizardValues(struct player *name){
	int j;

	/*Generates a random number and sets it to the corresponding variable
	in the struct.*/
	j = rand()%52+49;
	(*name).luck = j;

	j = rand()%12+89;
	(*name).smartness = j;

	j = rand()%20+1;
	(*name).strength = j;

	j = rand()%100+1;
	(*name).dexterity = j;

	j = rand()%22+79;
	(*name).magic = j;

	(*name).life = 100;
}

void printPlayers(struct player players[], int playerCount){
	int i;

	puts("Here are all warriors fighting today:");

	for (i = 0; i < playerCount; i++){
		printf("Sir %s\n", players[i].name);
		printf("Race - ");
		switch (players[i].type){
			case HUMAN:	puts("Human"); break;
			case ELF:	puts("Elf"); break;
			case WIZARD:puts("Wizard"); break;
			case OGRE:	puts("Ogre"); break;
		}
		printf("Strength  - %d\n", players[i].strength);
		printf("Dexterity - %d\n", players[i].dexterity);
		printf("Smartness - %d\n", players[i].smartness);
		printf("Magic     - %d\n", players[i].magic);
		printf("Luck      - %d\n", players[i].luck);
		printf("\n");
	}
}

void printBoard(struct slot **board, struct player players[], int playerCount){
	int i, j, k;
	
	for (i = 0; i < BOARD_SIZE; i++){
		for (j = 0; j < BOARD_SIZE; j++){
			if (board[i][j].type == 0)
				printf("Slot [%d][%d] - Ground ", i, j);
			else if (board[i][j].type == 1)
				printf("Slot [%d][%d] - Hills ", i, j);
			else if (board[i][j].type == 2)
				printf("Slot [%d][%d] - City ", i, j);
			for (k = 0; k < playerCount; k++){
				if (players[k].posRow == i){
					if (players[k].posCol == j)
						printf("- %s ", players[k].name);
				}
			}
			printf("\n");
		}
		printf("\n");
	}
	
/*	printf("   |");
	for (i = 0; i < BOARD_SIZE; i++){
		printf("%d          ", );
		
	}
	for (i = 0; i < BOARD_SIZE; i++){
		printf("%-2d |", i + 1);
		for (j = 0; j < BOARD_SIZE; j++){
			
		}
		printf("\n");
	}*/
}
