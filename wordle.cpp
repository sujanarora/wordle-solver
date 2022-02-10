//
//  wordle.cpp
//  wordle-solver
//
//  Created by Sujan Arora on 2/10/22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "xcode_redirect.hpp"

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */

using namespace std;

struct WordWeight{
    std::string word;
    long double freq;
}; // WordWeight

struct Wordle{
    vector<WordWeight> v;
    string currWord;
    string currColor;
    size_t turnCounter = 1;
    
    void getGuesses();
    void eliminateData();
    void printGuesses();
}; // Wordle

void Wordle::printGuesses(){
    
}

void Wordle::getGuesses(){
    if (turnCounter == 1){
        cout << "Make an initial guess. Suggestions:\n"
        << "1. raine\n2. arose\n3. arioel\n4. orate\n5. irate\n6. arise\n7. soare\n8. raile\n9. raise\n10. roate\n .\n .\n .\n"
        <<"Type guess (ex. 'soare'):\n";
        /*source: https://artofproblemsolving.com/news/articles/the-math-of-winning-wordle*/
    }
    else{
        cout << "Turn " << turnCounter << "Best words:\n";
    }
    

    cout << "> ";
    cin >> currWord;
    
    cout << "\nGuess 1: " << currWord << ". Type position information\n"
    << BOLDGREEN << "g"<< RESET << " = green, "<< BOLDYELLOW << "y" << RESET << " = yellow, x = gray "<<
    "(ex. x"<< BOLDGREEN << "g" << BOLDYELLOW << "yy" << RESET << "x)\n";
    
    cout << "> ";
    cin >> currColor;
    ++turnCounter;
} // getGuesses()


int main(/*int argc, const char ** argv*/){
//    std::ios_base::sync_with_stdio(false);
//    xcode_redirect(argc, argv);
    
    Wordle w;
    
    // Read in to data vector
    ifstream file;
    file.open("words.txt");
    if (!file.is_open()){
        cerr << "error opening file 'words.txt'\n";
        exit(1);
    } // if
    w.v.resize(12972);
    std::string s;
    long double f;
    size_t counter = 0;
    while (file >> s >> f){
        w.v[counter].word = s;
        w.v[counter].freq = f;
        ++counter;
    } // while
    

    // Algorithm
    while (w.turnCounter <= 6){
        w.getGuesses();
        
        
    } // while
    
    
    
    return 0;
} // main()
