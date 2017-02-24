EXENAME = testimage
EXENAME2 = testscene
OBJS = testimage.o image.o png.o rgbapixel.o
OBJS2 = testscene.o image.o png.o rgbapixel.o scene.o


CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : $(EXENAME) $(EXENAME2)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)
$(EXENAME2) : $(OBJS2)
	$(LD) $(OBJS2) $(LDFLAGS) -o $(EXENAME2)

testimage.o : testimage.cpp image.o
	$(CXX) $(CXXFLAGS) testimage.cpp

image.o : image.cpp image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) image.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp 

testscene.o: testscene.cpp rgbapixel.h png.h image.h scene.h
	$(CXX) $(CXXFLAGS) testscene.cpp

scene.o : scene.cpp scene.h rgbapixel.h png.h image.h
	$(CXX) $(CXXFLAGS) scene.cpp

clean :
	-rm -f *.o $(EXENAME) 
