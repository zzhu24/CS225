#include "image.h"
using namespace std;

//*(*this)(x,y) show the number expressing the color
//(*this)(x,y) point to the pixel

//Flips the image about a vertical line through its center by swapping pixels. 
void  Image :: flipleft ()
{for(size_t y=0;y < height();y++)
{RGBAPixel temp;
for (size_t x=0,dx= (width()-1);x<=dx;x++,dx--)
{temp= *(*this)(x,y);
*(*this)(x,y)=*(*this)(dx,y);
*(*this)(dx,y)=temp;}}}

//Adds to the red, green, and blue parts of each pixel in the image. 
void Image::adjustbrightness(int rednew, int greennew, int bluenew){
int r,g,b;
for (size_t i = 0 ; i < this->width() ; i ++)
{for (size_t j = 0 ; j < this->height() ; j ++)
{r = (*this)(i,j)->red + rednew;
g = (*this)(i,j)->green + greennew;
b = (*this)(i,j)->blue + bluenew;
if(r > 255) r = 255;
if(g > 255) g = 255;
if(b > 255) b = 255;
if(r < 0) r = 0;
if(g < 0) g = 0;
if(b < 0) b = 0;
(*this)(i,j)->red = r;
(*this)(i,j)->green = g;
(*this)(i,j)->blue = b;}}}

//Makes each RGB component of each pixel iequal to 255 minus its original value. 
void Image::invertcolors ()
{for(size_t y=0;y < height();y++)
{for (size_t x=0;x < width();x++)
{int newr=255-(*this)(x,y)->red;
int newg=255-(*this)(x,y)->green;
int newb=255-(*this)(x,y)->blue;
(*this)(x,y)->red = newr;
(*this)(x,y)->green = newg;
(*this)(x,y)->blue = newb;}}}
