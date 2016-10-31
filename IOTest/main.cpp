//
//  main.cpp
//  IOTest
//
//  Created by Rishat Valitov on 30.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>

#include "errors.hpp"
#include "functions.hpp"
#include "input_check.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    size_t number_of_figures = 0;
    size_t square_size = 0;
    
    if(argc != 3)
    {
        get_help();
        return 0;
    }
    
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    
    if(!input || !output)
    {
        get_help();
        return 0;
    }

    input >> number_of_figures;
    for(int i = 0; i < number_of_figures; i++)
    {
        int number;
        input >> number;
            
        input >> square_size;
            
        output << "Массив номер " << number << " " << endl;
            
        if(square_size <= 0)
        {
            get_error(WRONG_SIDE_SIZE, output);
            output << "Проверку не прошел!" << endl << endl;
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
            
        bool result = check_array_performance(binary_performance, square_size, output);
            
        if(result)
        {
            output << "Проверку не прошел!" << endl << endl;
        }
        else
        {
            output << "Проверку прошел!" << endl << endl;
        }
            
        delete_square_array(binary_performance, square_size);
    }
        
    output << "Тест окончен!";
    
    input.close();
    output.close();
    return 0;
}
