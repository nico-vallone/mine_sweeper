//Declarations for all the functions and types
//necessary for mine_sweeper

#ifndef mine_sweeper_h
#define mine_sweeper_h

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

enum DisplayState {HIDDEN, QUESTIONED, MARKED, REVEALED};

typedef struct Tile_Struct{
    int row;
    int col;
    enum DisplayState state;
    bool isMine;
    int numSurrounding;
} tile;

typedef struct MineSweeperBoard_Struct{
    tile** board;
    int numRows;
    int numCols;
    int numMines;
} MineSweeperBoard;

int SetSeed(int numArguments, char argv[]);

tile** AllocateBoard(int numRows, int numCols);

void SetupGame(MineSweeperBoard* game);

int CountNumSurrounding(MineSweeperBoard game, int row, int col);

bool IsOutOfBounds(MineSweeperBoard game, int row, int col);

void LayMines(MineSweeperBoard* game);

void DisplayBoard(MineSweeperBoard game);

void PrintState(tile tile);

#endif /* mine_sweeper_h */
