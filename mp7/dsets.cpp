/* Your code here! */

#include "dsets.h"

void DisjointSets::addelements (int num){
	for(int i = 0; i < num; i++){
		upNodes.push_back(-1);}
	return;}

int DisjointSets::find (int elem){
	if(upNodes[elem] < 0){
		return elem;}
	else{
		return upNodes[elem] = find(upNodes[elem]);}}

void DisjointSets::setunion(int a, int b){
	int nodea = find(a);
	int nodeb = find(b);
	if(nodea == nodeb){
		return;}
	
	//start to do the union
	int newSize = upNodes[nodea]+upNodes[nodeb];
	if(upNodes[nodea]<=upNodes[nodeb]){
		upNodes[nodeb] = nodea;
		upNodes[nodea] = newSize;}
	else{
		upNodes[nodea] = nodeb;
		upNodes[nodeb] = newSize;}}
