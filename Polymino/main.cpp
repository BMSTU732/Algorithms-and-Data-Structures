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

#include "functions.hpp"
#include "Polymino.hpp"
#include "errors.hpp"

using namespace std;

//заглушка
bool get_answer(vector<Polymino> input)
{
    return false;
}

int main(int argc, const char * argv[]) {
    
    if(argc != 3)
    {
        get_help();
        return 0;
    }
    
    size_t number_of_figures = 0;
    size_t square_size = 0;
    
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    
    if(!input || !output)
    {
        get_help();
        return 0;
    }
    
    vector<Polymino> input_polymino;
    
    //количество фигур на ввод
    input >> number_of_figures;
    
    for(int i = 0; i < number_of_figures; i++)
    {
        int number = 0;
        // считываем id фигуры
        input >> number;
        
        //сторона массива
        input >> square_size;
        
        if(square_size <= 0)
        {
            get_error(WRONG_SIDE_SIZE);
            continue;
        }
        
        int** binary_performance = get_zero_square_array(square_size);
        
        for(size_t j = 0; j < square_size; j++)
        {
            for(size_t k = 0; k < square_size; k++)
            {
                input >> binary_performance[j][k];
            }
        }
        
        cout << number << ".";
        
        //конструктор выполняет проверку на корректность данных
        Polymino item(binary_performance, square_size);
        
        if(item.is_correct)
        {
            item.setPrimaryKey(number);
            input_polymino.push_back(item);
        }
        else
        {
            item.freeArray();
        }
        
        cout << endl;
    }
    
    get_answer(input_polymino);

    return 0;
}
