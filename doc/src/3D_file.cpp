#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <math.h>
#include "graph.h"
using namespace std;

class _3D_file{
public:
	string get_3D_graph(vector<co_ordinates_3D> &c,vector<string> &faces){
		/*! Firstly, the user is prompted to input a file containing the 3D-figure and it is stored in a graph.
		* As we are generating 3D view along with the orthographic views, we applied certain transformations,
		  i.e. rotation, translation and scaling to get a renderable isometric view.
		* Then the faces which will be visible from the isometric view are generated and stored in a vector(faces).
		* The renderable isometric view generated is stored in a file so that the main function can render it.*/
	}
}