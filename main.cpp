#pragma once

#include <iostream>
#include <string>
#include <array>
#include <random>
using namespace std;

bool running = true;
bool menu = true;
string start;

//creating random number generator
random_device rd;
mt19937 gen(rd());

vector<vector<int>> generate_maze()
{
//generate the map for the game
    //number code for square types: 0 = tunnel (can walk), 1 = wall (can't walk), 2 = exit (ends game if reached), 3 = skeleton, 4 = bomb, 5 = coin
    //number code for maze generation tile types: 0 = empty, 1 = up, 2 = right, 3 = down, 4 = left, 5 = dead end. If not 0, then not empty.
    constexpr int mapSize = 10;
    array<array<int, mapSize>, mapSize> tile_map{};
    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            tile_map[i][j] = 0;
        }
    }

    int number_of_tiles = mapSize * mapSize;
    uniform_int_distribution<int> dist0_14(0, 14);
    /*
    //generate x and y for the exit
    int exitX = dist0_15(gen);
    int exitY = dist0_15(gen);
    tile_map[exitX][exitY] = 2;
    */
    //vector to store the data about adjacent tiles
    vector<array<int, 2>> available;

    //stack and available choice
    int stackPos = 0;
    vector<array<int, 2>> stack;
    stack.push_back({0,0});

    int indice = 0;

    //current position components
    int current_x = 0;
    int current_y = 0;

    //new position components
    int new_x = 0;
    int new_y = 0;

    int debug = tile_map[current_x + 1][current_y];
    cout << "\n" << debug;

    //generate a maze
    //less than since condition will be true for the last iteration where size(stack) becomes = number_of_tiles during the iteration, thus completing the tile map
    int generated = 0;

    //-1 since the last remaining zero tile should be the entrance to the maze
    while (generated < number_of_tiles)
    {
        //pick an adjacent tile that hasn't been visited
        //if there isn't an unvisited tile adjacent, move backwards through stack by 1 entry
        //move in that direction, set previous tile to direction traveled to reach current tile
        //add tile coordinates to stack

        //check if the four cardinal directions are possible
        //check the possible cardinally adjacent tiles are empty
        if (current_y - 1 >= 0)
        {
            if (tile_map[current_x][current_y - 1] == 0)
            {
              available.push_back({current_x, current_y - 1});
            }
        }
        if (current_x + 1 < mapSize)
        {
            if (tile_map[current_x + 1][current_y] == 0)
            {
                available.push_back({current_x + 1, current_y});
            }
        }
        if (current_y + 1 < mapSize)
        {
            if (tile_map[current_x][current_y + 1] == 0)
            {
                available.push_back({current_x, current_y + 1});
            }
        }
        if (current_x - 1 >= 0)
        {
             if (tile_map[current_x - 1][current_y] == 0)
            {
                available.push_back({current_x - 1, current_y});
            }
        }

        if (size(available) == 0)
        {
            //move backwards in the stack of visited tiles by one if the available vector is empty
            //having an error where the code is defaulting to executing the stack move back command on the first iteration even when the stack is empty
            //one likely explanation is that the code is not properly determining whether there are cardinally adjacent free tiles available

            //dead-end at current position if no cardinally adjacent tiles available
            //only set equal to five if current position has a value of zero, prevents overwriting previous movements at tiles
            if (tile_map[current_x][current_y] == 0) tile_map[current_x][current_y] = 5;

            stackPos -= 1;
            current_x = stack[stackPos][0];
            current_y = stack[stackPos][1];
        } else if (size(available) != 0)
        {
            //create a new random number distribution based on the size of the available vector
            uniform_int_distribution<int> distAvailable(0, size(available) - 1);
            indice = distAvailable(gen);

            new_x = available[indice][0];
            new_y = available[indice][1];

            //set direction for current tile based on location of new tile
            if (new_x - current_x > 0) tile_map[current_x][current_y] = 2; //right
            if (new_x - current_x < 0) tile_map[current_x][current_y] = 4; //left
            if (new_y - current_y > 0) tile_map[current_x][current_y] = 3; //down
            if (new_y - current_y < 0) tile_map[current_x][current_y] = 1; //up

            //after direction is written to the tile map, add new coordinates to the stack
            //there was an issue with the map being generated half empty that I think was caused by the "current" coordinates being added to the stack
            stack.push_back({new_x, new_y});

            //update stackPos to reflect new tile count
            stackPos = size(stack) - 1;

            current_x = new_x;
            current_y = new_y;

        }
        //checks how many tiles are generated after each loop
        //plus 1 since (0, 0) or first coordinate is added immediately after initialization
        generated = 0;
        for (int x = 0; x < mapSize; x++)
        {
            for (int y = 0; y< mapSize; y++)
            {
                if (tile_map[x][y] != 0)
                {
                    generated += 1;
                }
            }
        }

        //clear available vector before use in next iteration
        available.clear();
    cout << "\n" << generated;
    }

    cout << "\n" << generated;

    //loops to print the tile map when finished
    cout << "\n";
    for (int y = 0; y < mapSize; y++)
    {
        for (int x = 0; x < mapSize; x++)
        {
            int value = tile_map.at(x).at(y);
            if (value == 0)
            {
                cout << "s" << "  ";
            } else if (value == 1)
            {
                cout << "^" << "  ";
            } else if (value == 2)
            {
                cout << ">" << "  ";
            } else if (value == 3)
            {
                cout << "v" << "  ";
            } else if (value == 4)
            {
                cout << "<" << "  ";
            } else if (value == 5)
            {
                cout << "e" << "  ";
            } else if (value == 6)
            {
                cout << "!" << "  ";
            }

            //cout << tile_map[x][y] << "  ";
        }
        cout << "\n";
    }

    //for loops to create return vector so maze can be used elsewhere
    vector<int> y_values;
    vector<vector<int>> generated_maze;
    for (int x = 0; x < mapSize; x++)
    {
        for (int y = 0; y < mapSize; y++)
        {
            y_values.push_back(tile_map.at(x).at(y));
        }
        generated_maze.push_back(y_values);
    }

    return generated_maze;
}



int main() {
    //menu to start game
    while (menu)
    {
        cout << "Welcome to Bombs N' Bones!\nThis is a simple text-based dungeon crawler\nWould you like to play?\n(y/n)"; cin >> start;
        if (start[0] == 'y') {printf("start"); menu = false;} if (start[0] == 'n') {printf("quit"); menu = false; running = false;}
    }

    vector<vector<int>> maze = generate_maze();

    //generate_map(maze) returns vector of generated map with all starting locations for different game objects
    //probably should implement this with a class and methods so it's more flexible

/*
    //transform the tiles into map coordinates
    while (generated < tiles)
    {
        //generate a 3*3 set of "squares" or "pixels" with walkable tiles spaces along the center
        //check previous direction and next direction
        //if previous direction and next direction same as current direction, create a straight 3*3 tile
        //if previous direction is different, create the appropriate "corner" 3*3 tile for next direction
        //this is so that the game avoids bridging maze paths together and defeating the point of the maze
    }

    //for the different objects (money, bombs, skeletons), iterate through the entire map and create a vector containing the empty, walkable spaces
    //do this prior to generating the locations of each type of object
    //then randomly select numbers within the range of the number of free spaces
    //after each number is generated, place the appropriate item there and remove it from the list

     place money
    int money = 0;
    while (money < 50)
    {
        int moneyX = dist0_99(gen);
        int moneyY = dist0_99(gen);
        if map[]
        money += 1;
    } */
    return 0;
};