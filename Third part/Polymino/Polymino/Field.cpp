//
//  Field.cpp
//  Polymino
//
//  Created by Rishat Valitov on 24.11.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#include "Field.hpp"

Field::~Field()
{}

Field::Field(int argc, const char* argv[])
{
    area = 0;
    min_size = 0;
    min_size_i = 0;
    min_size_j = 0;
    is_checked = false;
    
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    
    bool check = false;
    
    check = checkUserInput(argc, input, output);
    
    if(!check)
    {
        return;
    }
    
    check = inputDataFromFile(input, output);
    
    if(!check)
    {
        return;
    }
    
    output_str = argv[2];
    
    check = countArea();
    
    if(!check)
    {
        return;
    }
    
    check = getValidSizes(area, min_size_i, min_size_j);
    
    if(!check)
    {
        getError(INVALID_AREA);
        return;
    }
    else
    {
        is_checked = true;
    }
}

bool Field::checkUserInput(int argc,
                           ifstream& input,
                           ofstream& output)
{
    if(argc != 3)
    {
        getError(NEED_HELP);
        return false;
    }
    
    if(!input || !output)
    {
        getError(NEED_HELP);
        return false;
    }
    
    return true;
}

bool Field::inputDataFromFile(ifstream& input, ofstream& output)
{
    vector<Polymino> input_polymino;
    
    size_t number_of_figures = 0;
    size_t square_size = 0;
    
    //количество фигур на ввод
    input >> number_of_figures;
    
    for(int i = 0; i < number_of_figures; i++)
    {
        int figure_id = 0;
        int number_of_figures = 0;
        
        // Cчитываем id фигуры
        input >> figure_id;
        
        // Cторона массива
        input >> square_size;
        
        if(square_size <= 0)
        {
            getError(WRONG_SIDE_SIZE);
            return false;
        }
        
        // Количество фигур
        input >> number_of_figures;
        
        vector<vector<int>> binary_performance = Polymino::getZeroSquareArray(square_size);
        
        for(size_t j = 0; j < square_size; j++)
        {
            for(size_t k = 0; k < square_size; k++)
            {
                input >> binary_performance[j][k];
            }
        }
        
        //конструктор выполняет проверку на корректность данных
        Polymino item(binary_performance);
        
        if(item.is_correct)
        {
            item.setPrimaryKey(figure_id);
            item.setNumberOfFigures(number_of_figures);
            input_polymino.push_back(item);
        }
        else
        {
            return false;
        }
        
        valid_data = input_polymino;

    }
    return true;
}

bool Field::countArea()
{
    for(int i = 0; i < valid_data.size(); i++)
    {
        area += valid_data[i].getArea() * valid_data[i].number_of_same_figures;
        
        if(valid_data[i].getSize() > min_size)
        {
            min_size = valid_data[i].getSize();
        }
        
        if(valid_data[i].side_size_i > min_size_i)
        {
            min_size_i = valid_data[i].side_size_i;
        }
        
        if(valid_data[i].side_size_j > min_size_j)
        {
            min_size_j = valid_data[i].side_size_j;
        }
    }
    
    if(area > 0)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

bool Field::getValidSizes(size_t area, size_t min_size_i, size_t min_size_j)
{
    vector<Coordinates> answer;
    
    for(int i = 1; i <= area / 2; i++)
    {
        if( area % i == 0)
        {
            int first_factor = i;
            int second_factor = (int)area/i;
            
            if((first_factor >= min_size_i &&
               second_factor >= min_size_j)||
               ((first_factor >= min_size_j &&
                 second_factor >= min_size_i)))
            {
                answer.push_back(Coordinates(first_factor, second_factor));
            }
        }
    }
    
    int array_half_size = (int)answer.size()/2;
    
    for(int i = 0; i < array_half_size ; i++)
    {
        answer.pop_back();
    }
    
    if(answer.size() > 0)
    {
        valid_sizes = answer;
        return true;
    }
    else
    {
        return false;
    }
}

bool Field::tryLocalOptimum()
{
    // Пробегаем все возможные размеры прямоугольника
    for(int j = 0; j < valid_sizes.size(); j++)
    {
        state_tree.clear();
        
        State state_size(valid_sizes[j].i,
                    valid_sizes[j].j,
                    0,
                    -1,
                    valid_data);
        state_tree.push_back(state_size);
        
        for(int i = 0; i < state_tree.size(); i++)
        {
            int new_state_id = (int)state_tree.size();
            State state = state_tree[i].countStep(new_state_id);
            
            switch (state.is_final)
            {
                case 1:
                    state_tree.push_back(state);
                    return true;
                    
                case -1:
                    return false;
                    
                default:
                    state_tree.push_back(state);
            }
        }
    }
    return false;
}

void Field::printFieldInfo()
{
    cout << "Polymino figures: " << endl;
    
    for(int i = 0; i < valid_data.size(); i++)
    {
        valid_data[i].printPolyminoInfo();
    }
    
    cout << endl << "All valid sizes: " << endl;
    
    for(int i = 0; i < valid_sizes.size(); i++)
    {
        valid_sizes[i].printCoordinatesInfo();
        cout << endl;
    }
    
    cout << endl << "Area: " << area << endl << endl;
}

void Field::getAnswer()
{
    int end = 0;
    ofstream output(output_str);
    
    output << "Answer: " << endl;
    
    for(int i = 0; i < state_tree.size(); i++)
    {
        if(state_tree[i].is_final == 1)
        {
            end = state_tree[i].parent_id;
        }
    }
    
    while(end >= 0)
    {
        output << state_tree[end].comparative.polymino.getPrimaryKey() << ". "
        << endl << state_tree[end].comparative.field_group_performance << endl;
        
        end = state_tree[end].parent_id;
    }
}
