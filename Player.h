/**
Michael Merola
Homework 1 : NINJA MAZE
Player.h

header file for Player Class
	handles functions that manipulate the player attributes
*/


#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <string>
using namespace std;


struct Position {
	int row;
	int col;

	// already implemented for you!
	bool operator==(const Position &other) {
		return row == other.row && col == other.col;
	}
};


class Player {
public:
//✅	// TODO: implement
	Player(const string name, const bool human);  // constructor
	
//✅	// These are already impleented for you
	string get_name() const {return name_; }  // inline member function
	int get_points() const {return points_; }  // inline member function
	Position get_position() const {return pos_; }  // inline member function
	bool isHuman() const {return is_human_; }  // inline member function

//	// TODO: implement the following functions
//✅	// You MUST implement the following functions
	void ChangePoints(const int x);  

//
//✅	// set a new position for this player
	void SetPosition(Position pos);

//
//	// You may want to implement these functions as well
//	// ToRelativePosition is a function we used to translate positions
//	// into directions relative to the player (up, down, etc)
	string ToRelativePosition(Position other);

//
//	// Convert this player to a string representation of their name and points
	string Stringify();

//
//	// You may add other functions as needed/wanted

private:
	string name_;
	int points_;
	Position pos_;
	bool is_human_;

	// You may add other fields as needed

}; // class Player

#endif  // _PLAYER_H_
