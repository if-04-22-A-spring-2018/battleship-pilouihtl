/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"


CellContent player_me[FIELDSIZE][FIELDSIZE];
CellContent player_op[FIELDSIZE][FIELDSIZE];
CellContent guesses[FIELDSIZE][FIELDSIZE];

void load_game(){
  FILE* fd_me = fopen("battleship.my", "r");
  FILE* fd_op = fopen("battleship.op", "r");
  for(int i = 0; i < FIELDSIZE; i++){
    for(int a = 0; a < FIELDSIZE; a++){
      fread(&player_op[a][i], 4, 1, fd_op);
      fread(&player_me[a][i], 4, 1, fd_me);
      guesses[a][i] = Unknown;
    }
  }
  fclose(fd_op);
  fclose(fd_me);
}

/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col){
  if(row < 0 || col < 0 || row == FIELDSIZE || col == FIELDSIZE){return OutOfRange;}
  return player_me[col][row];
}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The columnt where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/
bool shoot(int row, int col)
{
  if(get_shot(row, col) != OutOfRange){
    guesses[col][row] = player_op[col][row];
    for (int i = -1; i < 2; i++) {
      for (int a = -1; a < 2; a++) {
        if(get_my_guess(row+a, col+i) == Unknown){
          guesses[col+i][row+a] = Water;
        }
      }
    }
    return true;
  }
  return false;
}

/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col){
  if(row < 0 || col < 0 || row >= FIELDSIZE || col >= FIELDSIZE){return OutOfRange;}
  return guesses[col][row];
}
