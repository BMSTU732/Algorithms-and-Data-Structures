//
//  errors.cpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 29.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//
#include "errors.hpp"

void getError(Errors code)
{
    switch (code) {
        case ZERO_ARR:
            cout << "Вы ввели массив, состоящий из одних нулей! "
            << endl;
            break;
            
        case UNKNOWN_SYMBOL:
            cout << "Вы ввели массив, содержащий неизвестный элемент! "
            << endl;
            break;
            
        case HOLE:
            cout << "Вы ввели элемент, содержащий отверстие! "
            << endl;
            break;
            
        case NO_FILE:
            cout << "Файл не найден! "
            << endl;
            break;
            
        case NOT_SINGLE:
            cout << "Элемент не единственный! "
            << endl;
            break;
            
        case WRONG_SIDE_SIZE:
            cout << "Неверный размер массива! "
            << endl;
            break;
            
        case NEED_HELP:
            cout << "Использование: ./a.out <Путь папки>"
            << endl;
            break;
            
        case INVALID_AREA:
            cout << "Входные фигуры нельзя уместить в прямоугольник! "
            << endl;
            break;
            
        default:
            break;
    }
}

