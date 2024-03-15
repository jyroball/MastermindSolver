/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Jyro Jimenez
 * Purpose:  Mastermind Version 4: Ending Game
 */

//System Level Libraries
#include <iostream>  //Input-Output Library
#include <cstdlib>   //Random Function Library
#include <ctime>     //Time Library
using namespace std;

//User Defined Libraries

//Global Constants, not Global Variables
//These are recognized constants from the sciences
//Physics/Chemistry/Engineering and Conversions between
//systems of units!

//Function Prototypes

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare basic variables
    bool game = true;
    bool duplicate = false;
    bool same = false;
    bool special = false;
    char choice, length;
    int size, hint, moves;
    //Initialize some values
    size = 0;
    hint = 0;
    moves = 0;
    //Introduce game
    cout << "This is a program simulating the board game mastermind..." << endl << endl;
    //Display rules
    cout << "The rules of the game is as follows..." << endl;
    cout << "The computer will generate a code with the numbers 1-8, it is your job to " << endl
         << "figure out what the string of code is by guessing each individual number." << endl << endl;
    //Ask if they want to have duplicates
    cout << "Would you like to play with duplicates on? (y/n): ";
    cin >> choice;
    //Input validation
    while(choice != 'y' && choice != 'n') {
        cout << choice << " is invalid! Try again: ";
        cin >> choice;
    }
    //Change variable depending on choice
    if(choice == 'y') {
        duplicate = true;
    }
    //Ask if they how much pegs they want
    cout << endl <<  "What code length do you want? (4/6/8): ";
    cin >> length;
    //Validate
    while(length != '4' && length != '6' && length != '8') {
        cout << length << " is invalid! Try again: ";
        cin >> length;
    }
    //Set size equal to length
    size = length - '0';
    //Declare array variables
    char pat[size];
    char play[size];
    char list[size];
    //Declare counters for duplicates
    int count[8];
    int dupe[8];
    //Initialize both arrays
    for(int i = 0; i < 8; i++) {
        count[i] = 0;
        dupe[i] = 0;
    }
    //Initialize char arrays
    for(int i = 0; i < size; i++) {
        pat[i] = '0';
        play[i] = '0';
        list[i] = '0';
    }
    //Initialize pattern depending on duplicates or not
    for(int i = 0; i < size; i++) {
        if(duplicate) {
            //Create random number from 1-8, and make it a char
            pat[i] = (rand()% 8 + 1) + '0';
            //Add to count
            dupe[(pat[i] - '0') - 1] += 1;
        }
        else if(!duplicate){
            //set bool equal to true
            same = true;
            //Create random number from 1-8, and make it a char
            pat[i] = (rand()% 8 + 1) + '0';
            //set list equal to patern
            list[i] = pat[i];
            //loop to make sure pat[i] not equal to anything in list
            while(same) {
                //Loop to search for any duplicate
                for(int j = 0; j < i; j++) {
                    if(pat[i] == list[j]) {
                        same = false;
                    }
                }
                //If sattement to end or re roll pat
                if(same) {
                    same = false;
                }
                else {
                    same = true;
                    pat[i] =  (rand()% 8 + 1) + '0';
                    list[i] = pat[i];
                }
            }
            //Add counter for duplicates in each cell
            dupe[(pat[i] - '0') - 1] += 1;
        }
    }
    //Make loop for game
    while(game) {
        //Initialize to zero again
        for(int i = 0; i < 8; i++) {
            count[i] = 0;
        }
        hint = 0;
        
        //Ask for the player's guess
        cout << "Input Guess (Code length:" << size << "): ";
        //Loop to input each number in
        for(int i = 0; i < size; i++) {
            cin >> play[i];
            //Validate input
            while(play[i] > '8' || play[i] < '1') {
                cout << play[i] << " is invalid! Try again: ";
                cin >> play[i];
            }
        }
        //Loop to count the numbers used
        for(int i = 0; i < size; i++) {
            //Add to count array
            count[(play[i] - '0') - 1] += 1;
        }
        //Cout the hints to be given
        cout << endl;
        cout << "Hints (0 = Correct Spot, x = Incorrect Spot, - = Not part of code)..." << endl;
        cout << "Hint: ";
        //Loop to see if they got any in the right location
        for(int i = 0; i < size; i++) {
            //If statement to see if it is in the right location
            if(play[i] == pat[i]) {
                //Output the correct symbol
                cout << "0";
                //Loop to search for any duplicate
                for(int j = 0; j < size; j++) {
                    //If statement to see if there's a duplicate anywhere in the system
                    if(play[i] == pat[j]) {
                        //Bool to see if there is one
                        same = true;
                    }
                }
                //If satatements for each case
                //Not same so just change count back to 0 as to not out put unecessary hints
                if(!same) {
                    count[(play[i] - '0') - 1] = 0;
                }
                //If statements for when duplicates are 2 and subtract depending on how many guesses of same value
                else if(same && dupe[(play[i] - '0') - 1] >= 2 && count[(play[i] - '0') - 1] == 2) {
                    count[(play[i] - '0') - 1] -= 1;
                }
                else if(same && dupe[(play[i] - '0') - 1] >= 2 && count[(play[i] - '0') - 1] == 3) {
                    count[(play[i] - '0') - 1] -= 2;
                }
                else if(same && dupe[(play[i] - '0') - 1] >= 2 && count[(play[i] - '0') - 1] == 4) {
                    count[(play[i] - '0') - 1] -= 3;
                }
                else if(same && dupe[(play[i] - '0') - 1] >= 2 && count[(play[i] - '0') - 1] == 5) {
                    count[(play[i] - '0') - 1] -= 4;
                }
                else if(same && dupe[(play[i] - '0') - 1] >= 2 && count[(play[i] - '0') - 1] == 6) {
                    count[(play[i] - '0') - 1] -= 5;
                }
                else if(same && dupe[(play[i] - '0') - 1] >= 2 && count[(play[i] - '0') - 1] == 7) {
                    count[(play[i] - '0') - 1] -= 6;
                }
                else if(same && dupe[(play[i] - '0') - 1] >= 2 && count[(play[i] - '0') - 1] == 8) {
                    count[(play[i] - '0') - 1] -= 7;
                }
                //If statement for 1 value
                else if(same && dupe[(play[i] - '0') - 1] <= 1 && count[(play[i] - '0') - 1] == 1) {
                    count[(play[i] - '0') - 1] = 0;
                }
                //Just in case I missed a case
                else {
                    count[(play[i] - '0') - 1] = 0;
                }
                //Re-initialize boolean
                same = false;
                //Increment hints
                hint++;
            }
        }
        //Loop to output hints whether they got it or not.
        for(int i = 0; i < 8; i++) {
            //First check to see if a guess is right
            if(count[i] > 0 && dupe[i] > 0) {
                //Second check to see location of number
                //Loop to output one's that are in code but not in correct spot depending on guess and total ammount
                for(int j = 0; j < count[i] && j < dupe[i]; j++) {
                    //Output Incorrect spot symbol
                    cout << "X";
                    //Increment Hint
                    hint++;
                }
            }
        }
        //Loop to show that some not part of code
        for(int i = hint; i < size; i++) {
            //Output symbol
            cout << "-";
        }
        //Loop to end game
        game = false;
        for(int i = 0; i < size; i++) {
            if(play[i] != pat[i]) {
                game = true;
            }
        }
        //Output player input
        cout << endl <<  "Code: ";
        for(int i = 0; i < size; i++) {
            cout << play[i];
        }
        //Increment number of moves
        moves++;
        cout << endl << endl;
    }  
    cout << "Congratulations! You have solved the code!" << endl
         << "You solved it with " << moves << " guesses!" << endl;
    //Exit
    return 0;
}