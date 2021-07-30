//
//  Maze.hpp
//  mystl2
//
//  Created by K on 2021/1/1.
//  Copyright © 2021 K. All rights reserved.
//

#ifndef Maze_hpp
#define Maze_hpp


typedef struct Position
{
    int _x;
    int _y;
}Position;

#define MAX_ROW  100
#define MAX_COL  100

typedef struct Maze
{
    int _map[MAX_ROW][MAX_COL];
}Maze;


#endif /* Maze_hpp */
