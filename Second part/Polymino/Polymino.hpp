//
//  Polymino.hpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 30.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#ifndef Polymino_hpp
#define Polymino_hpp

#include <string>
#include <stdio.h>

#include "functions.hpp"
#include "print.hpp"
#include "input_check.hpp"

using namespace std;

//класс фигур

class Polymino
{
    int** array_performance;
    
    size_t side_size;
    
    string groupe_performance;
    
    int area;
    
public:
    
    int number_of_same_figures;
    int primary_key;
    
    bool is_correct;
    
    Polymino(int**, size_t);
    
    ~Polymino();
    void freeArray();
    
    /*bool setArrayPerformance(int**);
    bool setGroupPerformance(string);*/
    
    bool setPrimaryKey(int);
    
    void printArrayPerformance();
    void printGroupPerfomance();
    
    int** getArrayPerformance();
    string getGroupPerformance();
    int getArea();

private:
    
    bool countArea();
    bool countGroupPerformance();
    
    //использует метод из input_check
    bool checkValidation();
};

#endif /* Polymino_hpp */
