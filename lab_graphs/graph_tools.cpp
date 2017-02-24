/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
	vector <Vertex> verticesOrder = graph.getVertices();//get all the vertices
	int path = 0;
	for(size_t i = 0; i < verticesOrder.size(); i++){//set all as unexplored
		graph.setVertexLabel(verticesOrder[i], "UNEXPLORED");}
	vector <Edge> edgesOrder = graph.getEdges();
	for(size_t i = 0; i < edgesOrder.size(); i++){//set the two side of every edge
		graph.setEdgeLabel(edgesOrder[i].source, edgesOrder[i].dest, "UNEXPLORED");}
	queue <Vertex> verticesList;
	unordered_map <Vertex, Vertex> upnodeList;
	verticesList.push(start);
	graph.setVertexLabel(start, "VISITED");	
	while(verticesList.empty() == false){//after dequeue, we set as visited and check the adjacent edge and vertex, if the vertex is visited, the edge is set as cross, else we set the vertex as visited and the edge as discovered. then we go to check the second vertex of the queue
		Vertex temp = verticesList.front();
		verticesList.pop();
		vector <Vertex> adjacent = graph.getAdjacent(temp);
		for(size_t i = 0; i < adjacent.size(); i++){
			if(graph.getVertexLabel(adjacent[i]) == "UNEXPLORED"){
				graph.setEdgeLabel(temp, adjacent[i], "DISCOVERY");
				graph.setVertexLabel(adjacent[i], "VISITED");
				pair <Vertex, Vertex> pairVertex (adjacent[i], temp);
				upnodeList.insert(pairVertex);
				verticesList.push(adjacent[i]);}
			else if(graph.getEdgeLabel(temp, adjacent[i]) == "UNEXPLORED"){
				graph.setEdgeLabel(temp, adjacent[i], "CORSS");}}}
	while(end != start){//we aksi set an unorder//get through the unsorted map and find the unweighted distance
		graph.setEdgeLabel(end, upnodeList[end], "MINPATH");
		end = upnodeList[end];
		path ++;}
	return path;}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph & graph)
{
	vector <Vertex> vertices = graph.getVertices();//get through the unsorted map and find the unweighted distance
	for(size_t i = 0; i < vertices.size(); i++){//get all the vertices 
		graph.setVertexLabel(vertices[i], "UNEXPLORED");}
	vector <Edge> edges = graph.getEdges();//set all as unexplored/
	for(size_t i = 0; i < edges.size(); i++){//set the two side of every edge
		graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");}
	queue <Vertex> list;
	list.push(vertices[0]);
	graph.setVertexLabel(vertices[0], "VISITED");	
	vector <Vertex> compare = graph.getAdjacent(vertices[0]);
	int min = graph.getEdgeWeight(vertices[0], compare[0]);
	int curr = 0;
	Vertex one = vertices[0];
	Vertex two = compare[0];
	while(list.empty() == false){//also //after dequeue, we set as visited and check the adjacent edge and vertex, if the vertex is visited, the edge is set as cross, else we set the vertex as visited and the edge as discovered. then we go to check the second vertex of the queue
		Vertex temp = list.front();
		list.pop();
		vector <Vertex> adjacent = graph.getAdjacent(temp);
		for(size_t i = 0; i < adjacent.size(); i++){//also we want to find the minimum weight//also 
			if(graph.getVertexLabel(adjacent[i]) == "UNEXPLORED"){
				graph.setEdgeLabel(temp, adjacent[i], "DISCOVERY");
				graph.setVertexLabel(adjacent[i], "VISITED");
				curr = graph.getEdgeWeight(adjacent[i], temp);
				if(curr < min){
					min = curr;
					one = temp;
					two = adjacent[i];}
				list.push(adjacent[i]);}
			else if(graph.getEdgeLabel(temp, adjacent[i]) == "UNEXPLORED"){//after dequeue, we set as visited and check the adjacent edge and vertex, if the vertex is visited, the edge is set as cross, else we set the vertex as visited and the edge as discovered. then we go to check the second vertex of the queue
				graph.setEdgeLabel(temp, adjacent[i], "CORSS");
				curr = graph.getEdgeWeight(adjacent[i], temp);
				if(curr < min){//also we want to find the minimum weight if the vertex is already visited
					min = curr;
					one = temp;
					two = adjacent[i];}}}}
	
	graph.setEdgeLabel(one, two, "MIN");
	return min;}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
void GraphTools::findMST(Graph & graph)
{
	vector< Vertex > vertices = graph.getVertices();
	DisjointSets verticesList;
	verticesList.addelements(vertices.size());
	size_t count = 0;
//also we want to find the minimum weight if the vertex is already visited
	vector< Edge > edges = graph.getEdges();
	std::sort(edges.begin(), edges.end(), isSorted);
//in order to avoid loop// we use the dset to find the parent and go throught if the vertex
	for(size_t i = 0; i < edges.size() && count < vertices.size() - 1; i++){
		if(verticesList.find(edges[i].source) != verticesList.find(edges[i].dest)){
			verticesList.setunion(edges[i].source, edges[i].dest);
			graph.setEdgeLabel(edges[i].source, edges[i].dest, "MST");
			count++;}}}

bool GraphTools::isSorted (Edge one, Edge two) {
    return (one.weight < two.weight);}
