//
//  main.cpp
//  OITest
//
//  Created by Rishat Valitov on 31.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void get_help()
{
    cout << "Usage: ./Polymino_test.out <input file path> <output file path>" << endl;
}

int main(int argc, const char * argv[]) {
    
    if(argc != 3)
    {
        get_help();
        return 0;
    }
    
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    vector<int> array;
    
    if(!input || !output)
    {
        get_help();
        return 0;
    }
    
    while(!input.eof())
    {
        int number_of_figures_in_row = 0;
        int row = 0;
        input >> row >> number_of_figures_in_row;
        
        for(int i = 0; i < number_of_figures_in_row; i++)
        {
            int figure_id = 0;
            int figure_rotation = 0;
            input >> figure_id >> figure_rotation;
            
            if((figure_rotation > 8)||(figure_rotation < 1))
            {
                output << "Набор не корректен! Неизвестное положение фигуры!";
            }
            
            vector<int>::iterator search = find(array.begin(), array.end(), figure_id);
            
            if(search == array.end())
            {
                array.push_back(figure_id);
            }
            else
            {
                output << "Набор не корректен! Две фигуры с одинаковым id!";
            }
        }
    }
    output << "Набор корректен!";
    
    return 0;
}
