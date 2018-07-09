#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "graph.h"
using namespace std;
class trans{
public:
	int transform(vector<co_ordinates_3D> &graph ,vector<string> faces,vector<string> &points){
		/*! In this function the user selects the operation he/she wants to do by choosing various modes :
		* 1. Firstly, the user has to choose whether he wants orthographic views or view on a specified plane.
		* 2. If the user wants orthographic views, he/she will be prompted to input whether they want views 
		       without any rotation or with rotation. 
		* 3. If the user wants the views without any rotation, then the co-ordinates stored in the graph 
		         are only translated and/or scaled to make them renderable.
		* 4. If the user wants the views with rotation, he/she is again prompted to input how they want 
		         the rotation to be done, i.e., whether the want rotation about xyz-axes or they want
		         to rotate about a general axis.  
		* 5. If the user wants to rotate about xyz-axes then the user is prompted to give the angles 
		           rotation and the co-ordinates stored in the graph are rotated, translated and scaled 
		           accordingly to make them renderable.
		* 6. If the user wants to rotate about a random axis then the user is prompted to give the  
		           direction vectors of the axis along with the angle by which they wants the figure to 
		           be rotated and then the co-ordinates stored in the graph are rotated, translated and
		           scaled accordingly to make them renderable.
		* 7. If the user wants the view of the figure on a specified plane, the he/she is prompted to 
		      enter the normal vector of the plane on which he wants the view. The co-ordinates in the 
		      graph are then rotated, scaled and translated accordingly to make them renderable. */

	}
}