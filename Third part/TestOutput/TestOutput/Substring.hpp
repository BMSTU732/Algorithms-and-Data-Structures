//
//  Substring.hpp
//  Polymino
//
//  Created by Rishat Valitov on 06.12.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#ifndef Substring_hpp
#define Substring_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Substring
{
public:
    
    string substring;
    
    int rotation;
    size_t size;
    
    size_t index_in_field;
    size_t index_in_polymino;
    
    Substring(string, int, size_t, size_t);
    Substring();
    ~Substring();
};

#endif /* Substring_hpp */
