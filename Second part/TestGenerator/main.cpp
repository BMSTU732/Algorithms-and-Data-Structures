//
//  main.cpp
//  TestGenerator
//
//  Created by Rishat Valitov on 30.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//
#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

void get_help()
{
    cout << "Usage: ./<name>.out <output file path>" << endl;
}

// Создает файл для тестирования ввода,
// длиной до 10000 обьектов с разбросом сторон от 5 до 15

int main(int argc, const char * argv[]) {
    
    if(argc != 2)
    {
        get_help();
        return 0;
    }
    
    srand((unsigned int)time(0));
    
    ofstream out(argv[1]);
    
    if (!out) {
        cout << "Cannot open file!";
        return 1;
    }
    
    int value = rand() % 10000;
    
    out << value << endl;
    
    for(int i = 0; i < value; i++)
    {
        out << i << endl;
        int size = rand() % 10 + 5;
        
        out << size << endl;
        
        for(int j = 0; j < size; j++)
        {
            for(int k = 0; k < size; k++)
            {
                out << rand() % 2 << " ";
            }
            out << endl;
        }
    }
    
    out.close ();
    return 0;
}
