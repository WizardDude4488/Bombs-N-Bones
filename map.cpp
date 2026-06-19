#include "map.h"

//constructor
map::map()
= default;

//method to set probabilities
void map::set_probabilities(int skeletons, int bombs, int money)
{
    skeleton_probability = skeletons;
    bomb_probability = bombs;
    money_probability = money;
}

//method to generate map
void map::generate_map(vector<vector<int>> maze)
{
    //change x value in outer for loop
    //change y value in inner for loop
    //check to see if adjacent tiles are out of bounds, if so, don't check tile type
    //if an adjacent tile type is in bounds, compare it with the current tile type to determine what the (up/right/down/left) square in tile should be
    for (int maze_x = 0; maze_x < size(maze); maze_x++)
    {
        for (int maze_y = 0; maze_y < size(maze); maze_y++)
        {
            //ensures values are zero by default
            vector<vector<int>> map_tile{{0,0,0}, {0,0,0}, {0,0,0}};
            int tile_x = 0;
            int tile_y = 0;
            //blah
            //controls map square cardinal left from center


        }
    }
}

vector<vector<int>> map::return_map()
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
