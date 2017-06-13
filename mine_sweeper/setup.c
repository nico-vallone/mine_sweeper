//A set of functions to set up the game and begin, includes main

#include "mine_sweeper.h"

int main(int argc, char* argv[]) {
    
    ValidateArguments(argc);
    
    MineSweeperBoard game;
    
    game.numRows = atoi(argv[1]);
    game.numCols = atoi(argv[2]);
    game.numMines = atoi(argv[3]);
    
    srand(SetSeed(argc, *argv));
    
    game.board = AllocateBoard(game.numRows, game.numCols);
    
    SetupGame(&game);
    
    Play(game);
    
    return 0;
}

void ValidateArguments(int argc){
    
    if (argc < 4){
        printf("Not enough arguments. Usage:\n./mine_sweeper.out num_rows num_cols num_mines [seed])");
        exit(0);
    }
    if (argc > 5){
        printf("Too many arguments. Usage:\n./mine_sweeper.out num_rows num_cols num_mines [seed])");
        exit(0);
    }
}

int SetSeed(int numArguments, char argv[]){
    if (numArguments == 5) return atoi(&argv[4]);
    else return (int)time(0);
}

tile** AllocateBoard(int numRows, int numCols){
    
    //Allocate memory for board array of tiles
    tile** board = (tile**)malloc(numRows * sizeof(tile*));
    for(int i = 0; i < numRows; ++i){
        board[i] = (tile*)malloc(numCols * sizeof(tile));
    }
    return board;
}

void SetupGame(MineSweeperBoard* game){
    
    int i = 0; int j = 0;
    
    //Setup initial board values
    for(i = 0; i < (*game).numRows; ++i){
        for(j = 0; j < (*game).numCols; ++j){
            (*game).board[i][j].row = i;
            (*game).board[i][j].col = j;
            (*game).board[i][j].state = HIDDEN;
            (*game).board[i][j].isMine = false;
        }
    }
    
    LayMines(game);
    
    //Count number of surrouning mines per tile
    for (i = 0; i < game->numRows; ++i){
        for(j = 0; j < game->numCols; ++j){
            game->board[i][j].numSurrounding =
            CountNumSurrounding(*game, i, j);
        }
    }
}

void LayMines(MineSweeperBoard* game){
    
    int minesToLay = game->numMines;
    
    while (minesToLay > 0){
        int row = rand() % game->numRows;
        int col = rand() % game->numCols;
        if (game->board[row][col].isMine == false){
            game->board[row][col].isMine = true;
            printf("Placing mine at %d, %d\n", row, col);
            --minesToLay;
        }
    }
}

int CountNumSurrounding(MineSweeperBoard game, int row, int col){
    
    int i = 0; int j = 0;
    int numSurrounding = 0;
    
    //for the eight surrounding tiles, count number of mines
    for(i = -1; i < 2; ++i){
        for(j = -1; j < 2; ++j){
            if((!IsOutOfBounds(game, row + i, col + j)) &&
               (game.board[row + i][col + j].isMine == true)){
                ++numSurrounding;
            }
        }
    }
    return numSurrounding;
}

bool IsOutOfBounds(MineSweeperBoard game, int row, int col){
    if (row >= game.numRows || row < 0) return true;
    if (col >= game.numCols || col < 0) return true;
    return false;
}
