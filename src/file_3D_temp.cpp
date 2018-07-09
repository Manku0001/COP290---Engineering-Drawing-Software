#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <fstream>
#include "../include/graph.h"
#include "../include/file_3D_temp.h"
using namespace std;

void write_in_out_file(vector<vector<co_ordinates_2D> > outgraphs,int choice){
	int l;
	map<string,int> haha;
	if(choice==1) l=3;
	else l=1;
	ofstream outfile;
	outfile.open("output_3D.txt");
	for(int i=0;i<l;i++){
		vector<co_ordinates_2D> upco;
		map<string,string> myhash1;
		map<string,int> myhash2;
		vector<string> vertices,edges;
		for(int j=0;(unsigned)j < outgraphs.at(i).size();j++){
			string da = outgraphs.at(i).at(j).point;
			int temp[outgraphs.at(i).size()];
			for(int h=j+1;(unsigned)h<outgraphs.at(i).size();h++){
				if(abs(outgraphs.at(i).at(j).c1 - outgraphs.at(i).at(h).c1) < 0.00001  && abs(outgraphs.at(i).at(j).c2 - outgraphs.at(i).at(h).c2)<0.00001 && myhash2[outgraphs.at(i).at(h).point] !=1){
					da = da + "&" + outgraphs.at(i).at(h).point;
					myhash2[outgraphs.at(i).at(h).point] = 1;
					temp[h] = 1;
				}
			}
			co_ordinates_2D va;
			va.c1 = outgraphs.at(i).at(j).c1;
			va.c2 = outgraphs.at(i).at(j).c2;
			va.point = da;
			if(myhash2[da]!=1){
				myhash1[outgraphs.at(i).at(j).point] = da;
				for(int p=j+1;(unsigned)p<outgraphs.at(i).size();p++){
					if(temp[p] == 1) myhash1[outgraphs.at(i).at(p).point] = da;
				}
				haha[da] = upco.size();
				upco.push_back(va);
				vertices.push_back(da);
			}
		}
		for(int j=0;(unsigned)j<outgraphs.at(i).size();j++){
			for(int k=0;(unsigned)k<outgraphs.at(i).at(j).solidedges.size();k++){
				if(myhash1[outgraphs.at(i).at(j).point].compare(myhash1[outgraphs.at(i).at(j).solidedges.at(k)])!=0 && (myhash1[outgraphs.at(i).at(j).point]).empty()==false && (myhash1[outgraphs.at(i).at(j).solidedges.at(k)]).empty()== false){
					string pa = myhash1[outgraphs.at(i).at(j).point] + " " + myhash1[outgraphs.at(i).at(j).solidedges.at(k)];
					string si = myhash1[outgraphs.at(i).at(j).solidedges.at(k)] + " " + myhash1[outgraphs.at(i).at(j).point]; 
					if(edges.size()==0) edges.push_back(pa);	
					else{
						bool ma = true;
						for(int p = 0; (unsigned)p< edges.size();p++){
							if(pa.compare(edges.at(p))==0 || si.compare(edges.at(p))==0) ma = false;
						}
						if(ma==true) edges.push_back(pa);		
					}
				}
			}
		}
		outfile << edges.size() << endl;
		for(int px = 0; (unsigned)px < upco.size();px++){
			for(int l1=0;(unsigned)l1<edges.size();l1++){
				string s1 = edges.at(l1);
				string s2 = s1.substr(0,s1.find(" "));
				string s3 = s1.substr(s1.find(" ")+1,s1.length());
				if(upco.at(px).point.compare(s2)==0){
					outfile << upco.at(px).point << " ";
					outfile  << setprecision(4) << upco.at(px).c1 << " ";
					outfile  << setprecision(4) << upco.at(px).c2 << " ";
					int nn = haha[s3];
					outfile << upco.at(nn).point << " ";
					outfile  << setprecision(4) << upco.at(nn).c1 << " ";
					outfile  << setprecision(4) << upco.at(nn).c2 << endl;
				}
			}
		}
		outfile << endl;
	}
	outfile.close();
}