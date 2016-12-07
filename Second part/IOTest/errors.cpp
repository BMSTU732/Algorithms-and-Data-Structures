//
//  errors.cpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 29.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//
#include "errors.hpp"

void get_error(Errors code, ostream& output)
{
    switch (code) {
        case ZERO_ARR:
            output << "Нулевой массив!" << endl;
            break;
            
        case UNKNOWN_SYMBOL:
            output << "Обнаружен неверный элемент массива!" << endl;
            break;
            
        case HOLE:
            output << "Обнаружено отверстие в фигуре!" << endl;
            break;
            
        case NO_FILE:
            output << "Файл не найден!" << endl;
            break;
            
        case NOT_SINGLE:
            output << "В массиве несколько фигур!" << endl;
            break;
            
        case WRONG_SIDE_SIZE:
            output << "Неверный размер массива!" << endl;
            break;
            
        default:
            break;
    }
}

