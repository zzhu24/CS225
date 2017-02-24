#include "maze.h"

/**No-parameter constructor.
*Creates an empty maze.
*/
SquareMaze::SquareMaze (){}

/**Makes a new SquareMaze of the given height and width.
*If this object already represents a maze it will clear all the existing data before doing so. You will start with a square grid (like graph paper) with the specified height and width.
*You will select random walls to delete without creating a cycle, until there are no more walls that could be deleted without creating a cycle. Do not delete walls on the perimeter of the grid.
*Hints: You only need to store 2 bits per square: the "down" and "right" walls. The finished maze is always a tree of corridors.)
*Parameters
*width	The width of the SquareMaze (number of cells)
*height	The height of the SquareMaze (number of cells)
*/
void SquareMaze::makeMaze(int width, int height){
	this->size = (width * height);//this is the assignment
	theSet.addelements(size);//this is the initialization
	this -> widthSize = width;//this is the assignment
	this -> heightSize = height;//this is the assignment
	for(int i = 0; i < size; i++){//initialize all the data
		downList.push_back(true);//set all as having the downwall
		rightList.push_back(true);}//set all as having the rightwall
	int which = 0;
	int count = 0;
	//for randomly choosing the row
	//for randomly choosing the column
	srand (time(NULL));
	while(count < (size/2)){
		int row = rand() % (heightSize - 1);
		int col = rand() % (widthSize - 1);
		which = rand() % 2;//to gaurantee that all the steps are random
		if(which){
			if(isRight(row, col, widthSize) == true){
				randomRight(row, col, widthSize);
				count++;}}//be super careful here, we only count and add i of we already successfully knock down the wall
		else{
			if(isDown(row, col, widthSize) == true){
				randomDown(row, col, widthSize);
				count++;}}}//be super careful here, we only count and add i of we already successfully knock down the wall
	int rowNum = 0;//in order to avoid the circle path
	for (; rowNum < heightSize-1; rowNum++){
		int colNum = 0;
		for (; colNum  < widthSize - 1; colNum ++){//in order to avoid all the cycles
			if(which){
				if(isRight(rowNum, colNum, widthSize) == true){
					randomRight(rowNum, colNum, widthSize);}//walk again to find all possibility
				if(isDown(rowNum, colNum, widthSize) == true){
					randomDown(rowNum, colNum, widthSize);}}//walk again to find all possibility
			else{
				if(isDown(rowNum, colNum, widthSize) == true){
					randomDown(rowNum, colNum, widthSize);}//walk again to find all possibility
				if(isRight(rowNum, colNum, widthSize) == true){
					randomRight(rowNum, colNum, widthSize);}}}//walk again to find all possibility
		if(isDown(rowNum, colNum, widthSize) == true){	
			randomDown(rowNum, colNum, widthSize);}}//this is to check the bottom side of the maze
	for(int colNum = 0; colNum < widthSize -1; colNum ++){//this os for the down side wall
		if(isRight(rowNum, colNum, widthSize) == true){
			randomRight(rowNum, colNum, widthSize);}}}

/**the helper function for checking if we want to knock down the right wall without making a cycle*/
bool SquareMaze::isRight(int r, int c, int wid){
	return rightList[r * wid + c] == true && theSet.find(r * wid + c) != theSet.find(r * wid + c + 1);}

/**the helper function for checking if we want to knock down the right wall without making a cycle*/
bool SquareMaze::isDown(int r, int c, int wid){
	return downList[r * wid + c] == true && theSet.find(r * wid + c) != theSet.find((r+1)*wid + c);}

/**the helper function for randomly knock down the right wall*/
void SquareMaze::randomRight(int r, int c, int wid){
	rightList[r * wid + c] = false;
	theSet.setunion(r * wid + c, r * wid + c + 1);}

/**the helper function for randomly knock down the down wall*/
void SquareMaze::randomDown(int r, int c, int wid){
	downList[r * wid + c] = false;
	theSet.setunion(r * wid + c, (r+1)*wid + c);}

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
bool SquareMaze::canTravel(int x, int y, int dir) const{
	if(dir == 0 && x != widthSize-1){//check the right side boundary
		return (rightList[y*widthSize + x] == false);}
	if(dir == 1 && y != heightSize-1){//check the down side boundary
		return (downList[y*widthSize + x] == false);}
	if(dir == 2 && x != 0){//check the left side boundary
		return (rightList[y*widthSize + x-1] == false);}
	if(dir == 3 && y != 0){//check the up side boundary
		return (downList[(y-1)*widthSize + x] == false);}
	return false;}

