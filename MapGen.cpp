#include "MapGen.h"

//constructor
MapGen::MapGen()
{
    //1st int is number of current tile, 2nd int is number of adjacent tile, 3rd int is integer code for direction adjacent tile is from current tile
    //valid numbers for current tiles are 1-5 (inclusive) (1 = up, 2 = right, 3 = down, 4 = left, 5 = dead end, 6 = boundary)
    //rule is that any time a tile points directly into another, except for boundary tiles, it leaves a blank at the relevant spaces, allowing the maze to be preserved
    //default here for key initialization
    mapLookupTable[{0,0,0}] = 0;
    //for adjacent tile == 6
    mapLookupTable[{1,6,1}] = 1;
    mapLookupTable[{2,6,1}] = 1;
    mapLookupTable[{3,6,1}] = 1;
    mapLookupTable[{4,6,1}] = 1;
    mapLookupTable[{5,6,1}] = 1;
    mapLookupTable[{6,6,1}] = 1;
    mapLookupTable[{1,6,2}] = 1;
    mapLookupTable[{2,6,2}] = 1;
    mapLookupTable[{3,6,2}] = 1;
    mapLookupTable[{4,6,2}] = 1;
    mapLookupTable[{5,6,2}] = 1;
    mapLookupTable[{6,6,2}] = 1;
    mapLookupTable[{1,6,3}] = 1;
    mapLookupTable[{2,6,3}] = 1;
    mapLookupTable[{3,6,3}] = 1;
    mapLookupTable[{4,6,3}] = 1;
    mapLookupTable[{5,6,3}] = 1;
    mapLookupTable[{6,6,3}] = 1;
    mapLookupTable[{1,6,4}] = 1;
    mapLookupTable[{2,6,4}] = 1;
    mapLookupTable[{3,6,4}] = 1;
    mapLookupTable[{4,6,4}] = 1;
    mapLookupTable[{5,6,4}] = 1;
    mapLookupTable[{6,6,4}] = 1;
    //for adjacent tile == 5
    mapLookupTable[{1,5,1}] = 0;
    mapLookupTable[{2,5,1}] = 1;
    mapLookupTable[{3,5,1}] = 0;
    mapLookupTable[{4,5,1}] = 1;
    mapLookupTable[{5,5,1}] = 1;
    mapLookupTable[{6,5,1}] = 1;
    mapLookupTable[{1,5,2}] = 1;
    mapLookupTable[{2,5,2}] = 0;
    mapLookupTable[{3,5,2}] = 1;
    mapLookupTable[{4,5,2}] = 0;
    mapLookupTable[{5,5,2}] = 1;
    mapLookupTable[{6,5,2}] = 1;
    mapLookupTable[{1,5,3}] = 0;
    mapLookupTable[{2,5,3}] = 1;
    mapLookupTable[{3,5,3}] = 0;
    mapLookupTable[{4,5,3}] = 1;
    mapLookupTable[{5,5,3}] = 1;
    mapLookupTable[{6,5,3}] = 1;
    mapLookupTable[{1,5,4}] = 1;
    mapLookupTable[{2,5,4}] = 0;
    mapLookupTable[{3,5,4}] = 1;
    mapLookupTable[{4,5,4}] = 0;
    mapLookupTable[{5,5,4}] = 1;
    mapLookupTable[{6,5,4}] = 1;
    //for adjacent tile == 4
    mapLookupTable[{1,4,1}] = 0;
    mapLookupTable[{2,4,1}] = 1;
    mapLookupTable[{3,4,1}] = 0;
    mapLookupTable[{4,4,1}] = 1;
    mapLookupTable[{5,4,1}] = 1;
    mapLookupTable[{6,4,1}] = 1;
    mapLookupTable[{1,4,2}] = 0;
    mapLookupTable[{2,4,2}] = 0;
    mapLookupTable[{3,4,2}] = 0;
    mapLookupTable[{4,4,2}] = 0;
    mapLookupTable[{5,4,2}] = 0;
    mapLookupTable[{6,4,2}] = 1;
    mapLookupTable[{1,4,3}] = 0;
    mapLookupTable[{2,4,3}] = 1;
    mapLookupTable[{3,4,3}] = 0;
    mapLookupTable[{4,4,3}] = 1;
    mapLookupTable[{5,4,3}] = 1;
    mapLookupTable[{6,4,3}] = 1;
    mapLookupTable[{1,4,4}] = 1;
    mapLookupTable[{2,4,4}] = 1;
    mapLookupTable[{3,4,4}] = 1;
    mapLookupTable[{4,4,4}] = 0;
    mapLookupTable[{5,4,4}] = 1;
    mapLookupTable[{6,4,4}] = 1;
    //for adjacent tile == 3
    mapLookupTable[{1,3,1}] = 0;
    mapLookupTable[{2,3,1}] = 0;
    mapLookupTable[{3,3,1}] = 0;
    mapLookupTable[{4,3,1}] = 0;
    mapLookupTable[{5,3,1}] = 0;
    mapLookupTable[{6,3,1}] = 1;
    mapLookupTable[{1,3,2}] = 1;
    mapLookupTable[{2,3,2}] = 0;
    mapLookupTable[{3,3,2}] = 1;
    mapLookupTable[{4,3,2}] = 1;
    mapLookupTable[{5,3,2}] = 1;
    mapLookupTable[{6,3,2}] = 1;
    mapLookupTable[{1,3,3}] = 0;
    mapLookupTable[{2,3,3}] = 1;
    mapLookupTable[{3,3,3}] = 0;
    mapLookupTable[{4,3,3}] = 0;
    mapLookupTable[{5,3,3}] = 1;
    mapLookupTable[{6,3,3}] = 1;
    mapLookupTable[{1,3,4}] = 1;
    mapLookupTable[{2,3,4}] = 1;
    mapLookupTable[{3,3,4}] = 1;
    mapLookupTable[{4,3,4}] = 0;
    mapLookupTable[{5,3,4}] = 1;
    mapLookupTable[{6,3,4}] = 1;
    //for adjacent tile == 2
    mapLookupTable[{1,2,1}] = 0;
    mapLookupTable[{2,2,1}] = 1;
    mapLookupTable[{3,2,1}] = 1;
    mapLookupTable[{4,2,1}] = 1;
    mapLookupTable[{5,2,1}] = 1;
    mapLookupTable[{6,2,1}] = 1;
    mapLookupTable[{1,2,2}] = 1;
    mapLookupTable[{2,2,2}] = 0;
    mapLookupTable[{3,2,2}] = 1;
    mapLookupTable[{4,2,2}] = 1;
    mapLookupTable[{5,2,2}] = 1;
    mapLookupTable[{6,2,2}] = 1;
    mapLookupTable[{1,2,3}] = 1;
    mapLookupTable[{2,2,3}] = 1;
    mapLookupTable[{3,2,3}] = 0;
    mapLookupTable[{4,2,3}] = 1;
    mapLookupTable[{5,2,3}] = 1;
    mapLookupTable[{6,2,3}] = 1;
    mapLookupTable[{1,2,4}] = 0;
    mapLookupTable[{2,2,4}] = 0;
    mapLookupTable[{3,2,4}] = 0;
    mapLookupTable[{4,2,4}] = 1;
    mapLookupTable[{5,2,4}] = 0;
    mapLookupTable[{6,2,4}] = 1;
    //for adjacent tile == 1
    mapLookupTable[{1,1,1}] = 0;
    mapLookupTable[{2,1,1}] = 1;
    mapLookupTable[{3,1,1}] = 0;
    mapLookupTable[{4,1,1}] = 1;
    mapLookupTable[{5,1,1}] = 1;
    mapLookupTable[{6,1,1}] = 1;
    mapLookupTable[{1,1,2}] = 1;
    mapLookupTable[{2,1,2}] = 0;
    mapLookupTable[{3,1,2}] = 1;
    mapLookupTable[{4,1,2}] = 0;
    mapLookupTable[{5,1,2}] = 1;
    mapLookupTable[{6,1,2}] = 1;
    mapLookupTable[{1,1,3}] = 0;
    mapLookupTable[{2,1,3}] = 0;
    mapLookupTable[{3,1,3}] = 0;
    mapLookupTable[{4,1,3}] = 0;
    mapLookupTable[{5,1,3}] = 0;
    mapLookupTable[{6,1,3}] = 1;
    mapLookupTable[{1,1,4}] = 1;
    mapLookupTable[{2,1,4}] = 1;
    mapLookupTable[{3,1,4}] = 1;
    mapLookupTable[{4,1,4}] = 0;
    mapLookupTable[{5,1,4}] = 1;
    mapLookupTable[{6,1,4}] = 1;


}

