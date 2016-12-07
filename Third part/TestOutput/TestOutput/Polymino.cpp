//
//  Polymino.cpp
//  Polimino_cover
//
//  Created by Rishat Valitov on 30.10.16.
//  Copyright © 2016 Rishat Valitov. All rights reserved.
//
#include "Polymino.hpp"

// Public functions

Polymino::Polymino():
side_size{0},
area{0},
number_of_same_figures{0},
primary_key{-1},
is_correct{false}
{}

Polymino::Polymino(vector<vector<int>> array):
array_performance{array},
side_size{array.size()}
{
    bool check = checkValidation();
    
    if(check)
    {
        countArea();
        countGroupPerformance();
        countSizes();
    }
}

Polymino::~Polymino()
{}

bool Polymino::setPrimaryKey(int value)
{
    primary_key = value;
    return true;
}

bool Polymino::setNumberOfFigures(int value)
{
    number_of_same_figures = value;
    return true;
}

void Polymino::printArrayPerformance()
{
    cout << endl;
    for(size_t i = 0; i < side_size; i++)
    {
        for(size_t j = 0; j < side_size; j++)
        {
            cout << "[ " << i << " , " << j <<" ] " << array_performance[i][j] << ' ';
        }
        cout << endl;
    }
}

void Polymino::printArray(vector<vector<int>> array_performance)
{
    int side_size = (int)array_performance.size();
    
    cout << endl;
    for(size_t i = 0; i < side_size; i++)
    {
        for(size_t j = 0; j < side_size; j++)
        {
            cout << array_performance[i][j] << ' ';
        }
        cout << endl;
    }
}

void Polymino::printGroupPerfomances()
{
    for(int i = 0; i < group_performances_array.size(); i++)
    {
        cout << group_performances_array[i] << endl;
    }
}

void Polymino::printPolyminoInfo()
{
    cout << endl << getPrimaryKey() << endl << "Array performance:";
    printArrayPerformance();
    
    cout << endl << "Group performances:" << endl;
    printGroupPerfomances();
}

vector<vector<int>> Polymino::getArrayPerformance()
{
    return array_performance;
}

vector<string> Polymino::getGroupPerformances()
{
    return group_performances_array;
}

string Polymino::getGroupPerformanceByIndex(int index)
{
    if(index < group_performances_array.size())
    {
        return group_performances_array[index];
    }
    else
    {
        return nullptr;
    }
}

int Polymino::getPrimaryKey()
{
    return primary_key;
}

int Polymino::getArea()
{
    return area;
}

size_t Polymino::getSize()
{
    return side_size;
}

// Private functions

bool Polymino::countArea()
{
    int sum = 0;
    
    for(int i = 0; i < side_size; i++)
    {
        for(int j = 0; j < side_size; j++)
        {
            sum += array_performance[i][j];
        }
    }
    
    area = sum;
    return true;
}

bool Polymino::countGroupPerformance()
{
    Coordinates first_unit(0,0);
    string answer = "A";
    
    vector<vector<int>> help_array = getHelpArray(array_performance);
    first_unit = getFirstUnitCoordinates(help_array);
    
    Coordinates current_pos(first_unit.i, first_unit.j + 2);
    char last_move = 'A';
    
    while(first_unit != current_pos)
    {
        char new_move = 'R';
        Coordinates next_pos = getNextPosition(help_array,
                                               current_pos,
                                               last_move,
                                               new_move);
        
        last_move = new_move;
        answer += last_move;
        current_pos = next_pos;
    }
    
    group_performances_array.push_back(answer);
    
    getAllGroupPerformances();
    
    return true;
}

bool Polymino::countSizes()
{
    int max_size_j = 0;
    int max_size_i = 0;
    
    for(int i = 0; i < side_size; i++)
    {
        int current_size_i = 0;
        int current_size_j = 0;
        
        for(int j = 0; j < side_size; j++)
        {
            current_size_i += array_performance[i][j];
            current_size_j += array_performance[j][i];
        }
        
        if(current_size_i > max_size_i)
        {
            max_size_i = current_size_i;
        }
        
        if(current_size_j > max_size_j)
        {
            max_size_j = current_size_j;
        }
    }
    
    if(max_size_i * max_size_j != 0)
    {
        side_size_i = max_size_i;
        side_size_j = max_size_j;
        
        return true;
    }
    
    return false;
}

// Вернет true если найдет ошибку
bool Polymino::checkValidation()
{
    is_correct = !checkArrayPerformance();
    
    return is_correct;
}

