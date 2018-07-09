#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>
#include "../include/graph.h"
#include "../include/projection.h"
using namespace std;

void projections(vector<co_ordinates_3D> &c,vector<vector<co_ordinates_2D> > &graphs){
	vector<co_ordinates_2D> proj1,proj2,proj3;
	for(int i=0;(unsigned)i<c.size()-2;i++){
		co_ordinates_2D coxy,coyz,coxz;
		string temp = c.at(i).point;
		float tx = c.at(i).x;
		float ty = c.at(i).y;
		float tz = c.at(i).z;
		coxy.point = temp;
		coyz.point = temp;
		coxz.point = temp;
		coxy.c1 = tx;
		coxy.c2 = ty;
		coyz.c1 = ty;
		coyz.c2 = tz;
		coxz.c1 = tx;
		coxz.c2 = tz;
		for(int j=0;(unsigned)j<c.at(i).solidedges.size();j++){
			coxy.solidedges.push_back(c.at(i).solidedges.at(j));
			coyz.solidedges.push_back(c.at(i).solidedges.at(j));
			coxz.solidedges.push_back(c.at(i).solidedges.at(j));
		}
		proj1.push_back(coxy);
		proj3.push_back(coxz); 
		proj2.push_back(coyz);
	}
	graphs.push_back(proj1);
	graphs.push_back(proj3);
	graphs.push_back(proj2);
}