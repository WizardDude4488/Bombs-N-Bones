#pragma once
#include <array>
#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <string>
#include <tuple>
using namespace std;

class maze
{
public:
    maze();
    vector<vector<int>> generate_maze(int mazeSizeInt);

    void newHud();
    void action(string command);
    void updateSkeletons();

private:
    vector<vector<int>> generated_maze;
    int player_x = 1;
    int player_y = 1;
    int player_health = 5;
    int player_money = 0;

    struct skeleton {
        int mazeX = 0;
        int mazeY = 0;
        int health = 2;
        int attackDamage = 1;

        //stores available tiles in range
        vector<vector<int>> available;

    };
    vector<skeleton> skeletonList;

};
