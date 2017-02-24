// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
#include <unistd.h>
using namespace std;

/**
*constructor with no parameter and build an empty tree
**/
Quadtree::Quadtree(){
	root = NULL;
	imageSize = 0;}

/**
*This constructor's purpose is to build a Quadtree representing the upper-left d by d block of the source image
**/
Quadtree::Quadtree(PNG const & source, int resolution){
	root = NULL;
	imageSize = resolution;
	buildTree(source, resolution);}

/**
*copy constructor */
Quadtree::Quadtree(Quadtree const & source){
	root=NULL;
	imageSize=source.imageSize;
	copy(source.root,this->root);}

/**
*Helper function of the copy constructor
**/
void Quadtree::copy(QuadtreeNode * copiedOne, QuadtreeNode * & replacedOne){
	if(copiedOne == NULL){
		return;}
	else{
		replacedOne = new QuadtreeNode();
		replacedOne -> element = copiedOne -> element;
		copy(copiedOne -> nwChild, replacedOne -> nwChild);
		copy(copiedOne -> neChild, replacedOne -> neChild);
		copy(copiedOne -> swChild, replacedOne -> swChild);
		copy(copiedOne -> seChild, replacedOne -> seChild);}}
//*& mean its a address but passed by reference whick means original one can be changed

/**
*overload operator =
**/
Quadtree const & Quadtree::operator=(Quadtree const & source){
	if(this != & source){
		clear(root);
		imageSize = source.imageSize;
		copy(source.root,root);}
	return (*this);}

/**
*destructor
**/
Quadtree::~Quadtree(){
	clear(root);}

/**
*helper function of desctructor clear()
**/
void Quadtree::clear(QuadtreeNode *& node){
	if(node==NULL){
		return;}
	else{
		clear(node->nwChild);
		clear(node->neChild);
		clear(node->swChild);
		clear(node->seChild);
		delete node;
		node=NULL;}}

/**
*this function takes two arguments, a PNG object source, and an integer d, in that order. 
*It returns nothing. It should delete the current contents of the Quadtree object
*then turn it into a Quadtree object representing the upper-left d by d block of source.
**/
void Quadtree::buildTree(PNG const & source, int resolution){
	clear(root);
	imageSize=resolution;
	buildTree(source,resolution,0,0,root);}

/**
*helper function of buildTree
**/
void Quadtree::buildTree(PNG const & source, int resolution, int x, int y, QuadtreeNode * & node){
	node = new QuadtreeNode();
	if(resolution == 1){
		node -> element = * source(x,y);
		node -> neChild = NULL;
		node -> nwChild = NULL;
		node -> seChild = NULL;
		node -> swChild = NULL;
		return;}
	else{
		int newSize = resolution / 2;
		buildTree(source,newSize,x,y,node->nwChild);
		buildTree(source,newSize,x+newSize,y,node->neChild);
		buildTree(source,newSize,x,y+newSize,node->swChild);
		buildTree(source,newSize,x+newSize,y+newSize,node->seChild);
		node->element.red=(node->nwChild->element.red+node->neChild->element.red+node->swChild->element.red+node->seChild->element.red)/4;
		node->element.blue=(node->nwChild->element.blue+node->neChild->element.blue+node->swChild->element.blue+node->seChild->element.blue)/4;
		node->element.green=(node->nwChild->element.green+node->neChild->element.green+node->swChild->element.green+node->seChild->element.green)/4;}}

/**Gets the RGBAPixel corresponding to the pixel at coordinates (x, y) in the bitmap image which the Quadtree represents.
*Note that the Quadtree may not contain a node specifically corresponding to this pixel (due, for instance, to pruning - see below). 
*In this case, getPixel will retrieve the pixel (i.e. the color) of the square region within which the smaller query grid cell would lie. 
*(That is, it will return the element of the nonexistent leaf's deepest surviving ancestor.) 
*If the supplied coordinates fall outside of the bounds of the underlying bitmap, 
*or if the current Quadtree is "empty" (i.e., it was created by the default constructor) 
*then the returned RGBAPixel should be the one which is created by the default RGBAPixel constructor.
**/
RGBAPixel Quadtree::getPixel(int x,int y)const{
	return getPixel(root,x,y,imageSize);}

/**
*helper function of getPixel
**/
RGBAPixel Quadtree::getPixel(QuadtreeNode * node,int x,int y,int resolution) const{
	if(node->nwChild==NULL){
		return node->element;}
	if(x<resolution/2&&y<resolution/2){
		return getPixel(node->nwChild,x,y,resolution/2);}
	if(x<resolution/2&&y>=resolution/2){
		return getPixel(node->swChild,x,y-resolution/2,resolution/2);}
	if(x>=resolution/2&&y>=resolution/2){
		return getPixel(node->seChild,x-resolution/2,y-resolution/2,resolution/2);}
	else{
		return getPixel(node->neChild,x-resolution/2,y,resolution/2);}}


