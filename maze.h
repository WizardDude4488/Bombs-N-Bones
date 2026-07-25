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
    struct tile {
        int base = 0;
        bool skeleton = false;
        bool money = false;
        bool exit = false;
    };

    vector<vector<tile>> generated_maze;
    int mazeSizeExt;

    int player_x = 1;
    int player_y = 1;
    int player_health = 5;
    int player_money = 0;

    struct skeleton {
        int x = 0;
        int y = 0;
        int health = 2;
        int attackDamage = 1;

        //stores available tiles in range
        vector<vector<int>> available;

        //operator for list search
        bool operator==(const skeleton& other) const {
            return x == other.x && y == other.y;
        }

    };

    bool exitFound = false;
    bool playerDead = false;

    vector<skeleton> skeletonList;

    //methods declared after structs are created
    maze();
    vector<vector<tile>> generate_maze(int mazeSizeInt);

    void newHud();
    void action(string command);
    void updateSkeletons();
    void printMaze();
    vector<int> cardinalAdjacent(int target_x, int target_y, int caller_x, int caller_y, int crossDistance);



private:
    int visualTile(int x, int y);
};
