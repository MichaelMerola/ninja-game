/**
Michael Merola
Homework 1 : NINJA MAZE
Maze.cpp

implements functions for Maze and Board classes
*/

#include "Maze.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <map>
#include <limits>

#include <cstdlib> 

using namespace std;

//
// BOARD IMPLEMENTATION
//

// CONSTRUCTOR
Board :: Board() {
    srand(time(NULL));
    Position pos;
    pos.row = 0;
    pos.col = 0;


    for (int x = 0; x < rows_; x++) {
        for (int y = 0; y < cols_; y++) {
            pos.row = x;
            pos.col = y;

            SetSquareValue (pos);
        }
    }
}

//prints the board
void Board :: PrintBoard() {

    cout << "-------------------------" << endl;

    for (int x = 0; x < rows_; x++) {
        for (int y = 0; y < cols_; y++) {

            switch (boardArray[x][y]) {
                case SquareType::Empty:
                    cout << " ⬛️ " ;
                    break;

                case SquareType::Wall:
                    cout << " 🀄️ " ;
                    break;

                case SquareType::Exit:
                    cout << " ⛩ " ;
                    break;

                case SquareType::Human:
                    cout << " 🥋 " ;
                    break;

                case SquareType::Enemy: 
                    cout << " 🐲 " ;
                    break;

                case SquareType::Fortune: // Treasure
                    cout << " 🥠  " ;
                    break;

                case SquareType::Sushi: // Treasure
                    cout << " 🍣 " ;
                    break;

                case SquareType::Tree:  // Powerup
                    cout << " 🎋 " ;    // Tanabata tree gives humans 250 points
                    break;              // kills dragoons if they touch it
            }
        }
        cout << endl; 
    }

    cout << "-------------------------" << endl;
}

//sets a specific square value
void Board :: SetSquareValue(Position pos, SquareType sq) {
    boardArray[pos.row][pos.col] = sq;
}

//helps to build the initial board at beginning of game
void Board :: SetSquareValue (Position pos) {
    int x = pos.row;
    int y = pos.col;

    // if at start position, set square to Human
    if (x == 0 && y == 0) {
        boardArray[x][y] = SquareType::Human;
    
    // if at end position, set square to Exit
    } else if (x == 5 && y == 5) {
        boardArray[x][y] = SquareType::Exit;
    
    // else, set square according to random
    } else { 
        //RANDOM IMPLEMENTATION
        int randNum = rand() % 100;

        if (randNum <= 22) {                            // 22% chance for Wall
            boardArray[x][y] = SquareType::Wall;
        } else if (randNum > 22 && randNum <= 30) {     // 8% chance for Sushi
            boardArray[x][y] = SquareType::Sushi;
        } else if (randNum > 30 && randNum <= 35) {     // 5% chance for Tree
            boardArray[x][y] = SquareType::Tree;
        } else if (randNum > 35 && randNum <= 37) {     // 2% chance for Fortune
            boardArray[x][y] = SquareType::Fortune;
        } else {
            boardArray[x][y] = SquareType::Empty;       // 43% chance for Empty
        }
    }
}

SquareType Board :: get_square_value(Position pos) {
    int x = pos.row;
    int y = pos.col;

    return boardArray[x][y];
}

map<string, Position> Board :: GetMoves(Player *p) {

    Position pos = p->get_position(); 
    move_string_ = "";
    map<string, Position> moves;

    //CHECK UP
    Position up = pos;
    up.row = up.row - 1;
    if (isValidPos(up)) {
        moves["up"] = up;
        move_string_ += " UP ";
    }

    //CHECK RIGHT
    cout << endl;
    Position right = pos;
    right.col = right.col + 1;
    if (isValidPos(right)) {
        moves["right"] = right;
        move_string_ += " RIGHT ";
    }   

    //CHECK DOWN
    Position down = pos;
    down.row = down.row + 1;
    if (isValidPos(down)) {
        moves["down"] = down;
        move_string_ += " DOWN ";
    }   

    //CHECK LEFT
    Position left = pos;
    left.col = left.col - 1;
    if (isValidPos(left)) {
        moves["left"] = left;
        move_string_ += " LEFT ";
    }   

    move_string_ += " GUARD ";

    return moves;
}//end GetMoves

string Board :: GetMoveString() {
    return move_string_;
}