//method to set probabilities
void MapGen::set_probabilities(int skeletons, int bombs, int money)
{
    skeleton_probability = skeletons;
    bomb_probability = bombs;
    money_probability = money;
}

//method to generate map
void MapGen::generate_map(vector<vector<int>> maze)
{
    //change x value in outer for loop
    //change y value in inner for loop
    //check to see if adjacent tiles are out of bounds, if so, don't check tile type
    //if an adjacent tile type is in bounds, compare it with the current tile type to determine what the (up/right/down/left) square in tile should be

    //generates a new key for searching the lookup table
    auto key = make_tuple(0,0,0);
    //default value for iterator, commonly named "it" in C++
    auto it = mapLookupTable.find(key);
    vector<int> y_values;

    //vector for finished map
    for (int map_x = 0; map_x < 3*size(maze); map_x++)
    {
        for (int map_y = 0; map_y < 3*size(maze); map_y++)
        {
            y_values.push_back(0);
        }
        finished_map.push_back(y_values);
        y_values.clear();
    }

    for (int maze_x = 0; maze_x < size(maze); maze_x++)
    {
        for (int maze_y = 0; maze_y < size(maze); maze_y++)
        {
            //default map square
            vector<vector<int>> map_tile{{1,1,1}, {1,0,1}, {1,1,1}};

            //can remove the if else statement since current tile == 6 is always set to 1 in the code
            //controls map square cardinal left from center
            if (maze.at(maze_x).at(maze_y) == 6)
            {
                //modify so tile is all 1s
                map_tile.at(1).at(1) = 1;

            }
            //code: (current tile value, adjacent tile value, adjacent tile direction
            //up
            if (maze_y > 0)
            {
                key = make_tuple(maze.at(maze_x).at(maze_y), maze.at(maze_x).at(maze_y - 1), 1);
                it = mapLookupTable.find(key);
                map_tile[1][0] = it->second;
            }
            //right
            if (maze_x < size(maze) - 1)
            {
                key = make_tuple(maze.at(maze_x).at(maze_y), maze.at(maze_x + 1).at(maze_y), 2);
                it = mapLookupTable.find(key);
                map_tile[2][1] = it->second;
            }
            //down
            if (maze_y < size(maze) - 1)
            {
                key = make_tuple(maze.at(maze_x).at(maze_y), maze.at(maze_x).at(maze_y + 1), 3);
                it = mapLookupTable.find(key);
                map_tile[1][2] = it->second;
            }
            //left
            if (maze_x > 0)
            {
                key = make_tuple(maze.at(maze_x).at(maze_y), maze.at(maze_x - 1).at(maze_y), 4);
                it = mapLookupTable.find(key);
                map_tile[0][1] = it->second;
            }

            //pastes each finished tile onto the final map
            for (int map_x = 0; map_x < size(map_tile); map_x++)
            {
                for (int map_y = 0; map_y < size(map_tile); map_y++)
                {
                    //add three times maze_x and 3 times maze_y to offset
                    //runs into an exception when trying to access finishedMap at this location
                    finished_map.at(map_x + 3*maze_x).at(map_y + 3*maze_y) = map_tile[map_x][map_y];
                }

            }

        }
    }
}

vector<vector<int>> MapGen::return_map()
{
    if (size(finished_map) != 0)
    {
        return finished_map;
    } else
    {
        vector<vector<int>> failed{0};
        printf("\nMap generation failed!");
        return failed;
    }
}
