//
//  print.cpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 30.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#include "print.hpp"

void print_coord(Coordinates x)
{
    cout << "[ " << x.i << " , " << x.j << " ] ";
}

void print_vector_coord(vector<Coordinates> input)
{
    cout << endl;
    for(vector<Coordinates>::iterator iter = input.begin();
        iter != input.end();  iter++)
    {
        print_coord(*iter);
    }
    cout << endl;
}

void print_array_detail(int** array, size_t size)
{
    cout << endl;
    for(size_t i = 0; i < size; i++)
    {
        for(size_t j = 0; j < size; j++)
        {
            cout << "[ " << i << " , " << j <<" ] " << array[i][j] << ' ';
        }
        cout << endl;
    }
}

void print_array(int** array, size_t size)
{
    cout << endl;
    for(size_t i = 0; i < size; i++)
    {
        for(size_t j = 0; j < size; j++)
        {
            cout << array[i][j] << ' ';
        }
        cout << endl;
    }
}
