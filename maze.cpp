#include "maze.h"

#include <array>
#include <iostream>
#include <random>
#include <string>
#include <algorithm>
using namespace std;


random_device rd;
mt19937 gen(rd());

maze::maze() {}

void maze::newHud()
{
    //hud (3*3 grid, instructions for actions, place to enter letter for action)
    //printf(hud);
    //update positions and quantities
    cout << "\n" << visualTile(player_x - 1, player_y - 1) << "  "
    << visualTile(player_x, player_y - 1) << "  "
    << visualTile(player_x + 1, player_y - 1) << "     Enter one command at a time. Or, you can string together up to three commands using a single string, such" << "\n"
    << visualTile(player_x - 1, player_y) << "  "
    << visualTile(player_x, player_y) << "  "
    << visualTile(player_x + 1, player_y) << "     as 'aeq.' Use wasd to move, e to pickup or interact, and q to attack." "\n"
    << visualTile(player_x - 1, player_y + 1) << "  "
    << visualTile(player_x, player_y + 1) << "  "
    << visualTile(player_x + 1, player_y + 1) << "     Health: " << player_health << " " << "Money: " << player_money;
};

int maze::visualTile(int x, int y) {
    tile currentTile = generated_maze.at(x).at(y);
    int value = 0;
    if (currentTile.base == 1) {
        value = 1;
    } else if (currentTile.base == 0) {
        if (currentTile.skeleton) {
            value = 4;
        } else if (currentTile.exit) {
            value = 3;
        } else if (currentTile.money) {
            value = 2;
        } else {
            value = 0;
        }
    }

    return value;
}

void maze::action(string command)
{
    //using the older version || operator for compatibility
    //'' used to specify chars, "" used to specify string. Not interchangeable since the two are distinct data types
    //need to account for varying string length
    for (int i = 0; i < size(command) && i < 3; i++) {
        if (command[i] == 'e') {
            if (generated_maze.at(player_x).at(player_y).money) {
                //increment money, set tile to normal path
                player_money += 1;
                generated_maze.at(player_x).at(player_y).money = false;
            } if (generated_maze.at(player_x).at(player_y).exit) {
                exitFound = true;
            }
        } else if (command[i] == 'a') {
            if (generated_maze.at(player_x - 1).at(player_y).base != 1) {
                player_x -= 1;
            } else {
                cout << "\n" << "You can't move there! Try doing something else." << "\n";
            }
        } else if (command[i] == 'w') {
            if (generated_maze.at(player_x).at(player_y - 1).base != 1) {
                player_y -= 1;
            } else {
                cout << "\n" << "You can't move there! Try doing something else." << "\n";
            }
        } else if (command[i] == 'd') {
            if (generated_maze.at(player_x + 1).at(player_y).base != 1) {
                player_x += 1;
            } else {
                cout << "\n" << "You can't move there! Try doing something else." << "\n";
            }
        } else if (command[i] == 's') {
            if (generated_maze.at(player_x).at(player_y + 1).base != 1) {
                player_y += 1;
            } else {
                cout << "\n" << "You can't move there! Try doing something else." << "\n";
            }
        } else if (command[i] == 'q') {
            if (generated_maze.at(player_x).at(player_y + 1).skeleton) {
                skeleton current;
                current.x = player_x, current.y = player_y + 1;
                auto it = std::ranges::find(skeletonList, current);
                int index = distance(skeletonList.begin(), it);
                skeletonList[index].health -= 1;
                cout << "\n" << "skeleton hurt";
            }
            if (generated_maze.at(player_x).at(player_y).skeleton) {
                skeleton current;
                current.x = player_x, current.y = player_y;
                auto it = std::ranges::find(skeletonList, current);
                int index = distance(skeletonList.begin(), it);
                skeletonList[index].health -= 1;
                cout << "\n" << "skeleton hurt";
            }
            if (generated_maze.at(player_x).at(player_y - 1).skeleton) {
                skeleton current;
                current.x = player_x, current.y = player_y - 1;
                auto it = std::ranges::find(skeletonList, current);
                int index = distance(skeletonList.begin(), it);
                skeletonList[index].health -= 1;
                cout << "\n" << "skeleton hurt";
            }
            if (generated_maze.at(player_x - 1).at(player_y).skeleton) {
                skeleton current;
                current.x = player_x - 1, current.y = player_y;
                auto it = std::ranges::find(skeletonList, current);
                int index = distance(skeletonList.begin(), it);
                skeletonList[index].health -= 1;
                cout << "\n" << "skeleton hurt";
            }
            if (generated_maze.at(player_x + 1).at(player_y).skeleton) {
                skeleton current;
                current.x = player_x + 1, current.y = player_y;
                auto it = std::ranges::find(skeletonList, current);
                int index = distance(skeletonList.begin(), it);
                skeletonList[index].health -= 1;
                cout << "\n" << "skeleton hurt";
            }
        }
        else {
            cout << "\n" << "Invalid action." << "\n";
        }

    }

}

