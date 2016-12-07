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
    bool answer = true;
    for(int i = 0; i < 5; i++)
    {
        area = 0;
        
        min_size = 0;
        min_size_i = 0;
        min_size_j = 0;
        
        is_checked = false;
        
        string input_path = argv[1];
        input_path += "Input/input";
        input_path += to_string(i);
        input_path += ".txt";
        
        string output_path = argv[1];
        output_path += "Output/output";
        output_path += to_string(i);
        output_path += ".txt";
        
        string test_path = argv[1];
        test_path += "Test/test";
        test_path += to_string(i);
        test_path += ".txt";
        
        ifstream input(input_path);
        ofstream output(output_path);
        ifstream compare_o(output_path);
        ifstream compare_t(test_path);
        
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
        
        check = countArea();
        
        if(!check)
        {
            return;
        }
        
        check = getValidSizes(area, min_size_i, min_size_j);
        
        
        is_checked = true;
        
        
        printFieldInfo(output_path);
        answer *= compareTest(compare_o, compare_t);
        
        input.close();
        output.close();
        compare_o.close();
        compare_t.close();
    }
    
    if(answer)
    {
        cout << "Тест прошел!";
    }
    else
    {
        cout << "Тест не прошел!";
    }
}

bool Field::checkUserInput(int argc,
                           ifstream& input,
                           ofstream& output)
{
    if(argc != 2)
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
        state_size.printStateInfo();
        
        for(int i = 0; i < state_tree.size(); i++)
        {
            int new_state_id = (int)state_tree.size();
            State state = state_tree[i].countStep(new_state_id);
            
            state.printStateInfo();
            
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

void Field::printFieldInfo(string path)
{
    ofstream out(path);
    
    if(!out)
        cout << "Ошибка!" << path;
    
    out << "Polymino figures: " << endl;
    
    for(int i = 0; i < valid_data.size(); i++)
    {
        valid_data[i].printPolyminoInfo(out);
    }
    
    out << endl << "All valid sizes: " << endl;
    
    for(int i = 0; i < valid_sizes.size(); i++)
    {
        valid_sizes[i].printCoordinatesInfo(out);
        out << endl;
    }
    
    out << endl << "Area: " << area << endl << endl;
}

bool Field::compareTest(ifstream& i, ifstream& t)
{
    string s1((istreambuf_iterator<char>(i)), istreambuf_iterator<char>());
    string s2((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
    bool answer = (s1==s2);
    return answer;
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