/**Sets whether or not the specified wall exists.
*This function should be fast (constant time). You can assume that in grading we will not make your maze a non-tree and then call one of the other member functions. 
*setWall should not prevent cycles from occurring, but should simply set a wall to be present or not present. Our tests will call setWall to copy a specific maze into your implementation.
*Parameters
*x	The x coordinate of the current cell
*y	The y coordinate of the current cell
*dir	Either 0 (right) or 1 (down), which specifies which wall to set (same as the encoding explained in canTravel). You only need to support setting the bottom and right walls of every square in the grid.
*exists	true if setting the wall to exist, false otherwise
*/
void SquareMaze::setWall(int x, int y, int dir, bool exists){
	int boundary = x + y*widthSize;//in order tp set the boundary
	if(dir == 0 && x != widthSize-1)
		rightList[boundary] = exists? true : false;//if wall exist = true, index = true, else = false
	if(dir == 1 && y != heightSize-1)
		downList[boundary] = exists? true : false;//if wall exist = true, index = true, else = false
	return;}

vector<int> SquareMaze::solveMaze(){
	vector<int> solution;
	int * destRow = new int[widthSize];//this is for making sure that we do not go out of the range
	solveOne(solution, destRow, 0, 0);
	int theDest = 0;
	for(int i = 1; i < widthSize; i ++){
		if(destRow[theDest] < destRow[i]){//this function is used to find the dest for insertion
		theDest = i;}}
	solution.clear();//check again for the cycle
	solveTwo(solution, theDest, 0, 0);
	delete [] destRow;
	destRow = NULL;
	return solution;}

/**the helper function for finding the most part of the path for the maze we made*/
void SquareMaze::solveOne(vector<int> & a, int * dest, int x, int y){
	if(y == heightSize - 1){//this is for checking if we find the exist or to the boundary
		dest[x] = a.size();}
	if(canTravel(x, y, 0)){//this is for walking to the right ans test if we can go further
		tryRoad(a, x, y, 0, 0, true);
		//if we can go, we push this maze the the vector
		//close the wall since we want to turn the blank to a wall to avoid walking cycle
		solveOne(a, dest, x + 1, y);//if we can go, we will try the next maze at the right following the direction
		knockDown(a, x, y, 0, false);}
		//if not we do not want this path to exist in the vector any mall
		//we want to keep the block and not go any more
	if(canTravel(x, y, 1)){//this is for walking to the down ans test if we can go further
		tryRoad(a, x, y, 1, 1, true);
		//if we can go, we push this maze the the vector
		//close the wall since we want to turn the blank to a wall to avoid walking cycle
		solveOne(a, dest, x, y + 1);//if we can go, we will try the next maze at the right following the direction
		knockDown(a, x, y, 1, false);}
		//if not we do not want this path to exist in the vector any mall
		//we want to keep the block and not go any more	
	if(canTravel(x, y, 2)){//this is for walking to the left ans test if we can go further
		tryRoad(a, x - 1, y, 2, 0, true);
		//if we can go, we push this maze the the vector
		//close the wall since we want to turn the blank to a wall to avoid walking cycle
		solveOne(a, dest, x - 1, y);//if we can go, we will try the next maze at the right following the direction
		knockDown(a, x - 1, y, 0, false);}
		//if not we do not want this path to exist in the vector any mall
		//we want to keep the block and not go any more
	if(canTravel(x, y, 3)){//this is for walking to the up ans test if we can go further
		tryRoad(a, x, y - 1, 3, 1, true);
		//if we can go, we push this maze the the vector
		//close the wall since we want to turn the blank to a wall to avoid walking cycle
		solveOne(a, dest, x, y - 1);//if we can go, we will try the next maze at the right following the direction
		knockDown(a, x, y - 1, 1, false);}
		//if not we do not want this path to exist in the vector any mall
		//we want to keep the block and not go any more
	return;}

/**the helper function for trying if we want to go that way*/
void SquareMaze::tryRoad(vector<int> & a, int x, int y, int dir, int rd, bool knock){
	a.push_back(dir);
	setWall(x, y, rd, knock);}

/**the helper function for build the wall and avoid going back*/
void SquareMaze::knockDown(vector<int> & a, int x, int y, int rd, bool knock){
	a.pop_back();
	setWall(x, y, rd, knock);}

