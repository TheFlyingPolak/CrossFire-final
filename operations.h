#ifndef OPERATIONS_H_
#define OPERATIONS_H_
#define BOARD_SIZE 7

/*	This file contains the definitions of slot and player structures and prototypes of functions
	for the creation of the board and the players, as well as printing both to the screen.  */

enum slotType{GROUND, HILL, CITY};

struct slot{
	int row;
	int column;
	struct slot *left;
	struct slot *right;
	struct slot *up;
	struct slot *down;
	enum slotType type;
}slot;

enum playerType{HUMAN, ELF, WIZARD, OGRE};

struct player{;
	char *name;
	enum playerType type;
	int smartness;
	int strength;
	int dexterity;
	int magic;
	int luck;
	int life;
	int posRow;
	int posCol;
};

void initBoard(struct slot **board);	// Set all pointers to adjacent slots for all slots
void generatePlayers(struct player players[], int playerCount);
void setElfValues(struct player *name);
void setHumanValues(struct player *name);
void setOgreValues(struct player *name);
void setWizardValues(struct player *name);
void printPlayers(struct player players[], int playerCount);
void printBoard(struct slot **board, struct player players[], int playerCount);

#endif /* OPERATIONS_H_ */