void Board :: MovePlayer(Player *p, Position pos) {
    //set old position to empty
    Position start = p->get_position();
    SetSquareValue(start, SquareType::Empty);

    //set new position to the type of player
    p->SetPosition(pos);
    if (p->isHuman() == true) {
        SetSquareValue(pos, SquareType::Human);
    } else {
        SetSquareValue(pos, SquareType::Enemy);
    }
}//end MovePlayer

SquareType Board :: GetExitOccupant() {

    Position exit;
    exit.row = rows_-1;
    exit.col = cols_-1;

    return get_square_value(exit);
}

// Helper function to check if a position is valid
bool Board :: isValidPos(Position p) {

    // check if the pos is between the bounds of the board
    if ( (p.row >= 0 && p.row < rows_) && (p.col >= 0 && p.col < cols_) ) {

        //check if the pos is not a WALL
        if ( get_square_value(p) != SquareType::Wall) {
            return true;
        }
    }
    return false;
}


//
// MAZE IMPLEMENTATION
//

// CONSTRUCTOR
Maze :: Maze() {}

// starts a new game
void Maze :: NewGame(Player *human, const int enemies) {

    board_ = new Board();
    turn_count_ = 0;

    Position humanStart;
    humanStart.row = 0;
    humanStart.col = 0;
    human->SetPosition(humanStart);

    players_.push_back(human);

    Position exit;
    exit.row = board_->get_rows()-1;
    exit.col = board_->get_cols()-1;

    for (int i = 0; i < enemies; i++) {

        string enemyName = "dragoon" + to_string(i+1);
        Player *e = new Player(enemyName, false);

        Position enemyStart = exit;
        enemyStart.col -= (i+1);
        e->SetPosition(enemyStart);
        board_->SetSquareValue(enemyStart, SquareType::Enemy);

        players_.push_back(e);
    }


}//end NewGame

void Maze :: TakeTurn(Player *p) {

    cout << p->get_name() << "'s TURN !!" << endl;

    //its the Human player's turn
    if (p->isHuman() == true) { 

        board_->PrintBoard();

        string moveList = "";
        //print the players moves
        map<string, Position> moves = board_->GetMoves(p);

        cout << "moves: " << board_->GetMoveString() << endl;

        string choice;
        cin >> choice;
        cin.clear();
        cin.ignore();

        if (choice == "down" || choice == "up" || choice == "left" || choice == "right") {

            // interpret players move
            detectCollision(p, moves[choice], choice);

        } else {
            cout << "INVALID MOVE" << endl;
        }


    //its an ENEMY's turn
    } else { 

        string moving;
        Position init = p->get_position(); 
        Position enemyMove;
        bool isValid = false;

        while (isValid == false) { //loop until the generator chooses a valid position to move on
            enemyMove = init;

            //randomly chooses what direction the enemy moves
            srand(time(NULL));
            int randDir = rand() % 100;

            //
            // 40% chance that enemy moves UP/DOWN, LEFT/RIGHT, or  20% chance no move
            // 1/2 chance that enemy moves UP or DOWN, LEFT or RIGHT, depending on initial choice

            if (randDir <= 40) { // UP or DOWN

                srand(time(NULL));
                int randChoose = rand() % 100;
                if (randChoose < 50) {
                    //move UP
                    enemyMove.row -= 1;
                    moving = "UP";
                } else {
                    //move DOWN
                    enemyMove.row += 1;
                    moving = "DOWN";
                }         
            } else if (randDir > 40 && randDir <= 80) { // LEFT or RIGHT

                srand(time(NULL));
                int randChoose = rand() % 100;
                if (randChoose < 50) {
                    //move LEFT
                    enemyMove.col -= 1;
                    moving = "LEFT";
                } else {
                    //move RIGHT
                    enemyMove.col += 1;
                    moving = "RIGHT";
                }  
            } else { // NO MOVE
                moving = "NULL";
            }
            isValid = board_->isValidPos(enemyMove);

        }//end while

        detectCollision(p, enemyMove, moving);
    }

    turn_count_++;

}//end TakeTurn

