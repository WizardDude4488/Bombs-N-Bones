#pragma once
#include <array>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <tuple>
#include <algorithm>
using namespace std;

class maze
{
public:
    maze();
    vector<vector<int>> generate_maze(int mazeSizeInt);

    void newHud();
};
