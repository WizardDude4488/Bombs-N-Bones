#pragma once

#include <array>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <tuple>
#include <algorithm>
#include "maze.h"
using namespace std;

bool playing = true;
bool menu = true;
bool leaveMaze = true;
string start;

maze Maze;

int main() {
    //menu to start game
    while (menu)
    {
        cout << "Welcome to Bombs N' Bones!\nThis is a simple text-based dungeon crawler\nWould you like to play?\n(y/n)"; cin >> start;
        if (start[0] == 'y') {printf("start"); menu = false;} if (start[0] == 'n') {printf("quit"); menu = false; playing = false;}
    }

    Maze.generate_maze(20);

    //probably should implement this with a class and methods so it's more flexible

    while (playing)
    {
        //hud (3*3 grid, instructions for actions, place to enter letter for action)
        //printf(hud);
        //update positions and quantities

        //end game once exit reached
        if (leaveMaze)
        {
            playing = false;
        }
    }

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