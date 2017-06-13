//A series of functions for the end game

#include "mine_sweeper.h"

//Returns -1, 0, or 1, if lose, not over, or win respectively
int IsGameOver(MineSweeperBoard game){
    
    int i = 0; int j = 0;
    
    for(i = game.numRows - 1; i >= 0; --i){ //for every row
        for(j = 0; j < game.numCols; ++j){ //for every cell
            if(game.board[i][j].isMine && game.board[i][j].state == REVEALED) return LOSE; //if a mine is revealed you lost
            if(game.board[i][j].state == HIDDEN) return NOTOVER; //if any hidden tiles remain the game isn't over
        }
    }
    return WIN;
}

//Prints the final board state
void PrintEndGame(MineSweeperBoard* game, int winState){
    
    RevealAll(game);
    DisplayBoard(*game);
    if (winState == LOSE) printf("You lost :(\n");
    if (winState == WIN) printf("You Won!!\n");
}

//Sets every tile to revealed
void RevealAll(MineSweeperBoard* game){
    
    int i; int j;
    
    for(i = 0; i < game->numRows; ++i){ //for every row
        for(j = 0; j < game->numCols; ++j){ //every cell
            game->board[i][j].state = REVEALED; //is revealed
        }
    }
}
