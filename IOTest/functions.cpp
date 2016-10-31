//
//  functions.cpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 30.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#include "functions.hpp"

int** get_zero_square_array(size_t size)
{
    int** array = new int* [size];
    
    for(size_t i = 0; i < size; i++)
    {
        array[i] = new int[size];
        
        for(size_t j = 0; j < size; j++)
        {
            array[i][j] = 0;
        }
    }
    return array;
}

void fill_area_around_by_units(int**& input, size_t i, size_t j)
{
    input[i][j] = 1;
    input[i-1][j] = 1;
    input[i+1][j] = 1;
    input[i][j-1] = 1;
    input[i][j+1] = 1;
    input[i-1][j-1] = 1;
    input[i-1][j+1] = 1;
    input[i+1][j+1] = 1;
    input[i+1][j-1] = 1;
}

// Ищем первую единицу
void get_first_unit_index(int** input, size_t input_size,
                          long long& answer_i, long long& answer_j)
{
    for(size_t i = 0; i < input_size; i++)
    {
        for(size_t j = 0; j < input_size; j++)
        {
            if(input[i][j] == 1)
            {
                answer_i = i;
                answer_j = j;
                break;
            }
        }
        
        if ((answer_j!=-1)&&(answer_i!=-1))
        {
            break;
        }
    }
}

Coordinates get_first_unit_coordinates(int** input, size_t input_size)
{
    Coordinates answer(-1,-1);
    
    for(size_t i = 0; i < input_size; i++)
    {
        for(size_t j = 0; j < input_size; j++)
        {
            if(input[i][j] == 1)
            {
                answer.i = i;
                answer.j = j;
                break;
            }
        }
        
        if ((answer.j!=-1)&&(answer.i!=-1))
        {
            break;
        }
    }
    return answer;
}

void delete_square_array(int** array,size_t size)
{
    for (int i = 0; i < size; i++)
    {
        delete [] array[i];
    }
    delete [] array;
}

void get_help()
{
    cout << "Usage: ./Polymino_test.out <input file path> <output file path>" << endl;
}
