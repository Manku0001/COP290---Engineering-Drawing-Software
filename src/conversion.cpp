#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <math.h>
#include "../include/graph.h"
#include "../include/conversion.h"
using namespace std;

void tokenize1 (string a,vector<string> &vect){
	string token,token2;
	if(a.find('&')!= std::string::npos){
 		token = a.substr(0, a.find('&'));
 		token2 = a.substr(a.find('&')+1,a.length());
 		vect.push_back(token);
 		tokenize1(token2,vect);
	}
	else vect.push_back(a);
}

void isometric(vector<vector<co_ordinates_2D> > outgraphs2 ,vector<string> edges1,vector<string> edges2,vector<string> edges3){
	vector<string> vertices1,vertices2,vertices3,edges;
	float maxz = -100000;
	vector<co_ordinates_3D> gray;
	map<string,int> hash1,hash2,hash3;
	ofstream outfile;
	outfile.open("output_2D.txt");
	int n1 =0;
	for(int i=0;(unsigned)i<outgraphs2.at(0).size();i++){
		tokenize1(outgraphs2.at(0).at(i).point,vertices1);
	}
	for(int i=0;(unsigned)i<outgraphs2.at(1).size();i++){
		tokenize1(outgraphs2.at(1).at(i).point,vertices2);
	}
	for(int i=0;(unsigned)i<outgraphs2.at(2).size();i++){
		tokenize1(outgraphs2.at(2).at(i).point,vertices3);
	}
	if(vertices1.size()!=vertices2.size() || vertices2.size()!=vertices3.size() || vertices1.size()!=vertices3.size()){
		cout << "error" << endl;
	}
	else{
		for(int i=0;(unsigned)i<vertices1.size();i++){
			if(find(vertices2.begin(), vertices2.end(), vertices1.at(i)) != vertices2.end()){
				if(find(vertices3.begin(), vertices3.end(), vertices1.at(i)) == vertices2.end()) cout << "error" << endl;
			}
			else cout << "error" << endl;
		}
	}
	for(int i=0;(unsigned)i<outgraphs2.at(0).size();i++){
		vector<string> temp1;
		tokenize1(outgraphs2.at(0).at(i).point,temp1);
		for(int p=0;(unsigned)p<temp1.size();p++){
			co_ordinates_3D aa;
			aa.point = temp1.at(p);
			aa.x = outgraphs2.at(0).at(i).c1;
			aa.y = outgraphs2.at(0).at(i).c2;
			hash1[temp1.at(p)] = n1;
			n1++;
			gray.push_back(aa);
		}
	}
	for(int i=0;(unsigned)i<outgraphs2.at(1).size();i++){
		vector<string> temp1;
		tokenize1(outgraphs2.at(1).at(i).point,temp1);
		for(int p=0;(unsigned)p<temp1.size();p++){
			co_ordinates_3D aa;
			if(gray.at(hash1[temp1.at(p)]).y == outgraphs2.at(1).at(i).c1) gray.at(hash1[temp1.at(p)]).z = outgraphs2.at(1).at(i).c2;
			else cout << "error" << endl;
		}
	}
	for(int i=0;(unsigned)i<outgraphs2.at(2).size();i++){
		vector<string> temp1;
		tokenize1(outgraphs2.at(2).at(i).point,temp1);
		for(int p=0;(unsigned)p<temp1.size();p++){
			if(gray.at(hash1[temp1.at(p)]).x == outgraphs2.at(2).at(i).c2 && gray.at(hash1[temp1.at(p)]).z == outgraphs2.at(2).at(i).c1){}
			else cout << "error" << endl;
		}
	}
	for(int i=0;(unsigned)i<edges1.size();i++){
		string temp = edges1.at(i);
		reverse(temp.begin(),temp.end());
		if(find(edges2.begin(), edges2.end(), edges1.at(i)) != edges2.end() || find(edges2.begin(), edges2.end(), temp) != edges2.end()){
			if(find(edges3.begin(), edges3.end(), edges1.at(i)) != edges3.end() || find(edges3.begin(), edges3.end(), temp) != edges3.end()){
				if(edges.size()==0) edges.push_back(edges1.at(i));
				else{
					if(find(edges.begin(), edges.end(), edges1.at(i)) != edges.end()){}
					else edges.push_back(edges1.at(i));
				}
			}
		}
	}
	float a,b,c,theta_x,theta_y;
	int fa;
	cout << "Enter 1 to have default line of view (1,1,1) and 2 for other: ";
	cin >> fa;
	if(fa==1){
		a = 1;
		b = 1;
		c = 1;
	}
	else{
		cout << "Enter the x-component of the line of view:";
		cin >> a;
		cout << "Enter the y-component of the line of view:";
		cin >> b;
		cout << "Enter the z-component of the line of view:";
		cin >> c;
	}
	if(b!=0) theta_x = -1*((fabs(b))/b)*acos(c/(sqrt(b*b + c*c)));
	else theta_x = 0;
	if(a!=0) theta_y = ((fabs(a))/a)*acos(sqrt(b*b+c*c)/sqrt(a*a+b*b+c*c));
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
	for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            temp2[i][j] = 0 ;
            for (int k = 0; k < 4; k++){
                temp2[i][j] += rotationy[i][k]*rotationx[k][j];
            }
        }
    }
    string apa;
    for(int i=0; (unsigned)i < gray.size();i++){
    	float cof[4] = {};
        float x = gray.at(i).x;
    	float y = gray.at(i).y;
    	float z = gray.at(i).z;
        float mat[4] = {x,y,z,-1};
    	for (int j = 0; j < 4; j++){
            cof[j] =0;
            for (int k = 0; k < 4; k++){
               	cof[j] += temp2[j][k]*mat[k];
            }
    	}
    	gray.at(i).x = cof[0];
    	gray.at(i).y = cof[1];
    	gray.at(i).z = cof[2];
    	if(cof[2]-maxz>0.001){
    		maxz = cof[2];
    		apa = gray.at(i).point;
    	}
    	else if(cof[2]-maxz<0.001 && cof[2]-maxz>-0.001){
    		maxz = cof[2];
    		apa += gray.at(i).point;	
    	}
    }
    //cout << apa << endl;
	outfile << edges.size() << endl;
	for(int j=0;(unsigned)j<gray.size();j++) {
		for(int jj=0;(unsigned)jj<edges.size();jj++){
			string s1 = edges.at(jj).substr(0,edges.at(jj).find(" "));
			string s2 = edges.at(jj).substr(edges.at(jj).find(" ")+1,edges.at(jj).length());
			if(gray.at(j).point.compare(s1)==0){
				outfile << gray.at(j).point << " " << setprecision(4) <<gray.at(j).x << " " << setprecision(4)<<gray.at(j).y /*<< " " << setprecision(3)<<gray.at(j).z*/ << " ";
				outfile << gray.at(hash1[s2]).point << " " << setprecision(4) << gray.at(hash1[s2]).x << " " <<  setprecision(4) << gray.at(hash1[s2]).y << /*" " << setprecision(4) << gray.at(hash1[s2]).z <<*/ endl;
			}
		}
	}
	outfile.close();
}
