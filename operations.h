/*	operations.h contains the definitions of slot and player structures and prototypes of functions
	for the creation of the board and the players, as well as printing both to the screen.  */

#ifndef OPERATIONS_H_
#define OPERATIONS_H_
#define BOARD_SIZE 7

/*	Enumeration used to represent slot type  */
enum slotType{GROUND, HILL, CITY};

/*	Structure to store the parameters of each slot, as well as pointers to adjacent slots  */
struct slot{
	int row;
	int column;
	struct slot *left;
	struct slot *right;
	struct slot *up;
	struct slot *down;
	enum slotType type;
}slot;

/*	Enumeration used to represent player type  */
enum playerType{HUMAN, ELF, WIZARD, OGRE};

/*	Structure to store all parameters of each player  */
struct player{;
	char *name;
	enum playerType type;
	int smartness;
	int strength;
	int dexterity;
	int magic;
	int luck;
	int life;
	struct slot *position;
};

/*	Prototypes of functions used to initialise the game and show its current state  */
void initBoard(struct slot **board);	// Set all pointers to adjacent slots for all slots
void generatePlayers(struct slot **board, struct player players[], int playerCount);	// Set all players' name, type and attributes
void setElfValues(struct player *name);		// Define rules for assigning attributes to elves
void setHumanValues(struct player *name);	// Define rules for assigning attributes to humans
void setOgreValues(struct player *name);	// Define rules for assigning attributes to ogres
void setWizardValues(struct player *name);	// Define rules for assigning attributes to wizards
void printPlayers(struct player players[], int playerCount);	// Print a list of all players remaining in the game
void printBoard(struct slot **board, struct player players[], int playerCount);	// Print the board in its current state

#endif /* OPERATIONS_H_ */
