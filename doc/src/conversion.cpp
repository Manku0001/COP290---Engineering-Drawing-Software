#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <math.h>
#include "graph.h"
using namespace std;

class conversion{
public:
	void isometric(vector<vector<co_ordinates_2D> > outgraphs2 ,vector<string> edges1,vector<string> edges2,vector<string> edges3){
		
		/*! It checks for any inconsistency in the data given ,i.e. incompatible views etc in the source
		  graph(outgraphs2).
		* The 3D graph is then generated using point to point correspondence given in the input.
		* After the input given is verified for consistency and the 3D-graph is generated, the user is given a choice to see
		  the isometric view or view along a general line of sight.
		* If the user wants a general line of sight, he/she has to input the direction vectors of the
		  line of view.
		* After the viewing direction is decided, the co-ordinates stored in the graph are rotated and stored
		  in a .txt file in a renderable format for QT and then the control is returned to main function.*/
	}
}