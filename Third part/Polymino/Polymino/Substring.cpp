//
//  Substring.cpp
//  Polymino
//
//  Created by Rishat Valitov on 06.12.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#include "Substring.hpp"

Substring::Substring(string str,
                     int rotation,
                     size_t index_polymino,
                     size_t index_field):
substring{str},
rotation{rotation},
index_in_polymino{index_polymino},
index_in_field{index_field}
{
    size = substring.size();
}

Substring::~Substring()
{}
