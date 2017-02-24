#ifndef SCENE_H
#define SCENE_H

#include "image.h"
#include "png.h"
#include "rgbapixel.h"
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <iostream>
#include <sstream>
using namespace std;


class Scene{
public:
Scene (int max);

~Scene ();

Scene (const Scene & source);

const Scene & operator = (const Scene & source);

void changemaxlayers (int newmax);

void addpicture (const char *FileName, int index, int x, int y);

void  changelayer (int index, int newindex);

void  translate (int index, int xcoord, int ycoord);

void  deletepicture (int index);

Image * getpicture (int index) const ;

Image  drawscene () const;



int maxlay;

Image **imagepointersarray;

int *x,*y;

void clear();

void copy (const Scene & source);

};

#endif 

