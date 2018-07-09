#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "../include/transform.h"
#include "../include/graph.h"
using namespace std;
#define PI 3.1415926536
int transform(vector<co_ordinates_3D> &graph ,vector<string> faces,vector<string> &points){
	float translation[4][4] = {0}; 
  string mx,my,mz;
	float rotationx[4][4] = {0};
	float rotationy[4][4] = {0};
  float rotationz[4][4] = {0};
	float temp2[4][4]={0},tempf[4][4] = {0};
	float a,b,c,a1,b1,c1;
	float s1,s2,s3,s;
	float t1,t2,t3;
	float theta_x,theta_y,theta;
	float ctheta_x=0,ctheta_y=0,ctheta_z=0,c_theta=0;
	float stheta_x=0,stheta_y=0,stheta_z=0,s_theta=0,r=0;
    float ax,ay,az;
    int choice,g2,g3;
    cout << "Enter 1 for orthographic views and 2 for view on a specified plane: ";
    cin >> choice;
    if(choice == 1){
      cout << "Enter 1 for projections without rotation , 2 for projections with rotation: ";
      cin >> g2;
      if(g2 == 1){
        a = 0;
        b = 0;
        c = 1;
      }
      else{
        cout << "Enter 1 for rotation about x, y & z axes and 2 for rotation about a general axis: ";
        cin >> g3;
        if(g3==1){
          cout << "Enter angle of rotation about x-axis(in degrees): ";
          cin >> ax;
          cout << "Enter angle of rotation about y-axis(in degrees): ";
          cin >> ay;
          cout << "Enter angle of rotation about z-axis(in degrees): ";
          cin >> az;
        }
        else{
          cout << "Enter the x-component of direction vector of the axis: ";
          cin >> a1;
          cout << "Enter the y-component of direction vector of the axis: ";
          cin >> b1;
          cout << "Enter the z-component of direction vector of the axis: ";
          cin >> c1;
          cout << "Enter the angle of rotation about the axis(in degrees): ";
          cin >> theta;
        }
      }
    }
    else{
	   cout << "Enter the x-component of normal vector of the plane:";
	   cin >> a;
	   cout << "Enter the y-component of normal vector of the plane:";
	   cin >> b;
	   cout << "Enter the z-component of normal vector of the plane:";
	   cin >> c;
    }
    if(choice==2 || (choice ==1  && g2==1)){
	    if(b!=0){ 
		    theta_x = -1*((fabs(b))/b)*acos(c/(sqrt(b*b + c*c)));
	    }
	    else{
		    theta_x = 0;
	    }
	    if(a!=0){
		    theta_y = ((fabs(a))/a)*acos(sqrt(b*b+c*c)/sqrt(a*a+b*b+c*c));
	    }
	    else{
		    theta_y = 0;
	    }
      ctheta_x = cos(theta_x);
      ctheta_y = cos(theta_y);
      stheta_x = sin(theta_x);
      stheta_y = sin(theta_y);
      ctheta_z = 1;
      stheta_z = 0;
    }   
    else if(choice ==1  && g2==2){
      if(g3==1){
        ctheta_x = cos((PI*ax)/180);
        ctheta_y = cos((PI*ay)/180);
        ctheta_z = cos((PI*az)/180);
        stheta_x = sin((PI*ax)/180);
        stheta_y = sin((PI*ay)/180);
        stheta_z = sin((PI*az)/180);
      }
    }
    if(choice == 2 || (choice ==1 && g2==1) || (choice == 1 && g2==2 && g3 ==1)){
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
      rotationz[2][2] = 1;
      rotationz[3][3] = 1;
      rotationz[0][0] = ctheta_z;
      rotationz[1][1] = ctheta_z;
      rotationz[0][1] = stheta_z;
      rotationz[1][0] = -1*stheta_z;
      float maxx = -10000;
      float maxy = -10000;
      float maxz = -10000;
      float minx = graph.at(graph.size()-1).x;
      float miny = graph.at(graph.size()-1).y;
      float minz = graph.at(graph.size()-1).z;
      for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
          temp2[i][j] =0 ;
          for (int k = 0; k < 4; k++){
            temp2[i][j] += rotationy[i][k]*rotationx[k][j];
          }
        }
      }
      for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
          tempf[i][j] = 0;
          for (int k = 0; k < 4; k++){
            tempf[i][j] += rotationz[i][k]*temp2[k][j];
          }
        }
      }
      for(int i=0;(unsigned)i < graph.size()-2;i++){
    	  float cof[4] = {};
    	  float x = graph.at(i).x;
    	  float y = graph.at(i).y;
    	  float z = graph.at(i).z;
    	  float mat[4] = {x,y,z,-1};
    	  for (int j = 0; j < 4; j++){
          cof[j] =0;
          for (int k = 0; k < 4; k++){
            cof[j] += tempf[j][k]*mat[k];
          }
    	  }
    	  graph.at(i).x = cof[0];
        if(cof[0]<minx) minx = cof[0];
        if(cof[0]-maxx>0.001){
          maxx = cof[0];
          mx = graph.at(i).point;
        }
        else if(cof[0]-maxx<0.001 && cof[0]-maxx>-0.001){
          maxx = cof[0];
          mx += graph.at(i).point;  
        } 
    	  graph.at(i).y = cof[1];
        if(cof[1]<miny) miny = cof[1];
        if(cof[1]-maxy>0.001){
          maxy = cof[1];
          my = graph.at(i).point;
        }
        else if(cof[1]-maxy<0.001 && cof[1]-maxy>-0.001){
          maxy = cof[1];
          my += graph.at(i).point;  
        }
    	  graph.at(i).z = cof[2];
        if(cof[2]<minz) minz = cof[2];
        if(cof[2]-maxz>0.001){
          maxz = cof[2];
          mz = graph.at(i).point;
        }
        else if(cof[2]-maxz<0.001 && cof[2]-maxz>-0.001){
          maxz = cof[2];
          mz += graph.at(i).point;  
        } 
      }
      string lala3,lala2,lala1;
      for(int xx=0;(unsigned) xx<faces.size();xx++){
        int flagx=0,flagy=0,flagz=0;
        for(int ax=0;(unsigned) ax<mx.length();ax++){
          if(faces.at(xx).find(mx.at(ax))!= std::string::npos){
            flagx++;
          }
        }
        if((unsigned)flagx==mx.length()){
          lala3 += faces.at(xx); 
        }
        for(int ay=0;(unsigned) ay<my.length();ay++){
          if(faces.at(xx).find(my.at(ay))!= std::string::npos){
             flagy++;
          }
        }
        if((unsigned)flagy==my.length()){
          lala2 += faces.at(xx);
        }
        for(int az=0;(unsigned) az<mz.length();az++){
          if(faces.at(xx).find(mz.at(az))!= std::string::npos){
             flagz++;
          }
        }
        if((unsigned)flagz==mz.length()){
          lala1 += faces.at(xx);
        }
      }
      //cout << lala1 + " "<< lala2 + " " << lala3 << endl;
      points.push_back(lala1);
      points.push_back(lala2);
      points.push_back(lala3);
      t1 = minx ;
      minx = minx-t1;
      maxx = maxx-t1;
      if(maxx>550) s1 = 550/maxx;
      else if(maxx < 100) s1 = 400/maxx;
      else s1 = 1;
      t2 = miny ;
      miny = miny-t2;
      maxy = maxy-t2;
      if(maxy>550) s2 = 550/maxy;
      else if(maxy < 100) s2 = 400/maxy;
      else s2 = 1;
      t3 = minz ;
      minz = minz-t3;
      maxz = maxz-t3;
      if(maxz>550) s3 = 550/maxz;
      else if(maxz < 100) s3 = 400/maxz;
      else s3 = 1;
      if(s1<=s2 && s1 <= s3) s = s1;
      else if(s2<=s3 && s2<=s1) s = s2;
      else if(s3 <= s1&& s3 <= s2) s = s3;
      else s = s1;
      translation[0][0] =1;
      translation[1][1] =1;
      translation[2][2] =1;
      translation[3][3] =1;
      translation[0][3] =t1;
      translation[1][3] =t2;
      translation[2][3] =t3;
      for(int i=0; (unsigned)i < graph.size()-2;i++){
        float cof[4] = {};
        float x = graph.at(i).x;
        float y = graph.at(i).y;
        float z = graph.at(i).z;
        float mat[4] = {x,y,z,-1};
        for (int j = 0; j < 4; j++){
          cof[j] =0;
          for (int k = 0; k < 4; k++){
            cof[j] += translation[j][k]*mat[k];
          }
        }
        graph.at(i).x = cof[0]*s + 30;
        graph.at(i).y = cof[1]*s + 30;
        graph.at(i).z = cof[2]*s + 30;
      }
    }
    else{
      float maxx = -10000;
      float maxy = -10000;
      float maxz = -10000;
      float minx = graph.at(graph.size()-1).x;
      float miny = graph.at(graph.size()-1).y;
      float minz = graph.at(graph.size()-1).z;
      c_theta = cos((PI*theta)/180);
      s_theta = sin((PI*theta)/180);
      r = sqrt(a1*a1+b1*b1+c1*c1);
      a1 = a1/r;
      b1 = b1/r;
      c1 = c1/r;
      float t1,t2,t3;
      float matrix[4][4] = {0};
      float t = 1- c_theta;
      float translation[4][4] = {0};
      matrix[0][0] = t*a1*a1 + c_theta; 
      matrix[0][1] = t*a1*b1 - s_theta*c1;
      matrix[0][2] = t*a1*c1 + s_theta*b1;
      matrix[1][0] = t*a1*b1 + s_theta*c1;
      matrix[1][1] = t*b1*b1 + c_theta;
      matrix[1][2] = t*b1*c1 - s_theta*a1; 
      matrix[2][0] = t*a1*c1 - s_theta*b1; 
      matrix[2][1] = t*b1*c1 + s_theta*a1;
      matrix[2][2] = t*c1*c1 + c_theta;
      matrix[3][3] = 1;
      for(int i=0; (unsigned)i < graph.size()-2;i++){
        float cof[4] = {};
        float x = graph.at(i).x;
        float y = graph.at(i).y;
        float z = graph.at(i).z;
        float mat[4] = {x,y,z,-1};
        for (int j = 0; j < 4; j++){
          for (int k = 0; k < 4; k++){
            cof[j] += matrix[j][k]*mat[k];
          }
        }
        graph.at(i).x = cof[0];
        if(cof[0]<minx) minx = cof[0];
        if(cof[0]-maxx>0.001){
          maxx = cof[0];
          mx = graph.at(i).point;
        }
        else if(cof[0]-maxx<0.001 && cof[0]-maxx>-0.001){
          maxx = cof[0];
          mx += graph.at(i).point;  
        }
        graph.at(i).y = cof[1];
        if(cof[1]<miny) miny = cof[1];
        if(cof[1]-maxy>0.001){
          maxy = cof[1];
          my = graph.at(i).point;
        }
        else if(cof[1]-maxy<0.001 && cof[1]-maxy>-0.001){
          maxy = cof[1];
          my += graph.at(i).point;  
        }
        graph.at(i).z = cof[2];
        if(cof[2]<minz) minz = cof[2];
        if(cof[2]-maxz>0.001){
          maxz = cof[2];
          mz = graph.at(i).point;
        }
        else if(cof[2]-maxz<0.001 && cof[2]-maxz>-0.001){
          maxz = cof[2];
          mz += graph.at(i).point;  
        }
      }
      string lala3,lala2,lala1;
      
      for(int xx=0;(unsigned) xx<faces.size();xx++){
        int flagx=0,flagy=0,flagz=0;
        for(int ax=0;(unsigned) ax<mx.length();ax++){
          if(faces.at(xx).find(mx.at(ax))!= std::string::npos){
            flagx++;
          }
        }
        if((unsigned)flagx==mx.length()){
          lala3 += faces.at(xx); 
        }
        for(int ay=0;(unsigned) ay<my.length();ay++){
          if(faces.at(xx).find(my.at(ay))!= std::string::npos){
             flagy++;
          }
        }
        if((unsigned)flagy==my.length()){
          lala2 += faces.at(xx);
        }
        for(int az=0;(unsigned) az<mz.length();az++){
          if(faces.at(xx).find(mz.at(az))!= std::string::npos){
             flagz++;
          }
        }
        if((unsigned)flagz==mz.length()){
          lala1 += faces.at(xx);
        }
      }
      points.push_back(lala1);
      points.push_back(lala2);
      points.push_back(lala3);
      t1 = minx;
      minx = minx-t1;
      maxx = maxx-t1;
      if(maxx>550) s1 = 550/maxx;
      else if(maxx < 100) s1 = 400/maxx;
      else s1 = 1;
      t2 = miny ;
      miny = miny-t2;
      maxy = maxy-t2;
      if(maxy>550) s2 = 550/maxy;
      else if(maxy < 100) s2 = 400/maxy;
      else s2 = 1;
      t3 = minz;
      minz = minz-t3;
      maxz = maxz-t3;
      if(maxz>550) s3 = 550/maxz;
      else if(maxz < 100) s3 = 400/maxz;
      else s3 = 1;
      if(s1<=s2 && s1 <= s3) s = s1;
      else if(s2<=s3 && s2<=s1) s = s2;
      else if(s3 <= s1&& s3 <= s2) s = s3;
      else s = s1;
      translation[0][0] =1;
      translation[1][1] =1;
      translation[2][2] =1;
      translation[3][3] =1;
      translation[0][3] =t1;
      translation[1][3] =t2;
      translation[2][3] =t3;
      for(int i=0; (unsigned)i < graph.size()-2;i++){
        float cof[4] = {};
        float x = graph.at(i).x;
        float y = graph.at(i).y;
        float z = graph.at(i).z;
        float mat[4] = {x,y,z,-1};
        for (int j = 0; j < 4; j++){
          cof[j] =0;
          for (int k = 0; k < 4; k++){
            cof[j] += translation[j][k]*mat[k];
          }
        }
        graph.at(i).x = cof[0]*s + 30;
        graph.at(i).y = cof[1]*s + 30;
        graph.at(i).z = cof[2]*s + 30;
        }
    }
    return choice;
}