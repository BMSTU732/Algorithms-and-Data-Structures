//
//  Polymino.cpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 30.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#include "Polymino.hpp"

Polymino::Polymino(int** array, size_t size):
array_performance(array),
side_size(size)
{
    bool check = checkValidation();
    
    if(check)
    {
        countArea();
        countGroupPerformance();
    }
}

void Polymino::freeArray()
{
    delete_square_array(array_performance, side_size);
}

Polymino::~Polymino()
{
    //delete_square_array(array_performance, side_size);
}

bool Polymino::countArea()
{
    int sum = 0;
    
    for(int i = 0; i < side_size; i++)
    {
        for(int j = 0; j < side_size; j++)
        {
            sum += array_performance[i][j];
        }
    }
    
    area = sum;
    return true;
}

bool Polymino::checkValidation()
{
    is_correct = !check_array_performance(array_performance, side_size);
    //т.к. вернет true если найдет ошибку
    
    return is_correct;
}

bool Polymino::countGroupPerformance()
{
    cout << "Вызвана функция группового представления!" << endl;
    return false;
}

bool Polymino::setPrimaryKey(int value)
{
    primary_key = value;
    return true;
}

void Polymino::printArrayPerformance()
{
    cout << endl;
    for(size_t i = 0; i < side_size; i++)
    {
        for(size_t j = 0; j < side_size; j++)
        {
            cout << "[ " << i << " , " << j <<" ] " << array_performance[i][j] << ' ';
        }
        cout << endl;
    }
}

int Polymino::getArea()
{
    return area;
}


