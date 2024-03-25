/**********************************************************************
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/**********************************************************************
***********************************************************************/

// Constants identifying the strategy that the opponent plays
#define ALWAYS_COOPERATE        1	// Strategy "always cooperate"
#define MOSTLY_CHEAT            2	// Strategy "mostly cheat"
#define JOKER                   3	// Strategy "joker", aka "random"
#define COPYCAT                 4	// Strategy "copycat"
#define GRUDGER                 5	// Strategy "grudger"
#define COPYKITTEN              6	// Strategy "copykitten"

// Constant specifying the probability for the joker strategy to cooperate
#define PROBABILITY             0.5



/**********************************************************************
 * Predefined functions: Call these functions in your code to get user
 *                       input and report information to the user.
 *                       Do not modify these functions.
***********************************************************************/

// Asks the user what strategy the computer player should use
void get_strategy(int* strategy) {
        printf("\n");
        printf(" %d:ALWAYS_COOPERATE,",ALWAYS_COOPERATE);
        printf(" %d:MOSTLY_CHEAT, %d:JOKER,",MOSTLY_CHEAT,JOKER);
        printf(" %d:COPYCAT, %d:GRUDGER,",COPYCAT,GRUDGER);
        printf(" %d:COPYKITTEN\n",COPYKITTEN);
        printf(" Enter the strategy the computer should use: ");
        scanf("%d", strategy);
}

// Asks the user how many rounds to play
void get_rounds(int *num_rounds) {
        printf("\n");
        printf(" Enter how many rounds you want to play:   ");
        scanf("%d", num_rounds);
        printf("\n");
}

// Asks the user whether the player cooperates or not
// The result is passed back by the pointer 'move'
void get_player_move(int *move) {
        printf(" Does the player cooperate (1) or not (0): ");
        scanf("%d", move);
}

// Prints the moves both players are making
void print_moves(int move_player1, int move_player2) {
        printf(" Player 1 played %d", move_player1);
        printf(" and player 2 played %d \n", move_player2);
        printf("\n");
}

// Prints the final score for the two players
void print_scores(int score_player1, int score_player2) {
        printf(" Player 1 score:  %d\n", score_player1);
        printf(" Player 2 score:  %d\n", score_player2);
        printf("\n");
}



/**********************************************************************
 * These two functions decide on the move that the computer player makes,
 * based on the strategy it is employing. You need to implement these
 * functions and then also call them as part of the game of trust.
 *
 *	strategy:                The strategy used by the computer to
 *                               decide the move. This corresponds to
 *                               the strategy constants defined earlier.
 *	current_round:           The current round. We count rounds
 *                               starting from 0 (for the first round).
 *	opponent_previous_move:  The move made by the other player in
 *                               the PREVIOUS round (1 for cooperate
 *                               or 0 for cheat). Note that this is a
 *                               parameter in the second function only.
 *	move:                    Pointer where the function will
 *                               store the chosen move. This chosen
 *                               move is either 1 (for cooperate)
 *                               or 0 (for cheat).
***********************************************************************
* This function supports the strategies "always cooperate", "mostly cheat"
* and "joker".
***********************************************************************/
void get_computer_move(int strategy, int current_round, int *move) {
        if (strategy == ALWAYS_COOPERATE) {
                *move = 1;
        } else if (strategy == MOSTLY_CHEAT) {
                if (current_round == 0){
                        *move = 1;
                }else{
                      	*move = 0;
                }
        } else if (strategy == JOKER){
                if((rand() / (double)RAND_MAX) < PROBABILITY){
                        *move = 1;
                }else {
                       	*move = 0;
                }
        } else {
                *move = 0;
        }

}

/**********************************************************************
* This function supports the strategies "copycat", "grudger"
* and "copykitten" (optional).
***********************************************************************/
void get_computer_move2(int strategy, int current_round, int opponent_previous_move, int *move)  {
        static int consec_cheat = 0;
        if(current_round == 0) {

                *move = 1;
                return;
        }
	if(strategy == COPYCAT){
                *move =  opponent_previous_move;
        } else if (strategy == GRUDGER){
                if (opponent_previous_move == 0){
                *move = 0;
                }else {
                *move = 1;
                }
        }else if (strategy == COPYKITTEN){
                if (current_round == 0){
                        *move = 1;
                        consec_cheat = 0;
                } else {
                        if(opponent_previous_move == 0){
                        consec_cheat++;
                                if(consec_cheat >= 2){
                                        *move = 0;
                                } else{
                                       	*move = 1;
                                }
                        }else{
                              	*move = 1;
                                consec_cheat = 0;
                        }
                }
        }else {
               	if(current_round == 0){
                        *move = 1;
                }else {
                       	*move = 0;
                }
        }
}


/**********************************************************************
 * 
 * Main functionality: Write your code for implementing the game of
 *                     trust below.
 *                     You should seed the random number generator
 *                     with a random value based on the current time.
***********************************************************************/

int main(){

	int num_rounds, strategy;
        int move_player1, move_player2;
        int score_player1 = 0, score_player2 = 0;
        int previous_move_player1 = 0, previous_move_player2 = 1;
        int i = 0;

        srand((unsigned int)time(NULL));
        get_strategy(&strategy);
        get_rounds(&num_rounds);

        for(i = 0 ; i < num_rounds; ++i){


                get_player_move(&move_player1);
                if(strategy<= 3){
                get_computer_move(strategy, i, &move_player2);
                }else{
                      	get_computer_move2(strategy, i, previous_move_player1, &move_player2);
                }
        print_moves(move_player1, move_player2);

                if (move_player1 == 1 && move_player2 == 1){
                        score_player1 += 2;
                        score_player2 += 2;

                }else if ( move_player1 == 0 && move_player2 == 1){
                        score_player1 += 3;
                        score_player2 -= 1;
                }else if (move_player1 == 1  && move_player2 == 0){
                        score_player2 += 3;
                        score_player1 -= 1;
                }else if (move_player1 == 0 && move_player2 == 0){
                        score_player2 += 0;
                        score_player1 += 0;
                }

        previous_move_player1 = move_player1;
        previous_move_player2 = move_player2;
        }

	print_scores(score_player1, score_player2);


        return 0;
}