void maze::updateSkeletons() {
    for (int i = 0; i < size(skeletonList); i++) {
        //calculate available tiles
        skeleton current = skeletonList[i];

        //two available actions in string
        for (int j = 0; j < 2; j++) {
            //remove from list if health == 0
            if (skeletonList[i].health == 0) {
                std::erase(skeletonList, current);
                generated_maze.at(current.x).at(current.y).skeleton = false;
                cout << "\n" << "skeleton killed";
            }

            //need to check for player adjacency
            if ((current.x == player_x && current.y == player_y) ||
                (current.x + 1 == player_x && current.y == player_y) ||
                (current.x - 1 == player_x && current.y == player_y) ||
                (current.x == player_x && current.y + 1 == player_y) ||
                (current.x == player_x && current.y - 1 == player_y)) {
                player_health -= 1;
                } else {
                    vector<vector<int>> available;
                    //iterate through actions list twice

                    if (generated_maze.at(current.x).at(current.y - 1).base == 0)
                    {
                        available.push_back({current.x, current.y - 1});
                    }
                    if (generated_maze.at(current.x + 1).at(current.y).base == 0)
                    {
                        available.push_back({current.x + 1, current.y});
                    }
                    if (generated_maze.at(current.x).at(current.y + 1).base == 0)
                    {
                        available.push_back({current.x, current.y + 1});
                    }
                    if (generated_maze.at(current.x - 1).at(current.y).base == 0) {
                        available.push_back({current.x - 1, current.y});
                    }

                    uniform_int_distribution<> distAvailable(0, size(available) - 1);
                    int option = 0;
                    option = distAvailable(gen);
                    generated_maze.at(current.x).at(current.y).skeleton = false;

                    //need to modify the actual struct, not just a variable that is based on it
                    skeletonList[i].x = available.at(option).at(0);
                    skeletonList[i].y = available.at(option).at(1);
                    generated_maze.at(skeletonList[i].x).at(skeletonList[i].y).skeleton = true;

                }
        }
    }
}

