#include "maze.h"

#include <array>
#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;


random_device rd;
mt19937 gen(rd());

maze::maze() {}

void maze::newHud()
{
    //hud (3*3 grid, instructions for actions, place to enter letter for action)
    //printf(hud);
    //update positions and quantities
    cout << "\n" << visualTile(player_x - 2, player_y - 2) << "  " << visualTile(player_x - 1, player_y - 2) << "  " << visualTile(player_x, player_y - 2) << "  " << visualTile(player_x + 1, player_y - 2) << "  " << visualTile (player_x + 2, player_y - 2) << "     Enter one command at a time. Or, you can string together up to three commands using a single string,"
    << "\n" << visualTile(player_x - 2, player_y - 1) << "  " << visualTile(player_x - 1, player_y - 1) << "  " << visualTile(player_x, player_y - 1) << "  " << visualTile(player_x + 1, player_y - 1) << "  " << visualTile(player_x + 2, player_y - 1) << "     such as 'aeq.' Use wasd to move, e to pickup or interact, and q to attack."
    << "\n" << visualTile(player_x - 2, player_y) << "  " << visualTile(player_x - 1, player_y) << "  " << visualTile(player_x, player_y) << "  " << visualTile(player_x + 1, player_y) << "  " << visualTile(player_x + 2, player_y) << "     Health: " << player_health << " " << "Money: " << player_money
    << "\n" << visualTile(player_x - 2, player_y + 1) << "  " << visualTile(player_x - 1, player_y + 1) << "  " << visualTile(player_x, player_y + 1) << "  " << visualTile(player_x + 1, player_y + 1) << "  " << visualTile(player_x + 2, player_y + 1) << "     Recent message: " << message
    << "\n" << visualTile(player_x - 2, player_y + 2) << "  " << visualTile(player_x - 1, player_y + 2) << "  " << visualTile(player_x, player_y + 2) << "  " << visualTile(player_x + 1, player_y + 2) << "  " << visualTile(player_x + 2, player_y + 2);
};

char maze::visualTile(int x, int y) {
    tile currentTile = generated_maze.at(x).at(y);
    char value = '0';
    if (currentTile.base == 1) {
        value = '1';
    } else if (currentTile.base == 0) {
        if (currentTile.skeleton) {
            value = 's';
        } else if (currentTile.exit) {
            value = 'e';
        } else if (currentTile.money) {
            value = 'm';
        } else if (currentTile.bomb) {
            value = 'b';
        } else if (currentTile.health) {
            value = 'h';
        } else {
            value = '0';
        }
    }

    return value;
}
int maze::bombCheck(int caller_x, int caller_y) {
    uniform_int_distribution<> bombDamage(2, 5);
    int damage = 0;
    if (generated_maze.at(caller_x).at(caller_y).bomb) {
        damage = bombDamage(gen);
        generated_maze.at(caller_x).at(caller_y).bomb = false;
    }
    return damage;
}

vector<int> maze::cardinalAdjacent(int target_x, int target_y, int caller_x, int caller_y, int range = 0) {
    //takes in the target coordinates, the caller's coordinates, and the cross length to search on
    //returns a vector of (isAdjacent, distance, direction) for cross adjacency
    //0 = cross, 1 = square
    int distance = 0;
    int direction = 0;
    int withinRange = 0;

    if ((target_x == caller_x) ||
        (target_y == caller_y)) {

        if (abs(target_x - caller_x) != 0) {
            distance = abs(target_x - caller_y);
            if (target_x > caller_x) direction = 2;
            if (target_x < caller_x) direction = 4;
        }

        if (abs(target_y - caller_y) != 0) {
            distance = abs(target_y - caller_y);
            if (target_y > caller_y) direction = 3;
            if (target_y < caller_y) direction = 1;
        }

        if (abs(target_y - caller_y) != 0 && abs(target_x - caller_x) != 0) {
            distance = floor(sqrt(pow((target_x - caller_x),2) + pow((target_y - caller_y),2)));
        }

        if (abs(target_y - caller_y) == 0 && abs(target_x - caller_x) == 0) {
            distance = 0;
        }

        } else {
            distance = 1000;
            direction = 0;
        }


    if (range == 0) {
        withinRange = 1;
    } else {
        if (distance < range) withinRange = 1;
        if (distance > range) withinRange = 0;
    }

    //direction uses 1 = up, 2 = right, 3 = down, 4 = left standard
    return {distance, direction, withinRange};
}

