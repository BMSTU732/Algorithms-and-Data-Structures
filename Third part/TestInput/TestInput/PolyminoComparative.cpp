//
//  PolyminoComparative.cpp
//  Polymino
//
//  Created by Rishat Valitov on 02.12.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#include "PolyminoComparative.hpp"

PolyminoComparative::~PolyminoComparative()
{}

PolyminoComparative::PolyminoComparative(string base, Polymino figure):
field_group_performance{base},
polymino{figure},
end{false}
{
    vector<string> group_performances = polymino.getGroupPerformances();
    
    for(int i = 0; i < group_performances.size(); i++)
    {
        string buffer = base;
        
        for(int j = 0; j < buffer.size(); j++)
        {
            if(buffer == group_performances[i])
            {
                end = true;
                
                Substring common(field_group_performance,
                                 i,                       //rotation
                                 0,                       //index in polymino
                                 0);                      //index in field
                
                new_field_group_performances.push_back("");
                common_substrings.push_back(common);
                
                return;
            }
            buffer = getTurnedString(buffer);
        }
    }
    getPolyminosLargestCommonSubstring();
}

void PolyminoComparative::getPolyminosLargestCommonSubstring()
{
    vector<string> group_performances = polymino.getGroupPerformances();
    
    for(int i = 0; i < group_performances.size(); i++)
    {
        getLargestCommonSubstrings(group_performances[i], i);
    }
}

void PolyminoComparative::getLargestCommonSubstrings(string polymino_group_performance, int rotation)
{
    string field_string = field_group_performance + field_group_performance;
    string polymino_string = polymino_group_performance + polymino_group_performance;
    
    const int a_size = (int)field_string.size();
    const int b_size = (int)polymino_string.size();
    
    typedef vector<int> solution;
    
    const int solution_size = b_size + 1;
    solution x(solution_size, 0), y(solution_size);
    
    solution* previous = &x;
    solution* current = &y;
    
    size_t max_length = 0;
    size_t substring_begining_index_field = 0;
    size_t substring_begining_index_polymino = 0;
    
    for(int i = a_size - 1; i >= 0; i--)
    {
        for(int j = b_size - 1; j >= 0; j--)
        {
            int & current_match = (*current)[j];
            
            if(field_string[i] != polymino_string[j])
            {
                current_match = 0;
            }
            else
            {
                const int length = 1 + (*previous)[j + 1];
                
                if (length > max_length)
                {
                    max_length = length;
                    
                    substring_begining_index_field = i % (a_size/2);
                    substring_begining_index_polymino = j % (b_size/2);
                }
                
                current_match = length;
            }
        }
        
        swap(previous, current);
    }
    
    size_t substrings_length = 0;
    
    if(common_substrings.size() > 0)
    {
        substrings_length = common_substrings[0].size;
    }
    
    if(max_length > substrings_length)
    {
        common_substrings.clear();
        Substring substring(field_string.substr(substring_begining_index_field, max_length),
                            rotation,
                            substring_begining_index_polymino,
                            substring_begining_index_field);
        common_substrings.push_back(substring);
    }
    
    else if(max_length == substrings_length)
    {
        
        Substring substring(field_string.substr(substring_begining_index_field, max_length),
                            rotation,
                            substring_begining_index_polymino,
                            substring_begining_index_field);
        common_substrings.push_back(substring);
    }
}

bool PolyminoComparative::checkField(string input)
{
    vector<Coordinates> buffer;
    
    Coordinates coord(0,0);
    buffer.push_back(coord);
    
    for (int i = 0; i < input.size(); i++)
    {
        switch (input[i])
        {
            case 'A':
                coord.j++;
                break;
            case 'B':
                coord.i++;
                break;
            case 'C':
                coord.j--;
                break;
            case 'D':
                coord.i--;
                break;
            default:
                break;
        }
        
        if(i != input.size() - 1)
        {
            if(find(buffer.begin(),
                    buffer.end(),
                    coord)
               == buffer.end())
            {
                buffer.push_back(coord);
            }
            else
            {
                return false;
            }
        }
        else
        {
            if(coord != Coordinates(0, 0))
            {
                return false;
            }
        }
    }
    
    return true;
}

bool PolyminoComparative::countNewFieldBase()
{
    for(int i = 0; i < common_substrings.size(); i++)
    {
        if(field_group_performance.size() == 0)
        {
            return false;
        }
        
        else
        {
            string answer = "";
            string part_first = getInvertedPart(i);
                
            string field = field_group_performance;
                
            size_t begin = common_substrings[i].index_in_field;
            size_t end = (begin + common_substrings[i].substring.size()) % field.size();
                
            if(begin < end)
            {
                answer = field.substr(0, begin);
                answer += part_first;
                answer += field.substr(end, field.size() - end);
            }
            else
            {
                answer = field.substr(end, begin - end);
                answer += part_first;
            }
            
            new_field_group_performances.push_back(answer);
        }
    }
    return true;
}

string PolyminoComparative::getInvertedPart(int iterator)
{
    string answer = "";
    string inverted = "";
    string polymino_str = polymino.getGroupPerformanceByIndex(common_substrings[iterator].rotation);
    
    size_t begin = (common_substrings[iterator].index_in_polymino +
                    common_substrings[iterator].size)
                    % polymino_str.size();
    size_t size = polymino_str.size() - common_substrings[iterator].size;
    
    if(begin + size <= polymino_str.size())
    {
        inverted = polymino_str.substr(begin, size);
    }
    else
    {
        inverted = polymino_str.substr(begin, size);
    }
    
    for(int i = (int)inverted.size(); i >= 0 ; i--)
    {
        switch (inverted[i])
        {
            case 'A':
                answer.push_back('C');
                break;
            case 'B':
                answer.push_back('D');
                break;
            case 'C':
                answer.push_back('A');
                break;
            case 'D':
                answer.push_back('B');
                break;
            default:
                break;
        }
    }
    return answer;
}

size_t PolyminoComparative::getSubstringLength()
{
    if(common_substrings.size() > 0)
    {
        return common_substrings[0].size;
    }
    else return 0;
}

void PolyminoComparative::printComparativeInfo()
{
    cout << endl
    << "Base group performance: "
    << field_group_performance << endl
    << "Common substrings: ";
    
    for(int i = 0; i < common_substrings.size(); i++)
    {
        cout << common_substrings[i].substring
        << " " << common_substrings[i].index_in_polymino
        << " " << common_substrings[i].index_in_field
        << endl;
    }
    
    cout
    << "New field base string: ";
    
    for(int i = 0; i < new_field_group_performances.size(); i++)
    {
        cout << " " << new_field_group_performances[i] << endl;
    }
}

PolyminoComparative& PolyminoComparative::operator = (const PolyminoComparative& right)
{
    field_group_performance = right.field_group_performance;
    end = right.end;
    new_field_group_performances = right.new_field_group_performances;
    polymino = right.polymino;
    common_substrings = right.common_substrings;
    
    
    return *this;
}

string PolyminoComparative::getTurnedString(string input)
{
    size_t size = input.size();
    char tmp = input[size - 1];
    
    for(size_t i = size - 1; i > 0 ; i--)
    {
        input[i] = input[i - 1];
    }
    input[0] = tmp;
    
    return input;
}