void Maze :: detectCollision(Player* p, Position move, string choice) {

    SquareType sq = board_->get_square_value(move);

    // PLAYER
    if (p->isHuman() == true) { 
        switch (sq) {
            //player hits enemy...
            case SquareType::Enemy: 
                //player dies!
                board_->SetSquareValue(p->get_position(), SquareType::Empty); //destroys human
                system("clear");
                PrintHead();
                cout << "you moved " << choice << " !!" << endl; 
                board_->PrintBoard();
                cout << " !! 🐲🐲 🔥🔥🔥🔥🔥 🐲🐲 !! " << endl;
            break;

            case SquareType::Sushi:
                //player collects sushi!
                board_->MovePlayer(p, move);
                system("clear");
                PrintHead();
                cout << "you moved " << choice << " !!" << endl; 
                board_->PrintBoard();
                cout << " !! 🍣🍣 +100 🍣🍣 !! " << endl;
                p->ChangePoints(100);

                //wait for enter
                cout << endl;
                cout << "(press enter)";
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); //detects an enter keypress
                //this allows the player to pause and see the enemies move

            break;

            case SquareType::Fortune:
                //player collects sushi!
                board_->MovePlayer(p, move);
                system("clear");
                PrintHead();
                cout << "you moved " << choice << " !!" << endl; 
                board_->PrintBoard();
                cout << " !! 🥠🥠 +500 🥠🥠 !! " << endl;
                p->ChangePoints(500);

                //wait for enter
                cout << endl;
                cout << "(press enter)";
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); //detects an enter keypress
                //this allows the player to pause and see the enemies move

            break;

            case SquareType::Exit:
                //you win
                board_->MovePlayer(p, move);
                system("clear");
                PrintHead();
                cout << "you moved " << choice << " !!" << endl; 
                board_->PrintBoard();

            break;

            case SquareType::Tree:
                //player gets 250 points
                board_->MovePlayer(p, move);
                system("clear");
                PrintHead();
                cout << "you moved " << choice << " !!" << endl; 
                board_->PrintBoard();
                cout << " !! 🎋🎋 +250 🎋🎋 !! " << endl;
                p->ChangePoints(250);

                //wait for enter
                cout << endl;
                cout << "(press enter)";
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); //detects an enter keypress
                //this allows the player to pause and see the enemies move
            break;

            default:
                //player moves, nothing happens
                board_->MovePlayer(p, move);
                system("clear");
                PrintHead();
                cout << "you moved " << choice << " !!" << endl; 
                
                board_->PrintBoard();

                //wait for enter
                cout << endl;
                cout << "(press enter)";
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); //detects an enter keypress
                //this allows the player to pause and see the enemies move

            break;

        }
    // ENEMY
    } else {
        int e;
        switch (sq) {
            //enemy hits enemy...
            case SquareType::Enemy: 
                //moves canceled
                board_->PrintBoard();
                cout << p->get_name() << " is guarding.. " << endl;

                //wait for enter
                cout << endl;
                cout << "(press enter)";
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); //detects an enter keypress
                cout << endl;
                //this allows the player to pause and see the enemies move
            break;

            case SquareType::Exit: 
                //moves canceled
                board_->PrintBoard();
                cout << p->get_name() << " is guarding.. " << endl;

                //wait for enter
                cout << endl;
                cout << "(press enter)";
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); //detects an enter keypress
                cout << " !! 🀄️🀄️🀄️🀄️🀄️ !! " << endl;
                //this allows the player to pause and see the enemies move
            break;

            case SquareType::Human: 
                //player dies!

                board_->MovePlayer(p, move);
                board_->PrintBoard();
                cout << endl;
                cout << p->get_name() << " moved " << choice << " !! " << endl;
                cout << " !! 🐲 🔥🔥🔥 🥋 !! " << endl;
            break;

            case SquareType::Sushi:
                //enemy collects sushi!
                board_->MovePlayer(p, move);
                board_->PrintBoard();
                cout << p->get_name() << " moved " << choice << " !! " << endl;
                cout << " !! 🐲 stole a 🍣 !! " << endl;
                p->ChangePoints(100);

                //wait for enter
                cout << endl;
                cout << "(press enter)";
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); //detects an enter keypress
                cout << endl;
                //this allows the player to pause and see the enemies move

            break;

            case SquareType::Fortune:
                //enemy collects cookie!
                board_->MovePlayer(p, move);
                board_->PrintBoard();
                cout << p->get_name() << " moved " << choice << " !! " << endl;
                cout << " !! 🐲 stole a 🥠 !! " << endl;
                p->ChangePoints(500);

                //wait for enter
                cout << endl;
                cout << "(press enter)";
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); //detects an enter keypress
                cout << endl;
                //this allows the player to pause and see the enemies move

            break;

            case SquareType::Tree:
                //Dragoon dies!!
                board_->SetSquareValue(p->get_position(), SquareType::Empty); //destroys dragoon
                board_->PrintBoard();
                cout << p->get_name() << " moved " << choice << " !! " << endl;
                cout << " !! 🎋 🔥🔥🔥 🐲 !! " << endl;
                p->ChangePoints(-500);

                //remove dragoon from players vector
                e = turn_count_ % (players_.size());
                players_.erase(players_.begin() + e);

                //wait for enter
                cout << endl;
                cout << "(press enter)";
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); //detects an enter keypress
                cout << endl;
                //this allows the player to pause and see the enemies move
            break;

            default:
                board_->MovePlayer(p, move);
                board_->PrintBoard();
    
                if (choice == "NULL") {
                    cout << p->get_name() << " is guarding.. " << endl;
                } else {
                    cout << p->get_name() << " moved " << choice << " !! " << endl;
                }
                //wait for enter
                cout << endl;
                cout << "(press enter)";
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); //detects an enter keypress
                cout << endl;
                //this allows the player to pause and see the enemies move

            break;

        }
    }
}

