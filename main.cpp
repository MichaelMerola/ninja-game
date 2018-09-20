/**
Michael Merola
Homework 1 : NINJA MAZE
main.cpp

a fun maze game, 1 player vs. 2 AI enemies
to run game:
    $ cd HW1-merola
    $ make all
    $ ./maze
*/

#include "Maze.h"
#include "Player.h"
#include <iostream>
#include <vector>

using namespace std;


int main() {
    system("clear"); //clear terminal screen

    cout << " ----- NINJA MAZE ----- " << endl;
    cout << " ---------    --------- " << endl;
    cout << " ---   忍者の迷路   --- " << endl;

    Maze game; 
    cout << endl;

    string name;
    cout << " Enter a name: " ;
    cin >> name;
    cin.clear();
    cin.ignore();

    cout << endl;
    cout << " ready up " << name << " !!" << endl;
    cout << endl;
    cout << endl;
    cout << " ---- INSTRUCTIONS ---- " << endl;
    cout << endl;
    cout << " avoid 🐲 !!" << endl;
    cout << endl;
    cout << " ---------    --------- " << endl;
    cout << endl;
    cout << " 🀄️ are walls !!" << endl;
    cout << endl;
    cout << " ---------    --------- " << endl;
    cout << endl;
    cout << " collect TREASURE !!" << endl;
    cout << "  🍣 +100 points  (🐲 love sushi!)" << endl;
    cout << "  🥠  +500 points  (🐲 love fortunes!)" << endl;
    cout << "  🎋 +250 points  (destroys 🐲!)" << endl;
    cout << endl;
    cout << " ---------    --------- " << endl;
    cout << endl;
    cout << " get to the ⛩ !!" << endl;
    cout << endl;
    cout << " ---------    --------- " << endl;
    cout << endl;
    cout << " !! 行く !! 行く !!" << endl;
    cout << endl;

    Player *p1 = new Player(name, true);
    Player *current;

    game.NewGame(p1, 2);

    //wait for enter
    cout << "(press enter)";
    cin.ignore(numeric_limits<streamsize>::max(),'\n'); //detects an enter keypress
    cout << endl;
    //this allows the player to pause and see the enemies move

    while (!game.isGameOver()) { //while gameover parameters are not true
        
        system("clear");
        game.PrintHead();
        current = game.GetNextPlayer();
        game.TakeTurn(current);
    }
    cout << " ---- GAME OVER ---- " << endl;
    cout << endl;
}