/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Jyro Jimenez
 * Purpose:  Mastermind Version 2: Get duplicates and count
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
    char choice, length;
    int size;
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
        cout << "Input Guess (Code length:" << size << "): ";
        for(int i = 0; i < size; i++) {
            cin >> play[i];
            //Validate input
            while(play[i] > '8' || play[i] < '1') {
                cout << play[i] << " is invalid! Try again: ";
                cin >> play[i];
            }
        }
        
       
        for(int i = 0; i < 8; i++) {
            cout << dupe[i] << endl;
        }
        
        
        cout << endl << endl;
        cout << "Hints (0 = Correct Spot, x = Incorrect Spot, - = Not part of code)..." << endl;
        cout << "Hint: X00X--XX" << endl;
        
        
        cout << endl << "Pattern:" << endl;
        for(int i = 0; i < size; i++) {
            cout << pat[i];
        }
        cout << endl << "Copy:" << endl;
        for(int i = 0; i < size; i++) {
            cout << list[i];
        }
        cout << endl << "Player:" << endl;
        for(int i = 0; i < size; i++) {
            cout << play[i];
        }
        //end game
        game = false;
    }  
    //Exit
    return 0;
}