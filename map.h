#pragma once

#include <iostream>
#include <string>
#include <array>
#include <random>
using namespace std;


class map
{
public:
    //relative probabilities
    int skeleton_probability = 1;
    int bomb_probability = 1;
    int money_probability = 1;
    //constructor
    map();
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

