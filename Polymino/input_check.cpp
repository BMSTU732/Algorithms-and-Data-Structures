//
//  input_check.cpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 29.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//
#include "input_check.hpp"

// Проверка на ввод матрицы
// Не пускает нулевые матрицы и матрицы
// в которых есть что-то кроме 0 и 1
bool check_array_for_correct_numbers(int** array, size_t size)
{
    int unit_element_counter = 0;
    
    for(size_t i = 0; i < size; i++)
    {
        for(size_t j = 0; j < size; j++)
        {
            if((array[i][j] != 1)&&(array[i][j] != 0))
            {
                get_error(UNKNOWN_SYMBOL);
                return true;
            }
            
            if(array[i][j] == 1)
            {
                unit_element_counter++;
            }
        }
    }
    
    if (unit_element_counter == 0)
    {
        get_error(ZERO_ARR);
        return true;
    }
    
    return false;
}

// заносит в стек буфер соседние элементы такого же типа что и входящий
void push_to_buffer_element_hoods(stack<Coordinates>& buffer, Coordinates element, int** array, size_t size)
{
    if((element.j + 1 != size)&&(array[element.i][element.j + 1] == array[element.i][element.j]))
    {
        Coordinates coord_to_push(element.i, element.j + 1);
        buffer.push(coord_to_push);
    }
    
    if((element.j != 0)&&(array[element.i][element.j - 1] == array[element.i][element.j]))
    {
        Coordinates coord_to_push(element.i, element.j - 1);
        buffer.push(coord_to_push);
    }
    
    if((element.i + 1 != size)&&(array[element.i + 1][element.j] == array[element.i][element.j]))
    {
        Coordinates coord_to_push(element.i + 1, element.j);
        buffer.push(coord_to_push);
    }
    
    if((element.i != 0)&&(array[element.i - 1][element.j] == array[element.i][element.j]))
    {
        Coordinates coord_to_push(element.i - 1, element.j);
        buffer.push(coord_to_push);
    }
}

//возвращает массив координат нулей, не являющихся отверстиями
bool get_zeros_not_hole_coordinates(vector<Coordinates>& zeros, Coordinates element,
                                    int** array, size_t size)
{
    vector<Coordinates>::iterator search = find(zeros.begin(), zeros.end(), element);
    
    if(search != zeros.end())
    {
        return false;
    }
    
    stack<Coordinates> buffer;
    
    zeros.push_back(element);
    
    push_to_buffer_element_hoods(buffer, element, array, size);
    
    while(!buffer.empty())
    {
        Coordinates check = buffer.top();
        buffer.pop();
        
        search = find(zeros.begin(), zeros.end(), check);
        
        if(search == zeros.end())
        {
            zeros.push_back(check);
            push_to_buffer_element_hoods(buffer, check, array, size);
        }
    }
    return true;
}

//проверка на отверстия
bool check_array_for_holes(int** array, size_t size)
{
    vector<Coordinates> zeros_not_hole;
    vector<Coordinates>::iterator search;
    
    // идем по контуру и ищем все скопления нулей имеющих доступ к контуру
    for(int i = 0; i < size; i++)
    {
        if (array[i][0] == 0)
        {
            Coordinates coord(i, 0);
            get_zeros_not_hole_coordinates(zeros_not_hole, coord, array, size);
        }
        if (array[0][i] == 0)
        {
            Coordinates coord(0, i);
            get_zeros_not_hole_coordinates(zeros_not_hole, coord, array, size);
        }
        if (array[size - 1][i] == 0)
        {
            Coordinates coord(size - 1, i);
            get_zeros_not_hole_coordinates(zeros_not_hole, coord, array, size);
        }
        if (array[i][size - 1] == 0)
        {
            Coordinates coord(i, size - 1);
            get_zeros_not_hole_coordinates(zeros_not_hole, coord, array, size);
        }
    }
    
    //проверяем все ли нули имеют доступ к контуру
    for(size_t i = 0; i < size; i++)
    {
        for(size_t j = 0; j < size; j++)
        {
            if(array[i][j] == 0)
            {
                search = find(zeros_not_hole.begin(), zeros_not_hole.end(), Coordinates(i, j));
                
                if(search == zeros_not_hole.end())
                {
                    get_error(HOLE);
                    return true;
                }
            }
        }
    }
    return false;
}

//получаем координаты элементов одного(любого) скоплений единиц
bool get_units_coordinates(vector<Coordinates>& units, Coordinates element,
                                    int** array, size_t size)
{
    vector<Coordinates>::iterator search;
    search = find(units.begin(), units.end(), element);

    if(search != units.end())
    {
        return false;
    }
    
    stack<Coordinates> buffer;
    
    units.push_back(element);
    
    push_to_buffer_element_hoods(buffer, element, array, size);
    
    while(!buffer.empty())
    {
        Coordinates check = buffer.top();
        buffer.pop();
        
        vector<Coordinates>::iterator search = find(units.begin(), units.end(), check);
        
        if(search == units.end())
        {
            units.push_back(check);
            push_to_buffer_element_hoods(buffer, check, array, size);
        }
    }
    return true;
}

//проверяем на наличие нескольких фигур
bool check_array_for_single_figure(int** array, size_t size)
{
    vector<Coordinates> units_in_figure;
    vector<Coordinates>::iterator search;
    
    Coordinates first_unit = get_first_unit_coordinates(array, size);
    
    get_units_coordinates(units_in_figure, first_unit, array, size);
    
    //если найдется единица не из первого пучка, значит скоплений несколько
    for(size_t i = 0; i < size; i++)
    {
        for(size_t j = 0; j < size; j++)
        {
            if(array[i][j] == 1)
            {
                search = find(units_in_figure.begin(), units_in_figure.end(), Coordinates(i, j));
                
                if(search == units_in_figure.end())
                {
                    get_error(NOT_SINGLE);
                    return true;
                }
            }
        }
    }
    return false;
}

// true - если нашли ошибку
bool check_array_performance(int** array, size_t size)
{
    bool correct_number_check = true;
    bool holes_check = true;
    bool single_figure_check = true;
    
    correct_number_check = check_array_for_correct_numbers(array, size);
    
    if(correct_number_check)
    {
        return true;
    }
    
    single_figure_check = check_array_for_single_figure(array, size);
    
    if(single_figure_check)
    {
        return true;
    }
    
    holes_check = check_array_for_holes(array, size);
    
    if(holes_check)
    {
        return true;
    }
    
    return false;
}


