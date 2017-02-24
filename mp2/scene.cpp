#include "scene.h"
#include <string>
#include <iostream>
#include "image.h"
#include <stdint.h>
using namespace std;


Scene::Scene (int max)
{
maxlay = max;
imagepointersarray = new Image * [maxlay];
x = new int [maxlay];
y = new int [maxlay];
for (int i=0; i<maxlay; i++){imagepointersarray [i]=NULL; x[i]=0; y[i]=0;}
}


Scene::Scene (const Scene & source){
copy(source);
}

Scene :: ~Scene(){
if(imagepointersarray!=NULL) clear();
}

void Scene::copy( const Scene & source){

this->maxlay = source.maxlay;
this->imagepointersarray = new Image* [maxlay];
this->x = new int [maxlay];
this->y = new int [maxlay];
for (int i=0; i<maxlay; i++){
imagepointersarray[i]=NULL; 
x[i]=0; 
y[i]=0;
}
for (int i=0;i<maxlay;i++){

if (source.imagepointersarray[i]!=NULL)
{
imagepointersarray[i]=new Image(*(source.imagepointersarray[i]));

//*(imagepointersarray[i])=*(source.imagepointersarray[i]);//each source's image pointer give to-> this's each image pointer
this->x[i]=source.x[i];
this->y[i]=source.y[i];
}
}//actually all "this->" can be removed. 
}


const Scene & Scene :: operator = (const Scene & source){
//(1)check for self assignment 
if (this != &source)
//(2)if not: deletes everting in this Scene has allocated
{
clear();
//(3)then copy
copy(source);
}
//(4)return helpful value: this is for three or more assignment use
return (*this); //this is not local variable!! so return a REFERENCE like this is OK! it will not disappare after the function.


}


void Scene::clear(){
//clear() use delete [] (just like use) to delete array
// use delete to delete pointer;
for (int i=0; i<maxlay; i++){// for every pointers in imagepointersarray YOU NEED TO DELETE EACH OF THEM, at sigle time.
delete imagepointersarray[i];
imagepointersarray[i]=NULL;
}
delete [] imagepointersarray;
imagepointersarray=NULL;
delete [] y; 
y=NULL;
delete [] x;
x=NULL;

}



void Scene :: changemaxlayers (int newmax){
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!VERY IMPORTANT!!!!!!!!!!!!!!
//case 1: probably beyongd the limit:
if (newmax==maxlay) return;

if (newmax<maxlay){
for (int i = newmax; i<maxlay; i++ ){
if (imagepointersarray [i]!=NULL) 
{cout<<"invalid newmax"<<endl; return;}
}
}
//the we creat new space for copy (therefore set temp array pointers) !!!remember to delete the old one after use.
Image **temp_imagepointersarray = new Image * [newmax];
int *temp_x = new int [newmax], *temp_y = new int [newmax];

//case 2.1: newmax < maxlay, so, use "i<newmax" as limit 
if (newmax<maxlay){
for (int i=0; i<newmax; i++){
if (imagepointersarray[i]!=NULL){
temp_imagepointersarray[i] = imagepointersarray [i];
temp_x[i]=x[i];
temp_y[i]=y[i];
}//end if
else {
temp_imagepointersarray[i] = NULL;
temp_x[i]=0;
temp_y[i]=0;
}//end else
}//end for
}//end if_2.1

//case 2.1: newmax > maxlay, so, use "i<maxlay" as limit 
else if (newmax>maxlay){
for (int i=0; i<maxlay; i++){
if (imagepointersarray[i]!=NULL){
temp_imagepointersarray[i] = imagepointersarray [i];
temp_x[i]=x[i];
temp_y[i]=y[i];
}//end if
else {
temp_imagepointersarray[i] = NULL;
temp_x[i]=0;
temp_y[i]=0;
}//end else
}//end for 2.2-1
for (int i=maxlay; i<newmax; i++){
temp_imagepointersarray[i] = NULL;
temp_x[i]=0;
temp_y[i]=0;
}//end for 2.2-2
}//end if_2.2

//delete old space
for (int i=0; i<maxlay; i++){
delete imagepointersarray[i];
imagepointersarray[i]=NULL;
}//end for_delete arraypointers
delete [] x;
delete [] y;
delete [] imagepointersarray;

//re_assign
imagepointersarray=temp_imagepointersarray; 
x=temp_x;
y=temp_y;
//DONT'T FORGET THE maxlay!
maxlay=newmax;
}


void Scene ::addpicture (const char * FileName, int index, int x, int y){
if (index<0||index>=maxlay){cout << "index out of bounds" << endl; return;}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//YOU NEED TO FREEE THE MEMORY!!!
if (imagepointersarray [index]!=NULL){delete imagepointersarray[index];}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
imagepointersarray[index]=new Image;//why it is new image: because imagepointersarray[I] is an image pointer. This is just like Object * x; x=new Object;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
imagepointersarray[index]-> readFromFile(FileName);
this-> x[index] = x;
this-> y[index] = y;
}

void Scene :: changelayer (int index, int newindex){
if (index<0||index>=maxlay||newindex<0||newindex>=maxlay)
{cout << "invalid index" << endl;return;}
if (index==newindex) return;
if (imagepointersarray[newindex]!=NULL){
delete imagepointersarray[newindex];
}
imagepointersarray[newindex]=imagepointersarray[index];
//x&y also need to move:
x[newindex]=x[index];
y[newindex]=y[index];
//remember to delete old memory
imagepointersarray[index]=NULL;
}

void Scene :: translate (int index, int xcoord, int ycoord){
if (index<0||index>=maxlay||imagepointersarray[index]==NULL)
{cout << "invalid index" << endl;return;}
x[index]=xcoord;
y[index]=ycoord;
}

void Scene ::deletepicture (int index) {
if (index<0||index>=maxlay||imagepointersarray[index]==NULL)
{cout << "invalid index" << endl;return;}
delete imagepointersarray[index];
imagepointersarray[index]=NULL;
//NOT!!delete  y[index]; 
//NOT!!delete  x[index];
y[index]=0;
x[index]=0;
}

Image * Scene::getpicture (int index)const{
if (index<0||index>=maxlay||imagepointersarray[index]==NULL)
{cout << "invalid index" << endl;return NULL;}
return imagepointersarray[index];
}

Image Scene ::drawscene () const{ //this const means the return type is const
Image returnimage;
size_t wit=0 ;
size_t height=0;
size_t w=0 ;
size_t h=0; 
for (int i=0; i<maxlay;i++){
if (imagepointersarray[i]!=NULL) {

w = imagepointersarray[i]->width() +x[i];
h = imagepointersarray[i]->height() +y[i];
if (w>wit) wit=w;
if (h>height) height=h;
}
}//end for
returnimage.resize(wit,height);

for(int i=0;i<maxlay;i++){
if (imagepointersarray[i]!=NULL) {
for (size_t a=0;a<imagepointersarray[i]->height();a++){
for(size_t b=0;b<imagepointersarray[i]->width();b++){
*(returnimage(x[i]+b,y[i]+a))=*((*imagepointersarray[i])(b,a));
}
} 
}
}//end for

return  returnimage;
}
