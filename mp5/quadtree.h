// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
		Quadtree ();
		Quadtree(PNG const & source, int resolution);
		Quadtree(Quadtree const & source);
		~Quadtree();
		Quadtree const & operator=(const Quadtree &  source);
		void buildTree(PNG const & source,int resolution);
		RGBAPixel getPixel(int x,int y)const;
		PNG decompress()const;
		void clockwiseRotate();
		void prune(int tolerance);
		int pruneSize(int tolerance)const;
		int idealPrune(int numLeaves)const;
		
	
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
		class QuadtreeNode{
			public:
				QuadtreeNode* nwChild;  // pointer to northwest child
				QuadtreeNode* neChild;  // pointer to northeast child
				QuadtreeNode* swChild;  // pointer to southwest child
				QuadtreeNode* seChild;  // pointer to southeast child

				RGBAPixel element;};  // the pixel stored as this node's "data"
	
		QuadtreeNode* root;    // pointer to root of quadtree
		int imageSize; //size of this image
		void copy(QuadtreeNode * copiedOne, QuadtreeNode * & replacedOne);
	
		void clear(QuadtreeNode *& node);
		void buildTree(PNG const & source, int resolution, int x, int y, QuadtreeNode * & node);
		RGBAPixel getPixel(QuadtreeNode * node,int x,int y,int resolution) const;
		void decompress(PNG & replacedOne, int x, int y, int resolution, QuadtreeNode * node) const;
		void clockwiseRotate(QuadtreeNode * current);
		void prune(QuadtreeNode * current, int tolerance);
		bool needPrune(QuadtreeNode * node, int tolerance, QuadtreeNode * avg)const;
		int difference(RGBAPixel one, RGBAPixel two)const;
		int pruneSize(QuadtreeNode * current, int tolerance, QuadtreeNode * avg)const;
		int idealPrune(int max, int min, int number)const;

		/**** Functions added for testing/grading                ****/
		/**** Do not remove this line or copy its contents here! ****/
		#include "quadtree_given.h"
};

#endif
