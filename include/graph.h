#include <bits/stdc++.h>
using namespace std;

#ifndef __GRAPH__
#define __GRAPH__
struct co_ordinates_3D{
	string point;
    float x,y,z;
    vector<string> solidedges;
};

struct co_ordinates_2D{
	string point;
	float c1,c2;
	vector<string> solidedges;
	vector<string> hiddenedges;
};
#endif
