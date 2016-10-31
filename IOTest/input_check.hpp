//
//  input_check.hpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 29.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#ifndef input_check_hpp
#define input_check_hpp

#include <stdio.h>
#include <stack>
#include <vector>
#include <iterator>
#include <fstream>

#include "Coordinates.hpp"
#include "errors.hpp"
#include "functions.hpp"

#endif /* input_check_hpp */

bool check_array_for_correct_numbers(int**, size_t);
void push_to_buffer_zeros_hoods(stack<Coordinates>&, Coordinates, int**, size_t);
bool get_zeros_not_hole_coordinates(vector<Coordinates>&, Coordinates, int**, size_t);

bool check_array_for_holes(int**, size_t, ostream&);
bool check_array_performance(int**, size_t, ostream&);
bool check_array_for_single_figure(int**, size_t, ostream&);

void push_to_buffer_units_hoods(stack<Coordinates>&, Coordinates, int**, size_t);
bool get_units_coordinates(vector<Coordinates>&, Coordinates, int**, size_t);
