//A set of functions to play the game

#include "mine_sweeper.h"

//Master function that calls all the playtime functions
void Play(MineSweeperBoard game){
    
    tile move; //placeholder tile containing only coordinates
    tile selected; //actual tile in the game that is selected
    int action = 0;
    
    do{
        do{
            DisplayBoard(game);
            move = AskPosition(game);
            selected = game.board[move.row][move.col];
            action = AskAction(game, selected);
        } while (action == CANCEL);
        ExecuteAction(&game, selected, action);
    }while(!IsGameOver(game));
    
    PrintEndGame(&game, IsGameOver(game));
    
}

//Returns the coordinates of the users selected tile
tile AskPosition(MineSweeperBoard game){
    
    tile move;
    
    do{
        printf("Enter row a row between 0-%d "
               "and a column between 0-%d: ",
               game.numRows - 1, game.numCols - 1);
        scanf("%d %d", &move.row, &move.col);
    }while(!(IsMoveValid(game, move) && IsValidFormat()));
    
    return move;
}

//Determines if user move is valid
bool IsMoveValid(MineSweeperBoard game, tile move){
    
    //not valid if out of bounds or already revealed
    if(IsOutOfBounds(game, move.row, move.col)) return false;
    if(game.board[move.row][move.col].state == REVEALED){
        printf("This tile is already revealed\n");
        return false;
    }
    else return true;
}

//Determines if user formatting is valid
bool IsValidFormat(){
    
    char lastChar;
    
    do {
        scanf("%c", &lastChar);
        if(!isspace(lastChar)) return false;
    } while (lastChar != '\n'); //consume all remaining input
    
    return true;
}

//Gives user what the possible moves are given tile state
int AskAction(MineSweeperBoard game, tile move){
    
    int action = 0;
    printf("Enter Action\n");
    
    switch (game.board[move.row][move.col].state) {
        case HIDDEN:
            printf("0. Reveal\n1. Question\n2. Mark\n3. Cancel\n");
            action = ToDo(HIDDEN);
            break;
        case QUESTIONED:
            printf("0. UnQuestion\n1.Cancel\n");
            action = ToDo(QUESTIONED);
            break;
        case MARKED:
            printf("0. UnMark\n1. Cancel\n");
            action = ToDo(MARKED);
        case REVEALED:
            printf("There really shouldn't be a revealed tile here.\n");
    }
    return action;
}

//Returns action to interpret user input as
int ToDo(int state){
    
    int action;
    
    do {
        printf("Action: ");
        scanf(" %d", &action);
    } while (!IsValidAction(state, action));
    
    switch (state) {
        case HIDDEN:
            switch (action) {
                case 0: return REVEAL;
                case 1: return QUESTION;
                case 2: return MARK;
                case 3: return CANCEL;
            }
        case QUESTIONED:
            switch (action) {
                case 0: return UNQUESTION;
                case 1: return CANCEL;
            }
        case MARKED:
            switch (action) {
                case 0: return UNMARK;
                case 1: return CANCEL;
            }
    }
    return CANCEL; //if unexpected input, cancel
}

//Returns if user selection is valid given tile state and action
bool IsValidAction(int state, int action){
    
    if (action < 0) return false;
    
    switch (state) {
        case HIDDEN:
            if (action > 3) return false;
            break;
        default:
            if (action > 1) return false;
    }
    return true;
}

//Changes the board state to reflect user input
void ExecuteAction(MineSweeperBoard* game, tile move, int action){
    
    switch (action) {
        case REVEAL: Reveal(game, move); return;
        case QUESTION:
            game->board[move.row][move.col].state = QUESTIONED;
            return;
        case UNQUESTION:
            game->board[move.row][move.col].state = HIDDEN;
            return;
        case MARK:
            game->board[move.row][move.col].state = MARKED;
            return;
        case UNMARK:
            game->board[move.row][move.col].state = HIDDEN;
            return;
        case CANCEL:
            printf("there really shouldn't be a cancel move here");
            return;
    }
    return;
}

//Recursively reveals a tile & its mineless neighbors
void Reveal(MineSweeperBoard* game, tile move){
    
    int i; int j;
    tile revealTile; //placeholder tile containing a neighbor's coordinates
    
    game->board[move.row][move.col].state = REVEALED; //reveal self
    //if no mine neighbors, initiate recursive search
    if (game->board[move.row][move.col].numSurrounding == 0){
        for(i = -1; i < 2; ++i){
            for(j = -1; j < 2; ++j){
                if((!IsOutOfBounds(*game, move.row + i, move.col + j))
                   && game->board[move.row + i][move.col + j].state == HIDDEN){
                    revealTile.row = move.row + i;
                    revealTile.col = move.col + j;
                    Reveal(game, revealTile);
                }
            }
        }
    }
}