bool Polymino::checkArrayForCorrectNumbers()
{
    int unit_element_counter = 0;
    
    for(size_t i = 0; i < side_size; i++)
    {
        for(size_t j = 0; j < side_size; j++)
        {
            if((array_performance[i][j] != 1)
               &&(array_performance[i][j] != 0))
            {
                getError(UNKNOWN_SYMBOL);
                return true;
            }
            
            if(array_performance[i][j] == 1)
            {
                unit_element_counter++;
            }
        }
    }
    
    if (unit_element_counter == 0)
    {
        getError(ZERO_ARR);
        return true;
    }
    
    return false;
}

// Проверяем на наличие нескольких фигур
bool Polymino::checkArrayForSingleFigure()
{
    vector<Coordinates> units_in_figure;
    vector<Coordinates>::iterator search;
    
    Coordinates first_unit = getFirstUnitCoordinates();
    
    getUnitsCoordinates(units_in_figure, first_unit);
    
    // Если найдется единица не из первого пучка, значит скоплений несколько
    for(size_t i = 0; i < side_size; i++)
    {
        for(size_t j = 0; j < side_size; j++)
        {
            if(array_performance[i][j] == 1)
            {
                search = find(units_in_figure.begin(),
                              units_in_figure.end(),
                              Coordinates(i, j));
                
                if(search == units_in_figure.end())
                {
                    getError(NOT_SINGLE);
                    return true;
                }
            }
        }
    }
    return false;
}

// Проверка на отверстия
bool Polymino::checkArrayForHoles()
{
    vector<Coordinates> zeros_not_hole;
    vector<Coordinates>::iterator search;
    
    // Идем по контуру и ищем все скопления нулей имеющих доступ к контуру
    for(int i = 0; i < side_size; i++)
    {
        if (array_performance[i][0] == 0)
        {
            Coordinates coord(i, 0);
            getZerosNotHoleCoordinates(zeros_not_hole, coord);
        }
        if (array_performance[0][i] == 0)
        {
            Coordinates coord(0, i);
            getZerosNotHoleCoordinates(zeros_not_hole, coord);
        }
        if (array_performance[side_size - 1][i] == 0)
        {
            Coordinates coord(side_size - 1, i);
            getZerosNotHoleCoordinates(zeros_not_hole, coord);
        }
        if (array_performance[i][side_size - 1] == 0)
        {
            Coordinates coord(i, side_size - 1);
            getZerosNotHoleCoordinates(zeros_not_hole, coord);
        }
    }
    
    // Проверяем все ли нули имеют доступ к контуру
    for(size_t i = 0; i < side_size; i++)
    {
        for(size_t j = 0; j < side_size; j++)
        {
            if(array_performance[i][j] == 0)
            {
                search = find(zeros_not_hole.begin(),
                              zeros_not_hole.end(),
                              Coordinates(i, j));
                
                if(search == zeros_not_hole.end())
                {
                    getError(HOLE);
                    return true;
                }
            }
        }
    }
    return false;
}

// Вернет true если нашли ошибку
bool Polymino::checkArrayPerformance()
{
    bool correct_number_check = true;
    bool holes_check = true;
    bool single_figure_check = true;
    
    correct_number_check = checkArrayForCorrectNumbers();
    
    if(correct_number_check)
    {
        return true;
    }
    
    single_figure_check = checkArrayForSingleFigure();
    
    if(single_figure_check)
    {
        return true;
    }
    
    holes_check = checkArrayForHoles();
    
    if(holes_check)
    {
        return true;
    }
    
    return false;
}

// Возвращает массив координат нулей, не являющихся отверстиями
bool Polymino::getZerosNotHoleCoordinates(vector<Coordinates>& zeros, Coordinates element)
{
    vector<Coordinates>::iterator search = find(zeros.begin(),
                                                zeros.end(),
                                                element);
    
    if(search != zeros.end())
    {
        return false;
    }
    
    stack<Coordinates> buffer;
    
    zeros.push_back(element);
    
    pushToBufferElementHoods(buffer, element);
    
    while(!buffer.empty())
    {
        Coordinates check = buffer.top();
        buffer.pop();
        
        search = find(zeros.begin(), zeros.end(), check);
        
        if(search == zeros.end())
        {
            zeros.push_back(check);
            pushToBufferElementHoods(buffer, check);
        }
    }
    return true;
}

