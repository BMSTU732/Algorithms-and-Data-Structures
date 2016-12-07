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
#include <vector>
#include <stack>
#include <fstream>

#include "Errors.hpp"
#include "Coordinates.hpp"

using namespace std;

// Класс фигур
class Polymino
{
public:
    
    int number_of_same_figures;
    int primary_key;
    bool is_correct;
    
    size_t side_size_i;
    size_t side_size_j;
    
    Polymino(vector<vector<int>>);
    Polymino();
    ~Polymino();
    
    bool setPrimaryKey(int);
    bool setNumberOfFigures(int);
    
    void printArrayPerformance(ofstream&);
    void printGroupPerfomances(ofstream&);
    void printPolyminoInfo(ofstream&);
    
    vector<vector<int>> getArrayPerformance();
    vector<string> getGroupPerformances();
    string getGroupPerformanceByIndex(int);
    
    int getPrimaryKey();
    int getArea();
    size_t getSize();
    
    // Вспомогательные функции
    
    static vector<vector<int>> getZeroSquareArray(size_t);
    Polymino& operator = (const Polymino&);

private:
    
    vector<vector<int>> array_performance;
    size_t side_size;
    vector<string> group_performances_array;
    int area;
    
    bool countArea();
    bool countGroupPerformance();
    bool countSizes();
    void getAllGroupPerformances();

    bool checkValidation();
    
    bool checkArrayForCorrectNumbers();
    bool checkArrayForSingleFigure();
    bool checkArrayForHoles();
    bool checkArrayPerformance();
    
    bool getZerosNotHoleCoordinates(vector<Coordinates>&, Coordinates);
    bool getUnitsCoordinates(vector<Coordinates>&, Coordinates);
    
    void pushToBufferElementHoods(stack<Coordinates>&, Coordinates);
    void printArray(vector<vector<int>>);
    
    // Вспомогательные функции
    
    void fillAreaAroundByUnits(Coordinates);
    vector<vector<int>> getHelpArray(vector<vector<int>>);
    
    Coordinates getFirstUnitCoordinates(vector<vector<int>>);
    Coordinates getNextPosition(vector<vector<int>>,
                                Coordinates,
                                char,
                                char&);
    Coordinates getFirstUnitCoordinates();
    
    string getTurnGroupPerformance(string);
    string getMirrorGroupPerformance(string);
};

#endif /* Polymino_hpp */