vector<vector<maze::tile>> maze::generate_maze(int mazeSizeInt) {
    //generate the maze for the game
    //number code for square types: 0 = tunnel (can walk), 1 = wall (can't walk), 2 = exit (ends game if reached), 3 = skeleton, 4 = bomb, 5 = coin
    //number code for maze generation tile types: 0 = empty, 1 = up, 2 = right, 3 = down, 4 = left, 5 = dead end, 6 = boundary. If not 0, then not empty.//"mazeSizeInt" internal maze size
    mazeSizeExt = mazeSizeInt + 2; //external is internal plus one boundary tile on each side for both dimensions, so plus two
    vector<vector<int>> tile_maze{};
    vector<int> tile_maze_y;

    for (int i = 0; i < mazeSizeExt; i++)
    {
        for (int j = 0; j < mazeSizeExt; j++)
        {
            tile_maze_y.push_back(1);
        }
        tile_maze.push_back(tile_maze_y);
        tile_maze_y.clear();
    }

    //want to use mazeSizeInt (internal) since the maze won't generate at edges, only interior
    int number_of_tiles = mazeSizeExt * mazeSizeExt;

    //vector to store the data about adjacent tiles
    vector<array<int, 2>> available;

    //stack and available choice
    int stackPos = 0;
    vector<array<int, 2>> stack;
    stack.push_back({0,0});

    int indice = 0;

    //current position components
    int current_x = 1;
    int current_y = 1;

    //generate a maze
    //less than since condition will be true for the last iteration where size(stack) becomes = number_of_tiles during the iteration, thus completing the tile map
    int generated = 0;
    vector<int> failed;

    //-1 since the last remaining zero tile should be the entrance to the maze
    while (generated < floor(0.4 * number_of_tiles))
    {
        //pick an adjacent tile that hasn't been visited
        //if there isn't an unvisited tile adjacent, move backwards through stack by 1 entry
        //move in that direction, set previous tile to direction traveled to reach current tile
        //add tile coordinates to stack

        //check if the four cardinal directions are possible
        //check the possible cardinally adjacent tiles are empty
        //up
        if (current_y > 1)
        {
            if (tile_maze[current_x][current_y - 1] == 1
                && tile_maze[current_x][current_y - 2] == 1
                && tile_maze[current_x - 1][current_y - 1] == 1
                && tile_maze[current_x + 1][current_y - 1] == 1)
            {
                available.push_back({current_x, current_y - 1});
            }
        }
        //right
        if (current_x < size(tile_maze) - 2)
        {
            if (tile_maze[current_x + 1][current_y] == 1
                && tile_maze[current_x + 2][current_y] == 1
                && tile_maze[current_x + 1][current_y - 1] == 1
                && tile_maze[current_x + 1][current_y + 1] == 1)
            {
                available.push_back({current_x + 1, current_y});
            }
        }
        //down
        if (current_y < size(tile_maze) - 2)
        {
            if (tile_maze[current_x][current_y + 1] == 1
                && tile_maze[current_x][current_y + 2] == 1
                && tile_maze[current_x - 1][current_y + 1] == 1
                && tile_maze[current_x + 1][current_y + 1] == 1)
            {
                available.push_back({current_x, current_y + 1});
            }
        }
        //left
        if (current_x > 1)
        {
            if (tile_maze[current_x - 1][current_y] == 1
                && tile_maze[current_x - 2][current_y] == 1
                && tile_maze[current_x - 1][current_y - 1] == 1
                && tile_maze[current_x - 1][current_y + 1] == 1)
            {
                available.push_back({current_x - 1, current_y});
            }
        }

        if (size(available) == 0)
        {
            //move backwards in the stack of visited tiles by one if the available vector is empty
            //having an error where the code is defaulting to executing the stack move back command on the first iteration even when the stack is empty
            //one likely explanation is that the code is not properly determining whether there are cardinally adjacent free tiles available
            if (stackPos < 1) break;
            stackPos -= 1;
            current_x = stack[stackPos][0];
            current_y = stack[stackPos][1];
            failed.push_back(1);
        } else if (size(available) != 0)
        {
            //create a new random number distribution based on the size of the available vector
            uniform_int_distribution<int> distAvailable(0, size(available) - 1);
            indice = distAvailable(gen);

            current_x = available[indice][0];
            current_y = available[indice][1];

            //set current tile equal to zero
            tile_maze[current_x][current_y] = 0;

            //after direction is written to the tile map, add new coordinates to the stack
            //there was an issue with the map being generated half empty that I think was caused by the "current" coordinates being added to the stack
            stack.push_back({current_x, current_y});

            //update stackPos to reflect new tile count
            stackPos = size(stack) - 1;

            //clear failed list
            failed.clear();
        }
        //checks how many tiles are generated after each loop
        //plus 1 since (0, 0) or first coordinate is added immediately after initialization
        generated = 0;

        for (int x = 0; x < mazeSizeExt; x++)
        {
            generated += count(tile_maze[x].begin(), tile_maze[x].end(), 0);
        }

        //clear available vector before use in next iteration
        available.clear();
        //if number of failed attempts gets bigger than stack, stop generation
        if (size(failed) > generated) break;

        cout << "\n" << generated;
    }

    cout << "\n" << generated;

    //for loops to generate tile vector
    vector<tile> yRowTiles;
    for (int x = 0; x < mazeSizeExt; x++)
    {
        for (int y = 0; y < mazeSizeExt; y++)
        {
            tile currentTile;
            currentTile.base = tile_maze.at(x).at(y);
            yRowTiles.push_back(currentTile);
        }
        generated_maze.push_back(yRowTiles);
        //clear before using again
        yRowTiles.clear();
    }


    //create a list of available (walkable) tiles for generating the exit, money, skeletons and bombs
    vector<vector<int>> walkable;

    for (int x = 0; x < mazeSizeExt; x++) {
        for (int y = 0; y < mazeSizeExt; y++) {
            if (generated_maze.at(x).at(y).base == 0) {
                walkable.push_back({x, y});
            }
        }
    }
    //cout << "\nDebug: Walkable calculation succeeded." << "\n";

    //generate x and y for the exit
    uniform_int_distribution<> exitDistWalkable(1, size(walkable));
    int exit = exitDistWalkable(gen);

    int exitX = walkable.at(exit).at(0);
    int exitY = walkable.at(exit).at(1);
    generated_maze.at(exitX).at(exitY).exit = true;

    //remove the point where the exit was generated
    walkable.erase(walkable.begin() + exit);

    //generated x and y for the entrance
    uniform_int_distribution<> entranceDistWalkable(1, size(walkable));
    int entrance = entranceDistWalkable(gen);

    int entranceX = walkable.at(entrance).at(0);
    int entranceY = walkable.at(entrance).at(1);
    player_x = entranceX;
    player_y = entranceY;

    //generate money locations
    for (int positions = 0; positions < 0.15 * size(walkable); positions++) {
        uniform_int_distribution<> moneyDistWalkable(1, size(walkable));
        int listPos = moneyDistWalkable(gen);
        int moneyX = walkable.at(listPos).at(0);
        int moneyY = walkable.at(listPos).at(1);
        generated_maze.at(moneyX).at(moneyY).money = true;
        walkable.erase(walkable.begin() + listPos);
    }

    //generate initial skeleton locations
    for (int positions = 0; positions < 0.06 * size(walkable); positions++) {
        uniform_int_distribution<> moneyDistWalkable(1, size(walkable));
        int listPos = moneyDistWalkable(gen);
        skeleton current;
        current.x = walkable.at(listPos).at(0);
        current.y = walkable.at(listPos).at(1);
        //add skeleton at chosen position to list
        skeletonList.push_back(current);
        //update tile information
        generated_maze.at(current.x).at(current.y).skeleton = true;
        walkable.erase(walkable.begin() + listPos);
    }

    return generated_maze;
}


    //loops to print the tile map when finished
void maze::printMaze() {
    cout << "\n";
    for (int y = 0; y < mazeSizeExt; y++)
    {
        for (int x = 0; x < mazeSizeExt; x++)
        {
            int value = 0;
            value = visualTile(x, y);

            if (value == 0) {
                cout << "0" << "  ";
            } else if (value == 1) {
                cout << "1" << "  ";
            } else if (value == 2) {
                cout << "2" << "  ";
            } else if (value == 3) {
                cout << "3" << "  ";
            } else if (value == 4) {
                cout << "4" << "  ";
            } else {
                cout << "!" << "  ";
            }
        }
        cout << "\n";
    }
}


