/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:     main.cpp
 * Author:   Jyro Jimenez
 * Purpose:  Mastermind Project 2: AI
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

//Function Prototypes
string AI(char,char);
bool eval(string,string,char &,char &);
string set();

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare variables
    string code,guess;  //code to break, and current guess
    char rr,rw;         //right digit in right place vs. wrong place
    int nGuess;         //number of guesses
    
    //Initialize Values
    nGuess=0;
    code=set();
    rr=rw=0;

    //Loop until solved and count to find solution
    do{
       nGuess++;
       guess=AI(rr,rw);
    }while(eval(code,guess,rr,rw));
    
    //Output the solution
    cout<<"Number of guesses using Linear Search = "<<nGuess<<endl;
    cout<<code<<"="<<guess<<endl;

    //Exit the program
    return 0;
}

string AI(char rr, char rw){
    //Initialize some values
    static int guess = 0;                //Increment the guess number
    static string correctGuess = "XXXX"; //Initialize correct guess
    string aGuess = "XXXX";              //Guess correct spot
    string sGuess = "0000";              //Size the guess string
    //Declare and store correct numbers
    static int correctNum[4];
    //initialize indexes
    static int indx = 0;        //Index for correct
    static int tempIndx = 0;    //Index for finding correct spot
    //Initialize number of correct
    static int numCor = 0;
    //Find numbers from 0-9
    if(guess <= 10 && numCor != 4) {
        //Set numbers
        sGuess[0] = guess + '0';
        sGuess[1] = guess + '0';
        sGuess[2] = guess + '0';
        sGuess[3] = guess + '0';
        //Check rr to see old guess
        if(rr != 0) {
            //Add num correct till 4
            numCor += rr;
            //Add correct number to correct numbers array
            for(int i = 0; i < rr; i++) {
                correctNum[indx] = guess - 1;
                indx++;
            }
            //Reset indx once numCor == 4;
            if(numCor == 4) {
                indx = 0;
                aGuess[indx] = correctNum[tempIndx] + '0';
                sGuess = aGuess;
            }
        }
    }
    //If all numbers are found try to guess correct locations
    else {
        //Find First position
        if(indx == 0) {
            //If not in right spot
            if(rr == 0) {
                //Increment
                tempIndx++;
                //Place in proper spot to check
                aGuess[indx] = correctNum[tempIndx] + '0';
                //Set equal to s guess to evaluate
                sGuess = aGuess;
            }
            //If correct spot is found put in proper spot
            else {
                //Set correct guess
                correctGuess[indx] = correctNum[tempIndx] + '0';
                //Change value of correct num to stop checking it
                correctNum[tempIndx] = 100;
                //Restart tempIndx
                tempIndx = 0;
                //Increment indx
                indx++;
                //Check if tempIndx is not 100, if so skip
                if(correctNum[tempIndx] == 100) {
                    tempIndx++;
                }
                //Place in proper spot to check
                aGuess[indx] = correctNum[tempIndx] + '0';
                //Set equal to s guess to evaluate
                sGuess = aGuess;
            }
        }
        //Find second position
        else if(indx == 1) {
            //If not in right spot
            if(rr == 0) {
                //Increment
                tempIndx++;
                //Check if tempIndx is not 100, if so skip
                while(correctNum[tempIndx] == 100) {
                    tempIndx++;
                }
                //Place in proper spot to check
                aGuess[indx] = correctNum[tempIndx] + '0';
                //Set equal to s guess to evaluate
                sGuess = aGuess;
            }
            //If correct spot is found put in proper spot
            else {
                //Set correct guess
                correctGuess[indx] = correctNum[tempIndx] + '0';
                //Change value of correct num to stop checking it
                correctNum[tempIndx] = 100;
                //Restart tempIndx
                tempIndx = 0;
                //Increment indx
                indx++;
                //Check if tempIndx is not 100, if so skip
                while(correctNum[tempIndx] == 100) {
                    tempIndx++;
                }
                //Place in proper spot to check
                aGuess[indx] = correctNum[tempIndx] + '0';
                //Set equal to s guess to evaluate
                sGuess = aGuess;
            }
        }
        //Find Third position
        else if(indx == 2) {
            //If not in right spot
            if(rr == 0) {
                //Increment
                tempIndx++;
                //Check if tempIndx is not 100, if so skip
                while(correctNum[tempIndx] == 100) {
                    tempIndx++;
                }
                //Place in proper spot to check
                aGuess[indx] = correctNum[tempIndx] + '0';
                //Set equal to s guess to evaluate
                sGuess = aGuess;
            }
            //If correct spot is found put in proper spot
            else {
                //Set correct guess
                correctGuess[indx] = correctNum[tempIndx] + '0';
                //Change value of correct num to stop checking it
                correctNum[tempIndx] = 100;
                //Restart tempIndx
                tempIndx = 0;
                //Increment indx
                indx++;
                //Check if tempIndx is not 100, if so skip
                while(correctNum[tempIndx] == 100) {
                    tempIndx++;
                }
                //Place in proper spot to check
                aGuess[indx] = correctNum[tempIndx] + '0';
                //Set equal to s guess to evaluate
                sGuess = aGuess;
            }
        }
        //Place last number
        if(indx == 3) {
            correctGuess[indx] = correctNum[tempIndx] + '0';
            sGuess = correctGuess;
        }
    }
    //Increment guess
    guess++;
    //Return the result
    return sGuess;
}

bool eval(string code,string guess,char &rr,char &rw){
    string check="    ";
    rr=0,rw=0;
    //Check how many are right place
    for(int i=0;i<code.length();i++){
        if(code[i]==guess[i]){
            rr++;
            check[i]='x';
            guess[i]='x';
        }
    }
    //Check how many are wrong place
    for(int j=0;j<code.length();j++){
        for(int i=0;i<code.length();i++){
            if((i!=j)&&(code[i]==guess[j])&&(check[i]==' ')){
                rw++;
                check[i]='x';
                break;
            }
        }
    }
    
    //Found or not
    if(rr==4)return false;
    return true;
}

string set(){
    string code="0000";
    for(int i=0;i<code.length();i++){
        code[i]=rand()%10+'0';
    }
    return code;
}