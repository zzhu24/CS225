#include "rgbapixel.h"
#include <cstdint>
RGBAPixel::RGBAPixel (){
red = 255;
blue = 255;
green = 255;
alpha = 255;
} 	


RGBAPixel::RGBAPixel (uint8_t red1, uint8_t green1, uint8_t blue1)
{
red = red1;
blue = blue1;
green = green1;
alpha = 255;
} 	


