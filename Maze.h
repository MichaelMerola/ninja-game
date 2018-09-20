/**
Michael Merola
Homework 1 : NINJA MAZE
Maze.h

header file for Maze and Board classes
	Board - handles functions that change game board
	Maze  - handles functions that manage the maze game
*/

#ifndef _MAZE_H_
#define _MAZE_H_

#include <vector>
#include <map>
#include "Player.h"

using namespace std;

// defines the types of squares on Board
enum class SquareType { Wall, Exit, Empty, Human, Enemy, Sushi, Tree, Fortune };

class Board {
public:
//✅	// CONSTRUCTOR
	Board();
	
//✅	// already implemented in line
	int get_rows() const {return rows_; }  // you should be able to change the size of your 
	int get_cols() const {return cols_; }  // board by changing these numbers and the numbers in the arr_ field

//✅  // Function to print board in terminal
	void PrintBoard();	


//✅	// return the value of a specific square
	SquareType get_square_value(Position pos); 		


//✅	// set the value of a square to the given SquareType
	void SetSquareValue(Position pos);
	void SetSquareValue(Position pos, SquareType sq);


//
//	// get the possible Positions that a Player could move to
//✅	// (not off the board or into a wall)
	map<string, Position> GetMoves(Player *p);
	string GetMoveString();

//
//	// Move a player to a new position on the board. Return
//✅	// true if they moved successfully, false otherwise.
	void MovePlayer(Player *p, Position pos);


//
//✅	// Check the squaretype that currently occupies the exit square
	SquareType GetExitOccupant();

//
//✅	// Helper function to determine if a given position is valid for a players move
	bool isValidPos(Position p);

private:
	int rows_ = 6;
	int cols_ = 6; 

	string move_string_;

	SquareType boardArray [6][6];
	
	// you may add more fields, as needed
};  // class Board



class Maze {
public:
//✅	// TODO: implement these functions
	Maze(); // constructor


//
//	// initialize a new game, given one human player and 
//✅	// a number of enemies to generate
	void NewGame(Player *human, const int enemies);


//
//✅	// have the given Player take their turn
	void TakeTurn(Player *p);
	void detectCollision(Player* p, Position move, string choice);

//
//✅	// Get the next player in turn order
	Player * GetNextPlayer();


//
//	// return true iff the human made it to the exit 
//✅	// or the enemies ate all the humans
	bool isGameOver();
	bool CheckForHuman();

//
//✅	// print game header
	void PrintHead();

private:
	Board *board_; 
	vector<Player *> players_;
	int turn_count_;
//
//
//
};  // class Maze

#endif  // _MAZE_H_
