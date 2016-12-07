//
//  State.hpp
//  Polymino
//
//  Created by Rishat Valitov on 24.11.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//
#ifndef State_hpp
#define State_hpp

#include <string>
#include <iostream>

#include "Polymino.hpp"
#include "PolyminoComparative.hpp"

using namespace std;

class State
{
public:
    
    vector<PolyminoComparative> old_comparatives;
    vector<Polymino> data;
    
    unsigned int id;
    int parent_id;
    
    int is_final;
    
    size_t height;
    size_t width;
    
    string group_performance_base;
    
    PolyminoComparative comparative;
    
    string getGroupPerformance();
    size_t getWidth();
    size_t getHeight();
    
    State countStep(int);
    void countComparatives();
    
    void printStateInfo();
    
    State();
    State(size_t,
          size_t,
          unsigned int,
          int,
          vector<Polymino>);
    State(size_t,
          size_t,
          string,
          unsigned int,
          int,
          vector<Polymino>);
    ~State();
    
    State& operator = (const State&);
};

#endif /* State_hpp */
