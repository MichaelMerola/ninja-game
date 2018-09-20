/**
Michael Merola
Homework 1 : NINJA MAZE
Player.cpp

implements functions for Player class
*/

#include "Maze.h"
#include "Player.h"
#include <iostream>
#include <vector>

using namespace std;

Player :: Player(const string name, const bool human) {
    name_ = name;
    is_human_ = human;

    points_ = 0;
    
    pos_.row = 0;
    pos_.col = 0;
}

void Player :: ChangePoints(const int x) {
    points_ = points_ + x;
}

void Player :: SetPosition(Position pos) {
    pos_ = pos;
}