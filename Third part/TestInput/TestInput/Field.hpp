//
//  Field.hpp
//  Polymino
//
//  Created by Rishat Valitov on 24.11.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#ifndef Field_hpp
#define Field_hpp

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include "Polymino.hpp"
#include "Errors.hpp"
#include "Coordinates.hpp"
#include "State.hpp"

using namespace std;

class Field
{
    vector<Polymino> valid_data;
    vector<State> state_tree;
    vector<Coordinates> valid_sizes;

    string output_str;
    
    size_t min_size;
    size_t min_size_i;
    size_t min_size_j;
    size_t area;
    
    bool is_checked;
    
public:

    Field(int, const char**);
    ~Field();
    
    void printFieldInfo(string);
    bool tryLocalOptimum();
    void getAnswer();
    
private:
    
    bool checkUserInput(int, ifstream&, ofstream&);
    bool inputDataFromFile(ifstream&, ofstream&);
    bool countArea();
    bool compareTest(ifstream&, ifstream&);
    
    bool getValidSizes(size_t, size_t, size_t);
};

#endif 
/* Field_hpp */