/**
*Returns the underlying PNG object represented by the Quadtree.
*If the current Quadtree is "empty" (i.e., it was created by the default constructor) 
*then the returned PNG should be the one which is created by the default PNG constructor. 
*This function effectively "decompresses" the Quadtree. A Quadtree object, 
*in memory, may take up less space than the underlying bitmap image, but we cannot simply look at the Quadtree and tell what image it represents.
*By converting the Quadtree back into a bitmap image, we lose the compression, but gain the ability to view the image directly.
**/
PNG Quadtree::decompress()const{
	if(root==NULL){
		return PNG();}
	else{
		PNG temp = PNG(imageSize, imageSize);
		decompress(temp, 0, 0, imageSize, root);
		return temp;}}

/**
*helper function decompress
**/
void Quadtree::decompress(PNG & replacedOne, int x, int y, int resolution, QuadtreeNode * node) const{
	if(resolution == 1 || node -> nwChild == NULL){
		for(int i = 0; i < resolution; i ++){
			for(int j = 0; j < resolution; j++){
				*replacedOne(x+i,y+j)=node->element;}}}
	else if(node == NULL){
		return;}
	else{
		decompress(replacedOne,x,y,resolution/2,node->nwChild);
		decompress(replacedOne,x+resolution/2,y,resolution/2,node->neChild);
		decompress(replacedOne,x,y+resolution/2,resolution/2,node->swChild);
		decompress(replacedOne,x+resolution/2,y+resolution/2,resolution/2,node->seChild);}}
/**
*Rotates the Quadtree object's underlying image clockwise by 90 degrees.
*(Note that this should be done using pointer manipulation, not by attempting to swap the element fields of QuadtreeNodes. 
*Trust us; it's easier this way.)
**/
void Quadtree::clockwiseRotate(){
	clockwiseRotate(root);}

/**
*helper function clockwiseRotate
**/
void Quadtree::clockwiseRotate(QuadtreeNode * current){
	if(current == NULL){
		return;}
	if(current -> nwChild == NULL){
		return;}
	else{
		QuadtreeNode * temp = current -> nwChild;
		current -> nwChild = current -> swChild;
		current -> swChild = current -> seChild;
		current -> seChild = current -> neChild;
		current -> neChild = temp;
		temp = NULL;
		clockwiseRotate(current -> nwChild);
		clockwiseRotate(current -> swChild);
		clockwiseRotate(current -> neChild);
		clockwiseRotate(current -> seChild);}}

/**
*Compresses the image this Quadtree represents.
*If the color values of the leaves of a subquadtree don't vary by much, we might as well represent the entire subtree by, say, the average color value of those leaves.
*We may use this information to effectively "compress" the image, by strategically trimming the Quadtree.
*Consider a node n and the subtree, Tn rooted at n, and let avg denote the component-wise average color value of all the leaves of Tn.
*Component-wise average means that every internal node in the tree calculates its value by averaging its immediate children.
*This implies that the average must be calculated in a "bottom-up" manner.
*Due to rounding errors, using the component-wise average is not equivalent to using the true average of all leaves in a subtree.
*If a node n is pruned, the children of n and the subtrees for which they are the roots are removed from the Quadtree.
*Node n is pruned if the color value of no leaf in Tn, differs from avg by more than tolerance. (Note: for all average calculations, just truncate the value to integer.)
*We define the "difference" between two colors, (r1,g1,b1) and (r2,g2,b2), to be (r2−r1)2+(g2−g1)2+(b2−b1)2.
*To be more complete, if the tolerance condition is met at a node n, then the block of the underlying image which n represents contains only pixels which are "nearly" the same color.
*For each such node n, we remove from the Quadtree all four children of n, and their respective subtrees (an operation we call a pruning).
*This means that all of the leaves that were deleted, corresponding to pixels whose colors were similar,
*are now replaced by a single leaf with color equal to the average color over that square region.
*The prune function, given a tolerance value, prunes the Quadtree as extensively as possible.
*(Note, however, that we do not want the prune function to do an "iterative" prune.
*It is conceivable that by pruning some mid-level node n, an ancestor p of n then becomes prunable, due to the fact that the prune changed the leaves descended from p.
*Your prune function should evaluate the prunability of each node based on the presence of all nodes, and then delete the subtrees based at nodes deemed prunable.)
*Note
*You should start pruning from the root of the Quadtree.
*Parameters
*tolerance:The integer tolerance between two nodes that determines whether the subtree can be pruned.
**/
void Quadtree::prune(int tolerance){
	prune(root, tolerance);}