// Получаем координаты элементов одного(любого) скоплений единиц
bool Polymino::getUnitsCoordinates(vector<Coordinates>& units, Coordinates element)
{
    vector<Coordinates>::iterator search;
    search = find(units.begin(), units.end(), element);
    
    if(search != units.end())
    {
        return false;
    }
    
    stack<Coordinates> buffer;
    
    units.push_back(element);
    
    pushToBufferElementHoods(buffer, element);
    
    while(!buffer.empty())
    {
        Coordinates check = buffer.top();
        buffer.pop();
        
        vector<Coordinates>::iterator search = find(units.begin(),
                                                    units.end(),
                                                    check);
        
        if(search == units.end())
        {
            units.push_back(check);
            pushToBufferElementHoods(buffer, check);
        }
    }
    return true;
}

// Заносит в стек буфер соседние элементы такого же типа что и входящий
void Polymino::pushToBufferElementHoods(stack<Coordinates>& buffer, Coordinates element)
{
    if((element.j + 1 != side_size)&&
       (array_performance[element.i][element.j + 1] ==
        array_performance[element.i][element.j]))
    {
        Coordinates coord_to_push(element.i, element.j + 1);
        buffer.push(coord_to_push);
    }
    
    if((element.j != 0)&&
       (array_performance[element.i][element.j - 1] ==
        array_performance[element.i][element.j]))
    {
        Coordinates coord_to_push(element.i, element.j - 1);
        buffer.push(coord_to_push);
    }
    
    if((element.i + 1 != side_size)&&
       (array_performance[element.i + 1][element.j] ==
        array_performance[element.i][element.j]))
    {
        Coordinates coord_to_push(element.i + 1, element.j);
        buffer.push(coord_to_push);
    }
    
    if((element.i != 0)&&
       (array_performance[element.i - 1][element.j] ==
        array_performance[element.i][element.j]))
    {
        Coordinates coord_to_push(element.i - 1, element.j);
        buffer.push(coord_to_push);
    }
}

// Вспомогательные функции

vector<vector<int>> Polymino::getZeroSquareArray(size_t size)
{
    vector<vector<int>> square_array(size, vector<int>(size));
    
    for(size_t i = 0; i < size; i++)
    {
        for(size_t j = 0; j < size; j++)
        {
            square_array[i][j] = 0;
        }
    }
    return square_array;
}

void Polymino::fillAreaAroundByUnits(Coordinates coord)
{
    array_performance[coord.i][coord.j] = 1;
    
    array_performance[coord.i - 1][coord.j] = 1;
    array_performance[coord.i + 1][coord.j] = 1;
    array_performance[coord.i][coord.j - 1] = 1;
    array_performance[coord.i][coord.j + 1] = 1;
    
    array_performance[coord.i - 1][coord.j - 1] = 1;
    array_performance[coord.i - 1][coord.j + 1] = 1;
    array_performance[coord.i + 1][coord.j + 1] = 1;
    array_performance[coord.i + 1][coord.j - 1] = 1;
}

Coordinates Polymino::getFirstUnitCoordinates()
{
    Coordinates answer(-1,-1);
    
    for(size_t i = 0; i < side_size; i++)
    {
        for(size_t j = 0; j < side_size; j++)
        {
            if(array_performance[i][j] == 1)
            {
                answer.i = i;
                answer.j = j;
                break;
            }
        }
        
        if ((answer.j!=-1)&&(answer.i!=-1))
        {
            break;
        }
    }
    return answer;
}

vector<vector<int>> Polymino::getHelpArray(vector<vector<int>> array)
{
    int new_size = (int) array.size() * 2 + 3;
    vector<vector<int>> answer(new_size, vector<int>(new_size, 0));
    
    for (int i = 0; i < array.size(); i++)
    {
        for(int j = 0; j < array.size(); j++)
        {
            if(array[i][j] == 1)
            {
                answer[2*i+1][2*j+1] = 1;
                answer[2*i+1][2*j+2] = 1;
                answer[2*i+1][2*j+3] = 1;
                answer[2*i+3][2*j+1] = 1;
                answer[2*i+3][2*j+2] = 1;
                answer[2*i+3][2*j+3] = 1;
                answer[2*i+2][2*j+1] = 1;
                answer[2*i+2][2*j+2] = 1;
                answer[2*i+2][2*j+3] = 1;
            }
        }
    }
    
    vector<Coordinates> buffer;
    
    for (int i = 1; i < answer.size()-1; i++)
    {
        for(int j = 1; j < answer.size()-1; j++)
        {
            if(answer[i+1][j+1] == 1 &&
               answer[i+1][j] == 1 &&
               answer[i+1][j-1] == 1 &&
               answer[i-1][j+1] == 1 &&
               answer[i-1][j] == 1 &&
               answer[i-1][j-1] == 1 &&
               answer[i][j-1] == 1 &&
               answer[i][j] == 1 &&
               answer[i][j+1] == 1)
            {
                Coordinates coord(i,j);
                buffer.push_back(coord);
            }
        }
    }
    
    for(int i = 0; i < buffer.size(); i++)
    {
        answer[buffer[i].i][buffer[i].j] = 0;
    }
    return answer;
}