/**this helper funtion is to avoid the cycles in the solution*/
bool SquareMaze::solveTwo(vector<int> & a, int dest, int x, int y){
	if(x == dest && y == heightSize -1){//this is for checking if we find the exist or to the boundary
		return true;}
	if(canTravel(x, y, 0)){
		tryRoad(a, x, y, 0, 0, true);
		if(solveTwo(a, dest, x + 1, y)){//this is checking the right and see if there is a solution
			setWall(x, y, 0, false);//if we can go, we push this maze the the vector
			return true;}//close the wall since we want to turn the blank to a wall to avoid walking cycle
		knockDown(a, x, y, 0, false);}
		//if not we do not want this path to exist in the vector any mall
		//we want to keep the block and not go any more
	if(canTravel(x, y, 1)){
		tryRoad(a, x, y, 1, 1, true);
		if(solveTwo(a, dest, x, y + 1)){//this is checking the right and see if there is a solution
			setWall(x, y, 1, false);//if we can go, we push this maze the the vector
			return true;}//close the wall since we want to turn the blank to a wall to avoid walking cycle
		knockDown(a, x, y, 1, false);}
		//if not we do not want this path to exist in the vector any mall
		//we want to keep the block and not go any more
	if(canTravel(x, y, 2)){
		tryRoad(a, x - 1, y, 2, 0, true);
		if(solveTwo(a, dest, x - 1, y)){//this is checking the right and see if there is a solution
			setWall(x-1, y, 0, false);//if we can go, we push this maze the the vector
			return true;}//close the wall since we want to turn the blank to a wall to avoid walking cycle
		knockDown(a, x - 1, y, 0, false);}
		//if not we do not want this path to exist in the vector any mall
		//we want to keep the block and not go any more
	if(canTravel(x, y, 3)){
		tryRoad(a, x, y - 1, 3, 1, true);
		if(solveTwo(a, dest, x, y-1)){//this is checking the right and see if there is a solution
			setWall(x, y-1, 1, false);//if we can go, we push this maze the the vector
			return true;}//close the wall since we want to turn the blank to a wall to avoid walking cycle
		knockDown(a, x, y - 1, 1, false);}
		//if not we do not want this path to exist in the vector any mall
		//we want to keep the block and not go any more
	return false;}

PNG* SquareMaze::drawMaze() const{
	PNG * output = new PNG(widthSize*10+1, heightSize*10+1);
	for(int row = 0; row < heightSize*10; row++){//this is to draw the left side of the maze to be black
	blacken(output, 0, row);}
	for(int column = 10; column < widthSize*10; column++){//this is to draw the top side of the maze to be black
		blacken(output, column, 0);}
	for(int i = 0; i < size; i++){//this is for going trough a the maze and draw out all the blockes
		if(rightList[i]){
			for(int k = 0; k <= 10; k++){
			blacken(output, (i%widthSize + 1) * 10, i/widthSize * 10 + k);}}
		if(downList[i]){
			for(int k = 0; k <= 10; k++)
			{blacken(output, i%widthSize * 10 + k, (i/widthSize + 1) * 10);}}}

	return output;}

PNG* SquareMaze::drawMazeWithSolution(){
	PNG * output = drawMaze();
	vector< int > solution = solveMaze();
	int x = 10/2;
	int y = 10/2;
	for(size_t i = 0; i < solution.size(); i++){
		if(solution[i] == 0){
			for(int j = 0; j < 11; j++){//this is for coloring the right path of the solution
				reddish(output, x + j, y);}
			x = x + 10;}//in order to jump to the next one since the side is like 10
		else if(solution[i] == 1){//this is for coloring the down path of the solution
			for(int j = 0; j < 11; j++){
				reddish(output, x, y + j);}			
			y = y + 10;}//in order to jump to the next one since the side is like 10
		else if(solution[i] == 2){//this is for coloring the left path of the solution
			for(int j = 0; j < 11; j++){
				reddish(output, x - j, y);}
			x = x - 10;}//in order to jump to the next one since the side is like 10
		else{//this is for coloring the up path of the solution
			for(int j = 0; j < 11; j++){
				reddish(output, x, y - j);}		
			y = y - 10;}}//in order to jump to the next one since the side is like 10
	

	/*draw the exit*/
	for(int k = 1; k < 10; k++){
		blanked(output, (x/10)*10 + k, heightSize*10);}
	return output;}

/**make the side as black to draw the maze or the solution*/
void SquareMaze::blacken(PNG * change, int a, int b) const{
	(* change)(a, b)->red = 0;
	(* change)(a, b)->green = 0;
	(* change)(a, b)->blue = 0;}

/**make the side as red to draw the maze or the solution*/
void SquareMaze::reddish(PNG * change, int a, int b) const{
	(* change)(a, b)->red = 255;
	(* change)(a, b)->green = 0;
	(* change)(a, b)->blue = 0;}

/**make the side as black to draw the maze or the solution*/
void SquareMaze::blanked(PNG * change, int a, int b) const{
	(* change)(a, b)->red = 255;
	(* change)(a, b)->green = 255;
	(* change)(a, b)->blue = 255;}

















//tested right with tao
