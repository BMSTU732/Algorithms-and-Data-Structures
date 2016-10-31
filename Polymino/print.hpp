//
//  print.hpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 30.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#ifndef print_hpp
#define print_hpp

#include <stdio.h>
#include <vector>
#include <iterator>
#include <iostream>

#include "Coordinates.hpp"

using namespace std;

#endif /* print_hpp */

//функции вывода
void print_coord(Coordinates);
void print_vector(vector<Coordinates>);
void print_array_detail(int**, size_t);
void print_array(int**, size_t);