Coordinates Polymino::getFirstUnitCoordinates(vector<vector<int>> array)
{
    Coordinates first_unit(0,0);
    
    for(int i = 1; i < array.size(); i++)
    {
        for(int j = 1; j < array.size(); j++)
        {
            if(array[i][j] == 1)
            {
                first_unit.i = i;
                first_unit.j = j;
                return first_unit;
            }
        }
    }
    
    return first_unit;
}

Coordinates Polymino::getNextPosition(vector<vector<int>> array,
                                      Coordinates current,
                                      char last_move,
                                      char& new_move)
{
    switch (last_move)
    {
        case 'A':
            
            if(array[current.i - 1][current.j] == 1)
            {
                current.i-=2;
                new_move = 'D';
                return current;
            }
            
            if(array[current.i + 1][current.j] == 1)
            {
                current.i+=2;
                new_move = 'B';
                return current;
            }
            if(array[current.i][current.j + 1] == 1)
            {
                current.j+=2;
                new_move = 'A';
                return current;
            }
            
            break;
            
        case 'B':
            
            if(array[current.i + 1][current.j] == 1)
            {
                current.i+=2;
                new_move = 'B';
                return current;
            }
            
            if(array[current.i][current.j - 1] == 1)
            {
                current.j-=2;
                new_move = 'C';
                return current;
            }
            if(array[current.i][current.j + 1] == 1)
            {
                current.j+=2;
                new_move = 'A';
                return current;
            }
            
            break;
            
        case 'C':
            
            if(array[current.i - 1][current.j] == 1)
            {
                current.i-=2;
                new_move = 'D';
                return current;
            }
            
            if(array[current.i + 1][current.j] == 1)
            {
                current.i+=2;
                new_move = 'B';
                return current;
            }
            if(array[current.i][current.j - 1] == 1)
            {
                current.j-=2;
                new_move = 'C';
                return current;
            }
            
            break;
            
        case 'D':
            
            if(array[current.i - 1][current.j] == 1)
            {
                current.i-=2;
                new_move = 'D';
                return current;
            }
            
            if(array[current.i][current.j - 1] == 1)
            {
                current.j-=2;
                new_move = 'C';
                return current;
            }
            if(array[current.i][current.j + 1] == 1)
            {
                current.j+=2;
                new_move = 'A';
                return current;
            }
            
            break;
    }
    return Coordinates(0,0);
}

string Polymino::getTurnGroupPerformance(string performance)
{
    for(int i = 0; i < performance.size(); i++)
    {
        switch (performance[i])
        {
            case 'A':
                performance[i] = 'B';
                break;
            case 'B':
                performance[i] = 'C';
                break;
                
            case 'C':
                performance[i] = 'D';
                break;
                
            case 'D':
                performance[i] = 'A';
                break;
        }
    }
    
    return performance;
}

string Polymino::getMirrorGroupPerformance(string performance)
{
    for(int i = 0; i < performance.size(); i++)
    {
        switch (performance[i])
        {
            case 'A':
                performance[i] = 'C';
                break;
            case 'C':
                performance[i] = 'A';
                break;
        }
    }
    return performance;
}

void Polymino::getAllGroupPerformances()
{
    for(int i = 1; i < 4; i++)
    {
        group_performances_array.push_back(getTurnGroupPerformance(group_performances_array[i-1]));
    }
    group_performances_array.push_back(getMirrorGroupPerformance(group_performances_array[0]));
    
    for(int i = 5; i < 8; i++)
    {
        group_performances_array.push_back(getTurnGroupPerformance(group_performances_array[i-1]));
    }
}

Polymino& Polymino::operator = (const Polymino& right)
{
    number_of_same_figures = right.number_of_same_figures;
    primary_key = right.primary_key;
    is_correct = right.is_correct;
    array_performance = right.array_performance;
    side_size = right.side_size;
    group_performances_array = right.group_performances_array;
    area = right.area;

    return *this;
}
