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

void generate_map()
{

}



int main() {
    //menu to start game
    while (menu)
    {
        cout << "Welcome to Bombs N' Bones!\nThis is a simple text-based dungeon crawler\nWould you like to play?\n(y/n)"; cin >> start;
        if (start[0] == 'y') {printf("start"); menu = false;} if (start[0] == 'n') {printf("quit"); menu = false; running = false;}
    }
    //generate the map for the game
    //number code for square types: 0 = tunnel (can walk), 1 = wall (can't walk), 2 = exit (ends game if reached), 3 = skeleton, 4 = bomb, 5 = coin
    //number code for maze generation tile types: 0 = empty, 1 = generated
    constexpr int size = 15;
    array<array<int, size>, size> tile_map{};
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            tile_map[i][j] = 0;
        }
    }

    int number_of_tiles = 15 * 15;
    uniform_int_distribution<int> dist0_15(0, 15);

    //generate x and y for the exit
    int exitX = dist0_15(gen);
    int exitY = dist0_15(gen);
    tile_map[exitX][exitY] = 2;

    //list of visited tiles
    //visited[0][0] returns the x coordinate of the zeroeth tile visited
    vector<array<int, 2>> visited;
    visited[0] = {exitX, exitY};

    //vector to store the data about adjacent tiles
    vector<array<int, 2>> available;

    //generate a maze
    while (size(visited) <= number_of_tiles)
    {
        //start at previous location (exit for first iteration)
        //pick an adjacent tile that hasn't been visited
        //if there isn't an unvisited tile adjacent, move backwards through stack by 1 entry
        //move in that direction, set previous tile to direction traveled to reach current tile
        //add tile coordinates to stack
        
        //check adjacent squares


    }

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

    /*place money
    int money = 0;
    while (money < 50)
    {
        int moneyX = dist0_99(gen);
        int moneyY = dist0_99(gen);
        if map[]
        money += 1;
    }*/


    //while loop for the game
    while (running)
    {
    }
};