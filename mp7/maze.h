#ifndef MAZE_H
#define MAZE_H

#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
#include <cstdlib>

#include "dsets.h"
#include "png.h"

using std::vector;
using std::pair;
using std::queue;
using std::cout;
using std::endl;
using std::make_pair;

class SquareMaze{
	public:

		/**No-parameter constructor.
		*Creates an empty maze.
		*/
		SquareMaze ();
	
		/**Makes a new SquareMaze of the given height and width.
		*If this object already represents a maze it will clear all the existing data before doing so. You will start with a square grid (like graph paper) with the specified height and width.
		*You will select random walls to delete without creating a cycle, until there are no more walls that could be deleted without creating a cycle. Do not delete walls on the perimeter of the grid.
		*Hints: You only need to store 2 bits per square: the "down" and "right" walls. The finished maze is always a tree of corridors.)
		*Parameters
		*width	The width of the SquareMaze (number of cells)
		*height	The height of the SquareMaze (number of cells)
		*/
		void makeMaze(int width, int height);

		/**This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y).
		*For example, after makeMaze(2,2), the possible input coordinates will be (0,0), (0,1), (1,0), and (1,1).
		*dir = 0 represents a rightward step (+1 to the x coordinate)
		*dir = 1 represents a downward step (+1 to the y coordinate)
		*dir = 2 represents a leftward step (-1 to the x coordinate)
		*dir = 3 represents an upward step (-1 to the y coordinate)
		*You can not step off of the maze or through a wall.
		*This function will be very helpful in solving the maze. It will also be used by the grading program to verify that your maze is a tree that occupies the whole grid, and to verify your maze solution.
		*So make sure that this function works!
		*Parameters
		*x	The x coordinate of the current cell
		*y	The y coordinate of the current cell
		*dir	The desired direction to move from the current cell
		*Returns
		*whether you can travel in the specified direction
		*/
		bool canTravel(int x, int y, int dir) const;

		/**Sets whether or not the specified wall exists.
		*This function should be fast (constant time). You can assume that in grading we will not make your maze a non-tree and then call one of the other member functions. 
		*setWall should not prevent cycles from occurring, but should simply set a wall to be present or not present. Our tests will call setWall to copy a specific maze into your implementation.
		*Parameters
		*x	The x coordinate of the current cell
		*y	The y coordinate of the current cell
		*dir	Either 0 (right) or 1 (down), which specifies which wall to set (same as the encoding explained in canTravel). You only need to support setting the bottom and right walls of every square in the grid.
		*exists	true if setting the wall to exist, false otherwise
		*/
		void setWall(int x, int y, int dir, bool exists);		


		/**
		*
		*
		*
		*
		*
		*
		*
		*/
		
		vector<int> solveMaze();

		PNG* drawMaze() const;
		
		PNG* drawMazeWithSolution();

	private:
		vector<bool> downList;
		vector<bool> rightList;
		
		int widthSize;//in order to count the cells
		int heightSize;//in order to count the cells
		int size;//for recording the size of the maze

		DisjointSets theSet;//this is for recording the path and the solution

		bool isRight(int r, int c, int wid);//the helper function for checking if we want to knock down the right wall without making a cycle
		bool isDown(int r, int c, int wid);//the helper function for checking if we want to knock down the down wall without making a cycle
		void randomRight(int r, int c, int wid);//for randomly working through the helper function for randomly knock down the right wall
		void randomDown(int r, int c, int wid);//for randomly working through the helper function for randomly knock down the down wall

		void blacken(PNG * change, int a, int b) const;//make the side as black to draw the maze or the solution
		void reddish(PNG * change, int a, int b) const;//make the side as red to draw the maze or the solution
		void blanked(PNG * change, int a, int b) const;//make the side as white to draw the maze or the solution

		void solveOne(vector<int> & a, int * dest, int x, int y);//the helper function for finding the most part of the path for the maze we made
		bool solveTwo(vector<int> & a, int dest, int x, int y);//this helper funtion is to avoid the cycles in the solution

		void tryRoad(vector<int> & a, int x, int y, int dir, int rd, bool knock);//the helper function for trying if we want to go that way
		void knockDown(vector<int> & a, int x, int y, int rd, bool knock);//the helper function for build the wall and avoid going back

};

#endif









//tested right with tao
