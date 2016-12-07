//
//  main.cpp
//  Polymino
//
//  Created by Rishat Valitov on 30.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include "Polymino.hpp"
#include "Field.hpp"
#include "Errors.hpp"

using namespace std;

int main(int argc, const char* argv[])
{
    Field field(argc, argv);
    bool has_answer = field.tryLocalOptimum();
    
    if(has_answer)
    {
        getError(WIN);
        field.getAnswer();
    }
    else
    {
        getError(NO_ANSWER);
    }
    
    return 0;
}
