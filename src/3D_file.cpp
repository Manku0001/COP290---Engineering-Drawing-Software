#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <math.h>
#include "../include/3D_file.h"
#include "../include/graph.h"
using namespace std;
    
string get_3D_graph(vector<co_ordinates_3D> &c,vector<string> &faces){
	map<string,int> myhash;
	string vertex,n1,n2;
	int nv,ne;
	string s;
	float nx,ny,nz;
	ifstream infile;
	ofstream outfile;
	outfile.open("temp.txt");
	cout << "Enter the name of the input file: ";
	cin >> s;
	char abcs[s.length()];
	for(int i=0;(unsigned)i<s.length();i++) abcs[i] = s[i]; 
	float maxx=0,maxy=0,maxz=0,minx=0,miny=0,minz=0;
	infile.open(abcs);
	if (!infile){
    	cout << "There is no such file." << endl;
    	exit(1);   
	}
	infile >> nv;
	co_ordinates_3D c1;
	vector <string> co;
	for(int i=0;i<nv;i++){
		infile >> vertex >> nx >> ny >> nz;
		if(i==0){
			maxx = nx;
			minx = nx;
		}
		if(i==0){
			maxy = ny;
			miny = ny;
		}
		if(i==0){
			maxz = nz;
			minz = nz;
		}
		if(nx > maxx) maxx = nx;
		if(ny > maxy) maxy = ny;
		if(nz > maxz) maxz = nz;
		if(nx < minx) minx = nx;
		if(ny < miny) miny = ny;
		if(nz < minz) minz = nz;
		myhash[vertex] = i;
		c1.point = vertex;
		c1.x = nx;
		c1.y = ny;
		c1.z = nz;
		c.push_back(c1);
	}
	float maxz1= maxz,maxx1 = maxx,maxy1 =maxy;
	float minz1 = minz,miny1 = miny,minx1 = minx;
	float a = 1, b = 1, cn = 1,theta_x,theta_y;
	if(b!=0) theta_x = -1*((fabs(b))/b)*acos(cn/(sqrt(b*b + cn*cn)));
	else theta_x = 0;
	if(a!=0) theta_y = ((fabs(a))/a)*acos(sqrt(b*b+cn*cn)/sqrt(a*a+b*b+cn*cn));
	else theta_y = 0;
    float ctheta_x = cos(theta_x);
    float ctheta_y = cos(theta_y);
    float stheta_x = sin(theta_x);
    float stheta_y = sin(theta_y);
    float rotationx[4][4]={0},rotationy[4][4]={0},temp2[4][4] = {0};
    rotationx[0][0] = 1;
	rotationx[3][3] = 1;
	rotationx[1][1] = ctheta_x;
	rotationx[2][2] = ctheta_x;
	rotationx[1][2] = stheta_x;
	rotationx[2][1] = -1*stheta_x;
	rotationy[0][0] = ctheta_y;
	rotationy[1][1] = 1;
	rotationy[2][2] = ctheta_y;
	rotationy[3][3] = 1;
	rotationy[0][2] = -1*stheta_y;
	rotationy[2][0] = stheta_y;
	infile >> ne;
	outfile << ne << endl;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			temp2[i][j] =0;
			for(int k=0;k<4;k++){
				temp2[i][j] += rotationy[i][k]*rotationx[k][j];
			}
		}
	}
    string aa1[ne],aa2[ne];
    float cof[ne][4] = {0},cof1[ne][4] ={0};
    string apa;
	for(int j=0;j<ne;j++){
		infile >> n1 >> n2;
		c.at(myhash[n1]).solidedges.push_back(n2);
		c.at(myhash[n2]).solidedges.push_back(n1);
		aa1[j] = c.at(myhash[n1]).point;
		aa2[j] = c.at(myhash[n2]).point;
        float x = c.at(myhash[n1]).x;
    	float y = c.at(myhash[n1]).y;
    	float z = c.at(myhash[n1]).z;
    	float x1 = c.at(myhash[n2]).x;
    	float y1 = c.at(myhash[n2]).y;
    	float z1 = c.at(myhash[n2]).z;
        float mat[4] = {x,y,z,-1};
        float mat1[4] = {x1,y1,z1,-1};
    	for (int k = 0; k < 4; k++){
            cof[j][k] =0;
            cof1[j][k] =0;
            for (int r = 0; r < 4; r++){
               	cof[j][k] += temp2[k][r]*mat[r];
               	cof1[j][k] += temp2[k][r]*mat1[r];
            }
        }
        if(cof[j][0]>=maxx) maxx = cof[j][0];
    	if(cof[j][1]>=maxy) maxy = cof[j][1];
    	if(cof[j][2]-maxz>0.001){
    		maxz = cof[j][2];
    		apa = c.at(myhash[n1]).point;
    	}
    	else if(cof[j][2]-maxz<0.001 && cof[j][2]-maxz>-0.001){
    		maxz = cof[j][2];
    		apa += c.at(myhash[n1]).point;	
    	} 
    	if(cof1[j][0]>=maxx) maxx = cof1[j][0];
    	if(cof1[j][1]>=maxy) maxy = cof1[j][1];
    	if(cof1[j][2]-maxz>0.001){
    		maxz = cof1[j][2];
    		apa = c.at(myhash[n2]).point;
    	}
    	else if(cof1[j][2]-maxz<0.001 && cof1[j][2]-maxz>-0.001){
    		maxz = cof1[j][2];
    		apa += c.at(myhash[n2]).point;	
    	}     
	}
	int bs;
	infile >> bs;
	string fa;
	string lala;
	int flag;
	for(int xx=0;xx<bs;xx++){
		flag = 0;
		infile >> fa;
		faces.push_back(fa);
		for(int poo=0;(unsigned) poo< apa.length();poo++){
			if(fa.find(apa.at(poo))!= std::string::npos){
				flag++;
			}
		}
		if(flag==apa.length()){
			lala += fa;
		} 
	}
	
	float s1,s2,s3,s4,t1,t2,t3;
	t1 = minx;
	minx = minx-t1;
	maxx = maxx-t1;
	t2 = miny;
	miny = miny-t2;
	maxy = maxy-t2;
	t3 = minz;
	minz = minz-t3;
	maxz = maxz-t3;
    if(maxx>550) s1 = 550/maxx;
	else if(maxx < 100) s1 = 400/maxx;
    else s1 = 1;
   	if(maxy>550) s2 = 550/maxy;
    else if(maxy < 100) s2 = 400/maxy;
   	else s2 = 1;
   	if(maxz>550) s3 = 550/maxz;
   	else if(maxz < 100) s3 = 400/maxz;
   	else s3 = 1;
    if(s1<=s2 && s1 <= s3) s4 = s1;
   	else if(s2<=s3 && s2<=s1) s4 = s2;
   	else if(s3 <= s1&& s3 <= s2) s4 = s3;
   	else s4 = s1;
   	for(int po=0;po<ne;po++){
   		cof[po][0] = (cof[po][0]-t1)*s4;
        cof[po][1] = (cof[po][1]-t2)*s4;
        cof1[po][0] = (cof1[po][0]-t1)*s4;
        cof1[po][1] = (cof1[po][1]-t2)*s4;
		outfile << aa1[po] << " " << cof[po][0] << " " << cof[po][1] << " " << aa2[po] << " " << cof1[po][0] << " " << cof1[po][1] << endl;
   	}
	c1.x = maxx1;
	c1.y = maxy1;
	c1.z = maxz1;
	c.push_back(c1);
	c1.x = minx1;
	c1.y = miny1;
	c1.z = minz1;
	c.push_back(c1);
	infile.close();
	outfile.close();
	return lala;
}