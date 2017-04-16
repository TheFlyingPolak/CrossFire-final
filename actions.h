/*	actions.h contains the prototypes of functions necessary to run the game  */

#ifndef ACTIONS_H_
#define DEFINE_H_

void runGame(struct slot **board, struct player players[], int playerCount);	//Control the running of the game and game logic
void move(struct slot **board, struct player *name);	// Accommodate player movement
void wait(void);	// Ask the user to press ENTER to continue

#endif  /*  OPERATIONS_H_  */