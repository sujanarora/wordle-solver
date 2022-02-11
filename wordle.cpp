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
    vector<string> wordBank;
    string currWord;
    string currColor;
    size_t turnCounter = 1;
    
    void getGuesses();
    void eliminateData();
    void printGuesses();
}; // Wordle

void Wordle::printGuesses(){
    cout << "word  | language frequency\n---------------------------\n";
    for (unsigned i = 0; i < v.size(); ++i){
        cout << v[i].word << " | " << v[i].freq << "\n";
        if (i >= 20) break;
    }
}

void Wordle::eliminateData(){
    vector<char> allowRepeatLetters;
    for (unsigned i = 0; i < currColor.size(); ++i){
        if (currColor[i] == 'g'){
            allowRepeatLetters.push_back(currWord[i]);
        }
    }
    for (unsigned i = 0; i < currColor.size(); ++i){
        vector<WordWeight> wordslist;
        if (currColor[i] == 'g'){
            allowRepeatLetters.push_back(currWord[i]);
            for (unsigned j = 0; j < v.size(); ++j){
                if (v[j].word[i] == currWord[i]){
                    wordslist.push_back(v[j]);
                } // if word has green char at correct position
            } // for j: each word in v
        } // green
        else if (currColor[i] == 'y'){
            allowRepeatLetters.push_back(currWord[i]);
            for (unsigned j = 0; j < v.size(); ++j){
                char mightHave = currWord[i]; // right letter, wrong pos
                if (v[j].word[i] == mightHave){
                    continue; // word in the wrong spot
                } // if word has green char at correct position
                bool shouldPushBack = false;
                for (unsigned k = 0; k < currWord.size(); ++k){
                    if (v[j].word[k] == mightHave){
                        shouldPushBack = true;
                    }
                } // for k: chars in currWord
                if (shouldPushBack) wordslist.push_back(v[j]);
            } // for j: words in v
        } // yellow
        else if (currColor[i] == 'x'){
            bool letterInWord = false;
            for (unsigned l = 0; l < allowRepeatLetters.size(); ++l){
                if (currWord[i] == allowRepeatLetters[l]) letterInWord = true;
            }
            if (letterInWord) break;
            for (unsigned j = 0; j < v.size(); ++j){
                char doesntHave = currWord[i]; // right letter, wrong pos
                bool shouldPushBack = true;
                for (unsigned k = 0; k < currWord.size(); ++k){
                    if (v[j].word[k] == doesntHave){
                        shouldPushBack = false;
                    }
                } // for k: chars in currWord
                if (shouldPushBack) wordslist.push_back(v[j]);
            } // for j: words in v
        } // gray
        else{
            cout << "Error: invalid input";
            exit(1);
        }
        v = wordslist;
    } // for i: chars in currColor
    
} // eliminateData()

void Wordle::getGuesses(){
    if (turnCounter == 1){
        cout << "Make an initial guess. Suggestions:\n"
        << "1. raine\n2. arose\n3. ariel\n4. orate\n5. irate\n6. arise\n7. soare\n8. raile\n9. raise\n10. roate\n .\n .\n .\n"
        <<"Type guess (ex. 'irate'):\n> ";
        /*source: https://artofproblemsolving.com/news/articles/the-math-of-winning-wordle*/
    }
    else{
        cout << "Turn " << turnCounter << " - Best words:\n";
        printGuesses();
        cout << "Type 'exit' to exit\nType guess:\n> ";
    }
    

    
    cin >> currWord;
    
    if (currWord == "exit") exit(0);
    
    bool validWord = false;
    for (unsigned i = 0; i < wordBank.size(); ++i){
        if (currWord == wordBank[i]) validWord = true;
    }
    if (!validWord){
        cout << "Error: invalid input";
        exit(1);
    }
    
    cout << "\nGuess: " << currWord << ". Type position information\nType 'exit' to exit\n"
    << BOLDGREEN << "g"<< RESET << " = green, "<< BOLDYELLOW << "y" << RESET << " = yellow, x = gray "<<
    "(ex. x"<< BOLDGREEN << "g" << BOLDYELLOW << "yy" << RESET << "x)\n";
    
    cout << "> ";
    cin >> currColor;
    if (currColor == "exit") exit(0);
    
    eliminateData();
    
    ++turnCounter;
} // getGuesses()


int main(/*int argc, const char ** argv*/){
    Wordle w;
    
    // Read in to data vector
    ifstream file;
    file.open("words.txt");
    if (!file.is_open()){
        cerr << "error opening file 'words.txt'\n";
        exit(1);
    } // if
    w.v.resize(12972);
    w.wordBank.resize(12972);
    std::string s;
    long double f;
    unsigned counter = 0;
    
    while (file >> s >> f){
        w.v[counter].word = s;
        w.wordBank[counter] = s;
        w.v[counter].freq = f;
        ++counter;
    } // while
    

    // Algorithm
    while (w.turnCounter <= 6){
        w.getGuesses();
        
        
    } // while
    
    
    
    return 0;
} // main()
