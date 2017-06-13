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

enum Action {CANCEL, REVEAL, QUESTION, UNQUESTION, MARK, UNMARK};

enum WinState {LOSE = -1, NOTOVER, WIN};

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

void ValidateArguments(int argc);

int SetSeed(int numArguments, char argv[]);

tile** AllocateBoard(int numRows, int numCols);

void SetupGame(MineSweeperBoard* game);

int CountNumSurrounding(MineSweeperBoard game, int row, int col);

bool IsOutOfBounds(MineSweeperBoard game, int row, int col);

void LayMines(MineSweeperBoard* game);

void DisplayBoard(MineSweeperBoard game);

int CountMarked(MineSweeperBoard game);

void PrintState(tile tile);

void Play(MineSweeperBoard game);

tile AskPosition(MineSweeperBoard game);

bool IsMoveValid(MineSweeperBoard game, tile move);

bool IsValidInput(MineSweeperBoard game, tile move);

bool IsValidFormat();

int IsGameOver(MineSweeperBoard game);

void PrintEndGame(MineSweeperBoard* game, int winState);

void RevealAll(MineSweeperBoard* game);

int AskAction(MineSweeperBoard game, tile move);

int ToDo(int state);

bool IsValidAction(int state, int action);

void ExecuteAction(MineSweeperBoard* game, tile move, int action);

void Reveal(MineSweeperBoard* game, tile move);

#endif /* mine_sweeper_h */
