//A set of functions to print the board of the game

#include "mine_sweeper.h"

//Prints mines left, then cycles through each cell
void DisplayBoard(MineSweeperBoard game){
    
    int i = 0; int j = 0;
    
    printf("There are %d mines left\n",
           game.numMines - CountMarked(game));
    
    for(i = game.numRows - 1; i >= 0; --i){ //for every row
        printf("%d ", i); //print the row number
        for(j = 0; j < game.numCols; ++j){ //for every cell
            PrintState(game.board[i][j]); //print its state
        } printf("\n"); //end row with newline
    } printf("  "); //begin final row with two spaces
    for(i = 0; i < game.numCols; ++i){ //for every col
        printf("%d ", i); //print the col number
    } printf("\n");
}

//Prints a cell's visible state
void PrintState(tile tile){
    
    //char array of state symbols
    char symbols[4] = {'#', '?', '!', '*'};
    
    //if revealed, print number surrounding or if mine print mine
    if(tile.state == REVEALED)
        if(tile.isMine) printf("%c ", symbols[3]);
        else printf("%d ", tile.numSurrounding);
    
    //otherwise, print state
    else printf("%c ", symbols[tile.state]);
}

//Counts the number of marked tiles
int CountMarked(MineSweeperBoard game){
    
    int i = 0; int j = 0; int count = 0;
    
    for(i = game.numRows - 1; i >= 0; --i){ //for every row
        for(j = 0; j < game.numCols; ++j){ //for every cell
            if (game.board[i][j].state == MARKED) ++count;
        }
    }
    return count;
}
