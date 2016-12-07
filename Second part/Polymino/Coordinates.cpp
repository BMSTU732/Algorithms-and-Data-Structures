//
//  Coordinates.cpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 29.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//
#include "Coordinates.hpp"

Coordinates::Coordinates(size_t x, size_t y):i(x),j(y){}

Coordinates& Coordinates::operator = (const Coordinates& right)
{
    if (this == &right) {
        return *this;
    }
        
    i = right.i;
    j = right.j;
        
    return *this;
}
    
bool Coordinates::operator < (const Coordinates& right)const
{
    return (i < right.i)||(j < right.j);
}

bool Coordinates::operator == (const Coordinates& right)const
{
    return (i == right.i)&&(j == right.j);
}
