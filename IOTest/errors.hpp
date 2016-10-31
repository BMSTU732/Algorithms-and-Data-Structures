//
//  errors.hpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 29.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#ifndef errors_hpp
#define errors_hpp

#include <fstream>

using namespace std;

enum Errors
{
    ZERO_ARR,
    UNKNOWN_SYMBOL,
    HOLE,
    NO_FILE,
    NOT_SINGLE,
    WRONG_SIDE_SIZE
};

#endif /* errors_hpp */

void get_error(Errors, ostream&);