vector<int> maze::targetFollow(int target_x = 0, int target_y = 0, int caller_x = 0, int caller_y = 0, int range = 0, char target = 'd') {
    int direction = 0;
    int withinRange = 0;
    int delta_x = 0;
    int delta_y = 0;
    vector<int> availableDirections;

    if (abs(target_y - caller_y) < range && abs(target_x - caller_x) < range) {
        withinRange = 1;
        if (target_x > caller_x) {
            if (generated_maze.at(caller_x + 1).at(caller_y).base == 0) {
                availableDirections.push_back(2);
            }
            if (generated_maze.at(caller_x + 1).at(caller_y + 1).base == 0 &&
                generated_maze.at(caller_x).at(caller_y + 1).base == 0) {
                availableDirections.push_back(3);
            }
            if (generated_maze.at(caller_x + 1).at(caller_y - 1).base == 0 &&
                generated_maze.at(caller_x).at(caller_y - 1).base == 0) {
                availableDirections.push_back(1);
            }
        }
        if (target_x < caller_x) {
            if (generated_maze.at(caller_x - 1).at(caller_y).base == 0) {
                availableDirections.push_back(4);
            }
            if (generated_maze.at(caller_x - 1).at(caller_y + 1).base == 0 &&
                generated_maze.at(caller_x).at(caller_y + 1).base == 0) {
                availableDirections.push_back(3);
                }
            if (generated_maze.at(caller_x - 1).at(caller_y - 1).base == 0 &&
                generated_maze.at(caller_x).at(caller_y - 1).base == 0) {
                availableDirections.push_back(1);
                }
        }

        if (target_y < caller_y) {
            if (generated_maze.at(caller_x).at(caller_y - 1).base == 0) {
                availableDirections.push_back(1);
            }
            if (generated_maze.at(caller_x - 1).at(caller_y - 1).base == 0 &&
                generated_maze.at(caller_x - 1).at(caller_y).base == 0) {
                availableDirections.push_back(4);
                }
            if (generated_maze.at(caller_x + 1).at(caller_y - 1).base == 0 &&
                generated_maze.at(caller_x + 1).at(caller_y).base == 0) {
                availableDirections.push_back(2);
                }
        }

        if (target_y > caller_y) {
            if (generated_maze.at(caller_x).at(caller_y + 1).base == 0) {
                availableDirections.push_back(3);
            }
            if (generated_maze.at(caller_x - 1).at(caller_y + 1).base == 0 &&
                generated_maze.at(caller_x - 1).at(caller_y).base == 0) {
                availableDirections.push_back(4);
                }
            if (generated_maze.at(caller_x + 1).at(caller_y + 1).base == 0 &&
                generated_maze.at(caller_x + 1).at(caller_y).base == 0) {
                availableDirections.push_back(2);
                }
        }
        uniform_int_distribution<> directions(0, size(availableDirections) - 1);
        int listPos = directions(gen);
        direction = availableDirections.at(listPos);
    }

    if (direction == 0) {
        delta_x = 0;
        delta_y = 0;
    } else if (direction == 1) {
        delta_x = 0;
        delta_y = -1;
    } else if (direction == 2) {
        delta_x = 1;
        delta_y = 0;
    } else if (direction == 3) {
        delta_x = 0;
        delta_y = 1;
    } else if (direction == 4) {
        delta_x = -1;
        delta_y = 0;
    }

    return {withinRange, delta_x, delta_y};
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
                cout << "\n\n\n\n\n\n\nYou escaped! You left with" << " " << player_money << " " << "money. Thanks for playing!";
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
                message = "skeleton hurt";
            }
            if (generated_maze.at(player_x).at(player_y).skeleton) {
                skeleton current;
                current.x = player_x, current.y = player_y;
                auto it = std::ranges::find(skeletonList, current);
                int index = distance(skeletonList.begin(), it);
                skeletonList[index].health -= 1;
                message = "skeleton hurt";
            }
            if (generated_maze.at(player_x).at(player_y - 1).skeleton) {
                skeleton current;
                current.x = player_x, current.y = player_y - 1;
                auto it = std::ranges::find(skeletonList, current);
                int index = distance(skeletonList.begin(), it);
                skeletonList[index].health -= 1;
                message = "skeleton hurt";
            }
            if (generated_maze.at(player_x - 1).at(player_y).skeleton) {
                skeleton current;
                current.x = player_x - 1, current.y = player_y;
                auto it = std::ranges::find(skeletonList, current);
                int index = distance(skeletonList.begin(), it);
                skeletonList[index].health -= 1;
                message = "skeleton hurt";
            }
            if (generated_maze.at(player_x + 1).at(player_y).skeleton) {
                skeleton current;
                current.x = player_x + 1, current.y = player_y;
                auto it = std::ranges::find(skeletonList, current);
                int index = distance(skeletonList.begin(), it);
                skeletonList[index].health -= 1;
                message = "skeleton hurt";
            }
            player_health -= bombCheck(player_x, player_y);
        }
        else {
            message = "Invalid Action!";
        }

        //need to use less than or equal to because some effects cause negative health, thus preventing the condition from ever being reached
        if (player_health <= 0) {
            playerDead = true;
            cout << "\n\n\n\n\n\n\n\nYou died! You had " << player_money << "money upon death. Better luck next time!";
        }
    }

}

