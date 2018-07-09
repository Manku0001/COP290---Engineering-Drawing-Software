#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <math.h>
#include "../include/graph.h"
#include "../include/2D_file.h"
using namespace std;

void tokenize (string a,vector<string> &vect){
	string token,token2;
	if(a.find('&')!= std::string::npos){
 		token = a.substr(0, a.find('&'));
 		token2 = a.substr(a.find('&')+1,a.length());
 		vect.push_back(token);
 		tokenize(token2,vect);
	}
	else vect.push_back(a);
}

string get_2D_graph(vector<vector<co_ordinates_2D> > &cz,vector<string> &edges1,vector<string> &edges2,vector<string> &edges3){
	vector<co_ordinates_2D> proj1,proj2,proj3;
	map<string,int> myhash1,myhash2,myhash3;
	string vertex,n1,n2,s;
	int nv,ne;
	float c1,c2;
	ifstream infile;
	cout << "Enter the name of the input file: ";
	cin >> s;
	char abcs[s.length()];
	for(int i=0;(unsigned)i<s.length();i++){
		abcs[i] = s[i]; 
	}
	infile.open(abcs);
	if (!infile){
    	cout << "There is no such file." << endl;
    	exit(1);   
	}
	infile >> nv;
	co_ordinates_2D c;
	for(int i=0;i<nv;i++){
		infile >> vertex >> c1 >> c2;
		myhash1[vertex] = i;
		c.point = vertex;
		c.c1 = c1;
		c.c2 = c2;
		proj1.push_back(c);
	}
	infile >> ne;
	for(int i=0;i<ne;i++){
		infile >> n1 >> n2;
		vector<string> temp1,temp2;
		tokenize(n1,temp1);
		tokenize(n2,temp2);
		for(int i=0;(unsigned)i<temp1.size();i++){
			for(int j=i+1;(unsigned)j<temp1.size();j++){
				edges1.push_back(temp1.at(i) + " " + temp1.at(j));
			}
			for(int k=0;(unsigned)k<temp2.size();k++){
				edges1.push_back(temp1.at(i) + " " + temp2.at(k));
			}
		}
		for(int i=0;(unsigned)i<temp2.size();i++){
			for(int j=i+1;(unsigned)j<temp2.size();j++){
				edges1.push_back(temp2.at(i) + " " + temp2.at(j));
			}	
		}
	}
	infile >> nv;
	for(int i=0;i<nv;i++){
		infile >> vertex >> c1 >> c2;
		myhash2[vertex] = i;
		c.point = vertex;
		c.c1 = c1;
		c.c2 = c2;
		proj2.push_back(c);
	}
	infile >> ne;
	for(int i=0;i<ne;i++){
		infile >> n1 >> n2;
		vector<string> temp1,temp2;
		tokenize(n1,temp1);
		tokenize(n2,temp2);
		for(int i=0;(unsigned)i<temp1.size();i++){
			for(int j=i+1;(unsigned)j<temp1.size();j++){
				edges2.push_back(temp1.at(i) + " " + temp1.at(j));
			}
			for(int k=0;(unsigned)k<temp2.size();k++){
				edges2.push_back(temp1.at(i) + " " + temp2.at(k));
			}
		}
		for(int i=0;(unsigned)i<temp2.size();i++){
			for(int j=i+1;(unsigned)j<temp2.size();j++){
				edges2.push_back(temp2.at(i) + " " + temp2.at(j));
			}	
		}
	}
	infile >> nv;
	for(int i=0;i<nv;i++){
		infile >> vertex >> c1 >> c2;
		myhash3[vertex] = i;
		c.point = vertex;
		c.c1 = c1;
		c.c2 = c2;
		proj3.push_back(c);
	}
	infile >> ne;
	for(int i=0;i<ne;i++){
		infile >> n1 >> n2;
		vector<string> temp1,temp2;
		tokenize(n1,temp1);
		tokenize(n2,temp2);
		for(int i=0;(unsigned)i<temp1.size();i++){
			for(int j=i+1;(unsigned)j<temp1.size();j++){
				edges3.push_back(temp1.at(i) + " " + temp1.at(j));
			}
			for(int k=0;(unsigned)k<temp2.size();k++){
				edges3.push_back(temp1.at(i) + " " + temp2.at(k));
			}
		}
		for(int i=0;(unsigned)i<temp2.size();i++){
			for(int j=i+1;(unsigned)j<temp2.size();j++){
				edges3.push_back(temp2.at(i) + " " + temp2.at(j));
			}	
		}
	}
	string lal;
	infile >> lal;
	cz.push_back(proj1);
	cz.push_back(proj2);
	cz.push_back(proj3);
	return lal;
} 