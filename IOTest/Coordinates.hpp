//
//  Coordinates.hpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 29.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#ifndef Coordinates_hpp
#define Coordinates_hpp

#include <stdio.h>

class Coordinates
{
public:
    size_t i;
    size_t j;
    
    Coordinates(size_t, size_t);
    
    Coordinates& operator = (const Coordinates&);
    
    bool operator < (const Coordinates&)const;
    bool operator == (const Coordinates&)const;
};

#endif /* Coordinates_hpp */
