#include "rgbapixel.h"
#include "png.h"
 using namespace std;
PNG rotate (PNG inImage){
PNG outImage(inImage.width(), inImage.height());
	for(size_t x=0;x<inImage.width();x++){
		for (size_t y=0;y<inImage.height();y++){
			*outImage(x,y)=*inImage(inImage.width()-1-x,inImage.height()-1-y);
			
		}
	}
return outImage;
};

int main(){
PNG in ("in.png");
PNG outImage=rotate(in);
outImage.writeToFile("out.png");
return 0;
}
