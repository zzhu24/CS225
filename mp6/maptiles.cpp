/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    /**
     * @todo Implement this function!
     */
	const int Dim=3;
	MosaicCanvas *cur= new MosaicCanvas(theSource.getRows(),theSource.getColumns());
	vector<Point<Dim>> points;
	map<Point<Dim>,TileImage> maps;
	RGBAPixel pixel;
	double num[Dim];
	for(size_t i=0;i<theTiles.size();i++){
		pixel=theTiles[i].getAverageColor();
		num[0]=pixel.red;
		num[1]=pixel.green;
		num[2]=pixel.blue;
		Point<Dim> point(num);
		points.push_back(point);
		maps.insert(pair<Point<Dim>,TileImage>(points[i],theTiles[i]));}

	KDTree<Dim> trees(points);
	for(int i=0;i<cur->getColumns();i++){
		for(int j=0;j<cur->getColumns();j++){
			pixel=theSource.getRegionColor(i,j);
			num[0]=pixel.red;
			num[1]=pixel.green;
			num[2]=pixel.blue;
			Point<3> point1(num);
			TileImage near=maps.at(trees.findNearestNeighbor(point1));
			cur->setTile(i,j,near);}}
	return cur;}