/**
*helper function prune
**/
void Quadtree::prune(QuadtreeNode * current, int tolerance){
	if(current == NULL){
		return;}
	if(current -> nwChild == NULL){
		return;}
	if(needPrune(current, tolerance, current) == true){
		clear(current -> nwChild);
		clear(current -> swChild);
		clear(current -> seChild);
		clear(current -> neChild);
		return;}
	prune(current -> nwChild, tolerance);
	prune(current -> neChild, tolerance);
	prune(current -> swChild, tolerance);
	prune(current -> seChild, tolerance);}
//it is actually like you compare the leaves with the root, if the four leaf of same immediate parent are within the tolerance, then you cut the four leaves of the immediate parent
//then you go through all the leaves four by four
//if there are some leaves out of the tolerance, you move downward to four child of root and do the comparison and prune again by recursion

/**
*helper function prune -> needPrune
**/
bool Quadtree::needPrune(QuadtreeNode * node, int tolerance, QuadtreeNode * avg)const{
	if(node == NULL){
		return true;}
	if(node -> nwChild == NULL){
		if(difference(node -> element, avg -> element) > tolerance){
			return false;}
		else{
			return true;}}
	else{
	//the recursion if the current node is not a leaf nod
		return needPrune(node -> nwChild, tolerance, avg) && needPrune(node -> neChild, tolerance, avg) && needPrune(node -> swChild, tolerance, avg) && needPrune(node -> seChild, tolerance, avg);}}

/**
*helper function prune -> difference
**/
int Quadtree::difference(RGBAPixel one, RGBAPixel two)const{
	int diff = (one.red - two.red) * (one.red - two.red) + (one.green - two.green) * (one.green - two.green) + (one.blue - two.blue) * (one.blue - two.blue);
	return diff;}

/**
*This function is similar to prune; however, it does not actually prune the Quadtree.
*Rather, it returns a count of the total number of leaves the Quadtree would have if it were pruned as in the prune function.
*Parameters
*tolerance	The integer tolerance between two nodes that determines whether the subtree can be pruned.
*Returns
*How many leaves this Quadtree would have if it were pruned with the given tolerance.
**/
int Quadtree::pruneSize(int tolerance)const{
	return pruneSize(root, tolerance, root);}

/**
*helper function pruneSize
**/
int Quadtree::pruneSize(QuadtreeNode * current, int tolerance, QuadtreeNode * avg) const{
	if(current == NULL){
		return 0;}
	if(needPrune(current, tolerance, avg) == true || current -> nwChild == NULL){
		return 1;}
	else{
		return pruneSize(current -> nwChild, tolerance, avg -> nwChild) + pruneSize(current -> neChild, tolerance, avg -> neChild) + pruneSize(current -> swChild, tolerance, avg -> swChild) + pruneSize(current -> seChild, tolerance, avg -> seChild);}}

/**
*Calculates and returns the minimum tolerance necessary to guarantee that upon pruning the tree, no more than numLeaves leaves remain in the Quadtree.
*Essentially, this function is an inverse of pruneSize; for any Quadtree object theTree, and for any positive integer tolerance it should be true that
*theTree.pruneSize(theTree.idealPrune(numLeaves)) <= numLeaves 
*Once you understand what this function is supposed to do, you will probably notice that there is an "obvious" implementation.
*This is probably not the implementation you want to use! There is a fast way to implement this function, and a slow way; you will need to find the fast way.
*(If you doubt that it makes a significant difference, the tests in the given main.cpp should convince you.)
*Parameters
*numLeaves
*The number of leaves you want to remain in the tree after prune is called.
*Returns
*The minimum tolerance needed to guarantee that there are no more than numLeaves remaining in the tree.
*Note
*The "obvious" implementation involves a sort of linear search over all possible tolerances.
*What if you tried a binary search instead?
**/
int Quadtree::idealPrune(int numLeaves)const{
	if(numLeaves >= pruneSize(0)){
		return 0;}
//some leaves should be pruned though they have a difference with the average
//if tolerance is large, there should be less leaves
//if the tolerance already get to zero and theTree.pruneSize(theTree.idealPrune(numLeaves)) <= numLeaves  still cannot be satisfied, then return 0
	else{
		return idealPrune(65025, 0, numLeaves);}}

/**
*helper function idealPrune
**/
int Quadtree::idealPrune(int max, int min, int number)const{
	int temp = (max + min)/2;
	int size = pruneSize(temp);
	if(min >= max){
		return min;}
	if(size > number){
		return idealPrune(max, temp +1, number);}
	else{
		return idealPrune(temp, min, number);}}
