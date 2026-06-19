#pragma once

#include <iostream>
#include <string>
#include <array>
#include <random>
#include <map>
#include <tuple>
using namespace std;


class MapGen //map generator
{
public:
    //relative probabilities
    int skeleton_probability = 1;
    int bomb_probability = 1;
    int money_probability = 1;
    //lookup table for map generation
    //1 = up, 2 = right, 3 = down, 4 = left, 5 = dead end, 6 = boundary
    //1st int is number of current tile type, 2nd int is number of adjacent tile type, output value is int since will be either zero or 1
    //values implemented in .cpp file
    std::map<std::tuple<int, int>, int> mapLookupTable;

    //constructor
    MapGen();
    //method for modifying probability of certain spawns (enemies, money, etc) for adjusting gameplay
    void set_probabilities(int skeletons, int bombs, int money);
    //method for actually converting the maze into a map with 9x the spaces
    //make sure to create a new discrete distribution at the beginning of the method definition
    void generate_map(vector<vector<int>> maze);
    vector<vector<int>> return_map();
private:
    //private and accessed by a function to ensure the map is not used elsewhere in the game before it is finished
    vector<vector<int>> finished_map;
};

