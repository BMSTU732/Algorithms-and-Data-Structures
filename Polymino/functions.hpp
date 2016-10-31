//
//  functions.hpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 30.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#ifndef functions_hpp
#define functions_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "Coordinates.hpp"

using namespace std;

#endif /* functions_hpp */

// вспомогательные функции

int** get_zero_square_array(size_t);
void fill_area_around_by_units(int**&, size_t, size_t);
Coordinates get_first_unit_coordinates(int**, size_t);
void get_help();
void delete_square_array(int**,size_t);
