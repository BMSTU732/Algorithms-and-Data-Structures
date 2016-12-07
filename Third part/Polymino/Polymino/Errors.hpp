//
//  errors.hpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 29.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#ifndef errors_hpp
#define errors_hpp

#include <iostream>

using namespace std;

// различные ошибки для вывода в консоль
enum Errors
{
    ZERO_ARR,
    UNKNOWN_SYMBOL,
    HOLE,
    NO_FILE,
    NOT_SINGLE,
    WRONG_SIDE_SIZE,
    NEED_HELP,
    INVALID_AREA,
    NO_ANSWER,
    WIN
};

#endif /* errors_hpp */

void getError(Errors);





