//
//  State.cpp
//  Polymino
//
//  Created by Rishat Valitov on 24.11.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//

#include "State.hpp"

State::State():
height{0},
width{0},
group_performance_base{""},
id{0},
parent_id{0},
is_final{0},
comparative{PolyminoComparative("", Polymino())}
{}

State::State(size_t height,
             size_t width,
             string base,
             unsigned int id,
             int parent_id,
             vector<Polymino> data):
height{height},
width{width},
group_performance_base{base},
id{id},
parent_id{parent_id},
data{data},
is_final{0},
comparative{PolyminoComparative(group_performance_base, Polymino())}
{
    countComparatives();
}

State::State(size_t height,
             size_t width,
             unsigned int id,
             int parent_id,
             vector<Polymino> data):
height{height},
width{width},
id{id},
parent_id{parent_id},
data{data},
is_final{0},
comparative{PolyminoComparative("", Polymino())}
{
    for(int i = 0; i < width; i++)
    {
        group_performance_base.append("A");
    }
    for(int i = 0; i < height; i++)
    {
        group_performance_base.append("B");
    }
    for(int i = 0; i < width; i++)
    {
        group_performance_base.append("C");
    }
    for(int i = 0; i < height; i++)
    {
        group_performance_base.append("D");
    }
    
    countComparatives();
}

State::~State()
{}

string State::getGroupPerformance()
{
    return group_performance_base;
}

size_t State::getWidth()
{
    return width;
}

size_t State::getHeight()
{
    return height;
}

void State::countComparatives()
{
    for(int i = 0; i < data.size(); i++)
    {
        PolyminoComparative max(group_performance_base, data[i]);
        
        if(max.getSubstringLength() >= comparative.getSubstringLength())
        {
            if(max.getSubstringLength() == comparative.getSubstringLength())
            {
                old_comparatives.push_back(max);
            }
            else
            {
                comparative = max;
                old_comparatives.clear();
            }
        }
    }
}

State State::countStep(int new_state_id)
{
    if(comparative.countNewFieldBase())
    {
        if(comparative.end)
        {
            State answer;
            answer.is_final = 1;
            answer.parent_id = id;
            return answer;
        }
        else
        {
            int primary_key = comparative.polymino.primary_key;
            
            for(int j = 0; j < data.size(); j++)
            {
                if(data[j].primary_key == primary_key)
                {
                    if(data[j].number_of_same_figures > 1)
                    {
                        data[j].number_of_same_figures--;
                    }
                    else
                    {
                        data.erase(data.begin()+j);
                    }
                }
            }
            if (comparative.new_field_group_performances.size() > 0)
            {
                return State(height,
                             width,
                             comparative.new_field_group_performances[0],         //??
                             new_state_id,
                             id,
                             data);
            }
            else
            {
                State answer = *this;
                
                if(old_comparatives.size() > 0)
                {
                    size_t end = old_comparatives.size() - 1;
                    answer.comparative = old_comparatives[end];
                    old_comparatives.pop_back();
                }
                else
                {
                    answer.is_final = -1;
                    answer.parent_id = id;
                }
                
                return answer;
            }
        }
    }
    else
    {
        State answer = *this;
        
        if(old_comparatives.size() > 0)
        {
            size_t end = old_comparatives.size() - 1;
            answer.comparative = old_comparatives[end];
            old_comparatives.pop_back();
        }
        else
        {
            answer.is_final = -1;
        }
        
        return answer;
    }
}

void State::printStateInfo()
{
    cout << "State #" << id << endl
    << "Parent id#" << parent_id << endl
    << "Height: " << height << endl
    << "Width: " << width << endl
    << "Base: " << group_performance_base << endl
    << "Comparative: ";
    
    comparative.printComparativeInfo();
    
    for(int i = 0; i < data.size(); i++)
    {
        //data[i].printPolyminoInfo();
    }
}

State& State::operator = (const State& right)
{
    old_comparatives = right.old_comparatives;
    data = right.data;
    
    id = right.id;
    parent_id = right.parent_id;
    
    is_final = right.is_final;
    height = right.height;
    width = right.width;
    
    group_performance_base = right.group_performance_base;
    comparative = right.comparative;
    
    return *this;
}
