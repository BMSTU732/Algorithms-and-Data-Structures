//
//  PolyminoComparative.hpp
//  Polymino
//
//  Created by Rishat Valitov on 02.12.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#ifndef PolyminoComparative_hpp
#define PolyminoComparative_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "Polymino.hpp"
#include "Substring.hpp"

using namespace std;

class PolyminoComparative
{
public:
    string field_group_performance;
    vector<string> new_field_group_performances;
    vector<Substring> common_substrings;

    Polymino polymino;
    bool end;
    
    PolyminoComparative(string, Polymino);
    ~PolyminoComparative();
    
    void getPolyminosLargestCommonSubstring();
    void getLargestCommonSubstrings(string, int);
    
    bool countNewFieldBase();
    bool checkField(string);
    
    size_t getSubstringLength();
    
    void printComparativeInfo();
    
    string getInvertedPart(int);
    string getTurnedString(string);
    
    PolyminoComparative& operator = (const PolyminoComparative&);
};

#endif /* PolyminoComparative_hpp */
