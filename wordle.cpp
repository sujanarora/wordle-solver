//
//  wordle.cpp
//  wordle-solver
//
//  Created by Sujan Arora on 2/10/22.
//

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "xcode_redirect.hpp"

using namespace std;

struct WordWeight{
    std::string word;
    long double freq;
};


int main(int argc, char ** argv){
    std::ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    vector<WordWeight> v;
    v.resize(12972);
    std::string s;
    long double f;
    size_t counter = 0;
    
    while (cin >> s >> f){
        v[counter].word = s;
        v[counter].freq = f;
        ++counter;
    }
    
    return 0;
}