// get the next player by modding the turns by the number of players
Player* Maze :: GetNextPlayer() {
    
    int numPlayers = players_.size();       //get number of players
    int turn = turn_count_ % numPlayers;    //get whose turn it is
        //ex.. if there are 3 players and its turn 7..
        //     7 % 3 = 1, so return the player at the 1 index of the vector

    Player* p = players_[turn];

    return p;
}

bool Maze :: isGameOver() {

    if (board_->GetExitOccupant() == SquareType::Human) { //human reached exit
        cout << endl;
        cout << " ⛩🥋                             🥋⛩ " << endl;
        cout << " ⛩🥋 !! YOU MADE SENSEI PROUD !! 🥋⛩ " << endl;
        cout << " ⛩🥋                             🥋⛩ " << endl;
        cout << endl;
        cout << " -------------------- " << endl;
        cout << " ---- SCOREBOARD ---- " << endl;
        cout << endl;
        
        //prints the points of each player
        for (auto p : players_) {
        
            if (p->isHuman()) {
                cout << "🥋 " << p->get_name() << " POINTS: " << p->get_points() << endl;
                cout << endl;
            } else {
                cout << "🐲 " << p->get_name() << " POINTS: " << p->get_points() << endl;
            }
        }
        cout << endl;
        return true;

    } else if (!CheckForHuman()) { //human was destroyed
        cout << endl;
        cout << " ⛩🔥                    🔥⛩ " << endl;
        cout << " ⛩🔥 YOU WERE DESTROYED 🔥⛩ " << endl;
        cout << " ⛩🔥                    🔥⛩ " << endl;
        cout << endl;
        cout << " -------------------- " << endl;
        cout << " ---- SCOREBOARD ---- " << endl;
        cout << endl;

        for (auto p : players_) {
        
            if (p->isHuman()) {
                cout << "🥋 " << p->get_name() << " POINTS: " << p->get_points() << endl;
                cout << endl;
            } else {
                cout << "🐲 " << p->get_name() << " POINTS: " << p->get_points() << endl;
            }
        }
        cout << endl;
        return true;

    } else {
        return false; //human still exists
    }

}

//check if there is a human player left on the board
bool Maze :: CheckForHuman() {

    Position temp;

    for (int x = 0; x < board_->get_rows(); x++) {
        for (int y = 0; y < board_->get_cols(); y++) {

            temp.row = x;
            temp.col = y;

            if (board_->get_square_value(temp) == SquareType::Human) {
                return true;
            }
        }
    }
    return false;
}

//print the header of the board
void Maze :: PrintHead() {

     cout << " ----- NINJA MAZE ----- " << endl;
    cout << " ---------    --------- " << endl;
    cout << " ---   忍者の迷路   --- " << endl;
    cout << endl;
    
    for (auto p : players_) {
        
        if (p->isHuman()) {
            cout << "🥋 " << p->get_name() << " POINTS: " << p->get_points() << endl;
            cout << endl;
        } else {
            cout << "🐲 " << p->get_name() << " POINTS: " << p->get_points() << endl;
        }
    }

    cout << endl;
}