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

#include "Coordinates.hpp"

using namespace std;

#endif /* functions_hpp */

int** get_zero_square_array(size_t);
void fill_area_around_by_units(int**&, size_t, size_t);
void get_first_unit_index(int**, size_t, long long&, long long&);
Coordinates get_first_unit_coordinates(int**, size_t);
void delete_square_array(int**,size_t);
void get_help();

