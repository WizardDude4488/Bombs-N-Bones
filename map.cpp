#include "map.h"

//constructor
MapGen::MapGen()
{
    //1st int is number of current tile, 2nd int is number of adjacent tile, 3rd int is integer code for direction adjacent tile is from current tile
    //valid numbers for current tiles are 1-5 (inclusive)
    //not checking current tile == 6 since that's just boundary
    mapLookupTable[{0,0,0}] = 0;
    mapLookupTable[{1,6,1}] = 1;
    mapLookupTable[{2,6,1}] = 1;
    mapLookupTable[{3,6,1}] = 1;
    mapLookupTable[{4,6,1}] = 1;
    mapLookupTable[{5,6,1}] = 1;
    mapLookupTable[{1,6,2}] = 1;
    mapLookupTable[{2,6,2}] = 1;
    mapLookupTable[{3,6,2}] = 1;
    mapLookupTable[{4,6,2}] = 1;
    mapLookupTable[{5,6,2}] = 1;
    mapLookupTable[{4,1}] = 1;
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
    auto key = make_tuple(0,0, 0);
    //default value for iterator, commonly named "it" in C++
    auto it = mapLookupTable.find(key);

    //vector for finished map
    vector<vector<int>> finishedMap;

    for (int maze_x = 0; maze_x < size(maze); maze_x++)
    {
        for (int maze_y = 0; maze_y < size(maze); maze_y++)
        {
            //default map square
            vector<vector<int>> map_tile{{1,1,1}, {1,0,1}, {1,1,1}};

            //blah
            //controls map square cardinal left from center
            if (maze.at(maze_x).at(maze_y) == 6)
            {
                //modify so tile is all 1s
                map_tile.at(1).at(1) = 1;

            } else
            {
                //up
                key = make_tuple(maze.at(maze_x).at(maze_y), maze.at(maze_x).at(maze_y - 1));
                map_tile[1][0] = it->second;
                //right
                key = make_tuple(maze.at(maze_x).at(maze_y), maze.at(maze_x + 1).at(maze_y));
                map_tile[2][1] = it->second;
                //down
                key = make_tuple(maze.at(maze_x).at(maze_y), maze.at(maze_x).at(maze_y + 1));
                map_tile[1][2] = it->second;
                //left
                key = make_tuple(maze.at(maze_x).at(maze_y), maze.at(maze_x - 1).at(maze_y));
                map_tile[0][1] = it->second;
            }

            //pastes each finished tile onto the final map
            for (int map_x = 0; map_x < size(map_tile); map_x++)
            {
                for (int map_y = 0; map_y < size(map_tile); map_y++)
                {
                    finishedMap.at(map_x).at(map_y) = map_tile[map_x][map_y];
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