void maze::updateSkeletons() {
    for (int i = 0; i < size(skeletonList); i++) {
        //calculate available tiles
        skeleton current = skeletonList[i];

        //two available actions in string
        for (int j = 0; j < 2; j++) {
            //remove from list if health <= 0
            if (skeletonList[i].health <= 0) {
                std::erase(skeletonList, current);
                generated_maze.at(current.x).at(current.y).skeleton = false;
                message = "skeleton killed!";

            } else if (cardinalAdjacent(player_x, player_y, current.x, current.y, 1).at(2) == 1) {
                player_health -= 1;
                skeletonList[i].health -= bombCheck(current.x, current.y);
            } else {
                vector<vector<int>> available;
                //iterate through actions list twice
                vector<int> targetData = cardinalAdjacent(player_x, player_y, current.x, current.y, 2);
                int distance = targetData[0];
                int direction = targetData[1];
                int withinRange = targetData[2];
                if (withinRange == 1) {
                    generated_maze.at(current.x).at(current.y).skeleton = false;
                    if (direction == 1) skeletonList[i].y -= 1;
                    if (direction == 2) skeletonList[i].x += 1;
                    if (direction == 3) skeletonList[i].y += 1;
                    if (direction == 4) skeletonList[i].x -= 1;
                    generated_maze.at(skeletonList[i].x).at(skeletonList[i].y).skeleton = true;
                } else {
                    targetData = targetFollow(player_x, player_y, current.x, current.y, 2);
                    if (targetData.at(0) == 1) {
                        generated_maze.at(current.x).at(current.y).skeleton = false;
                        skeletonList[i].x += targetData.at(1);
                        skeletonList[i].y += targetData.at(2);
                        generated_maze.at(skeletonList[i].x).at(skeletonList[i].y).skeleton = true;
                    } else {
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
    }
}

vector<vector<maze::tile>> maze::generate_maze(int mazeSizeInt) {
    //generate the maze for the game
    //number code for square types: 0 = tunnel (can walk), 1 = wall (can't walk), 2 = exit (ends game if reached), 3 = skeleton, 4 = bomb, 5 = coin
    //number code for maze generation tile types: 0 = empty, 1 = up, 2 = right, 3 = down, 4 = left, 5 = dead end, 6 = boundary. If not 0, then not empty.//"mazeSizeInt" internal maze size
    mazeSizeExt = mazeSizeInt + 4; //external is internal plus one boundary tile on each side for both dimensions, so plus two
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
    int number_of_tiles = mazeSizeInt * mazeSizeInt;

    //vector to store the data about adjacent tiles
    vector<array<int, 2>> available;

    //stack and available choice
    int stackPos = 0;
    vector<array<int, 2>> stack;
    stack.push_back({0,0});

    int indice = 0;

    //current position components
    int current_x = 2;
    int current_y = 2;

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
        if (current_y > 2)
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
        if (current_x < size(tile_maze) - 3)
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
        if (current_y < size(tile_maze) - 3)
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
        if (current_x > 2)
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
            generated += count(tile_maze.at(x).begin(), tile_maze.at(x).end(), 0);
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
    cout << " ";

    //generate x and y for the exit
    uniform_int_distribution<> exitDistWalkable(0, size(walkable) - 1);
    int exit = exitDistWalkable(gen);

    int exitX = walkable.at(exit).at(0);
    int exitY = walkable.at(exit).at(1);
    generated_maze.at(exitX).at(exitY).exit = true;

    //remove the point where the exit was generated
    walkable.erase(walkable.begin() + exit);

    //generated x and y for the entrance
    //make sure to use (0, size - 1) since the first index is zero and the last index is size - 1
    uniform_int_distribution<> entranceDistWalkable(0, size(walkable) - 1);
    int entrance = entranceDistWalkable(gen);

    int entranceX = walkable.at(entrance).at(0);
    int entranceY = walkable.at(entrance).at(1);
    player_x = entranceX;
    player_y = entranceY;

    //generate money locations
    for (int positions = 0; positions < 0.15 * size(walkable); positions++) {
        uniform_int_distribution<> moneyDistWalkable(0, size(walkable) - 1);
        int listPos = moneyDistWalkable(gen);
        int moneyX = walkable.at(listPos).at(0);
        int moneyY = walkable.at(listPos).at(1);
        generated_maze.at(moneyX).at(moneyY).money = true;
        walkable.erase(walkable.begin() + listPos);
    }

    //generate initial skeleton locations
    for (int positions = 0; positions < 0.06 * size(walkable); positions++) {
        uniform_int_distribution<> moneyDistWalkable(0, size(walkable) - 1);
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

    //generate bomb locations
    for (int positions = 0; positions < 0.08 * size(walkable); positions++) {
        uniform_int_distribution<> bombDistWalkable(0, size(walkable) - 1);
        int listPos = bombDistWalkable(gen);
        int bombX = walkable.at(listPos).at(0);
        int bombY = walkable.at(listPos).at(1);
        generated_maze.at(bombX).at(bombY).bomb = true;
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
            char value = '0';
            value = visualTile(x, y);

            if (value == '0') {
                cout << "0" << "  ";
            } else if (value == '1') {
                cout << "1" << "  ";
            } else if (value == 's') {
                cout << "s" << "  ";
            } else if (value == 'm') {
                cout << "m" << "  ";
            } else if (value == 'e') {
                cout << "e" << "  ";
            } else if (value == 'b') {
                cout << "b" << "  ";
            } else if (value == 'h') {
                cout << "h" << "  ";
            } else {
                cout << "!" << "  ";
            }
        }
        cout << "\n";
    }
}


