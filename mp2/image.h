#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "rgbapixel.h"
#include "png.h"

class Image : public PNG
{public:
void invertcolors();
void adjustbrightness(int rednew, int greennew, int bluenew);
void flipleft();};

#endif
