#include <math.h>
#include <QtCore>
#include <QtGui>
#include <QString>
#define PI 3.1415926536
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "transform.h"
#include "2D_file.h"
#include "graph.h"
#include "conversion.h"
#include "file_3D_temp.h"
#include "projection.h"
#include "3D_file.h"
using namespace std;
using namespace Qt;


struct vertex{
   string f,g;  /*! Two vertices having an edge between them are stored along with their co-ordinated(2D). */
   float e,b,c,d;
};

/*! User Mode selection is done here. */
class Master{
public:
	void tokenize(string a, vector<string> &vect){
		/*! This function breaks a string into characters and store them in a vector named vect.*/
	}
	int main(){
		/*! The procedure that has been applied here is :
		* 1. Firstly, the user is prompted to input that in which mode he wants to work , 3D_to_2D mode or 2D_to_3D mode.
		* 2. In the second step, the user is directed to functions/methods in other files according to the choice made.
		* 3. When the processing in other files is done, the output file is rendered on a canvas using QT.*/
	}
}