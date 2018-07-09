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
using namespace std;
using namespace Qt;
#include "../include/graph.h"
#include "../include/3D_file.h"
#include "../include/projection.h"
#include "../include/transform.h"
#include "../include/file_3D_temp.h"
#include "../include/2D_file.h"
#include "../include/conversion.h"

struct vertex{
   string f,g;
   float e,b,c,d;
};

void tokenize3 (string a,vector<string> &vect){
   string token,token2;
   if(a.find('&')!= std::string::npos){
      token = a.substr(0, a.find('&'));
      token2 = a.substr(a.find('&')+1,a.length());
      vect.push_back(token);
      tokenize3(token2,vect);
   }
   else vect.push_back(a);
}

vector<co_ordinates_3D> graph;
vector<string> edges1,edges2,edges3;
vector<vector<co_ordinates_2D> > outgraphs1,outgraphs2;
int choice;
int main(int argc, char *argv[]){
	int mode;
   map<string,int> m1,m2,m3;
	cout << "Enter user mode ('1' for 3D to 2D and '2' for 2D to 3D): ";
	cin >> mode;
   int n,n1;
   float e,b,c,d;
   float max=0.0;
   string f,g;
   QApplication a(argc, argv);
   QLabel l;
   QPicture pi;
   QPainter p(&pi);
   ifstream infile;
   QString lab;
	if(mode == 1){
      vector<string> faces,points;
		string lala = get_3D_graph(graph,faces);
		choice = transform(graph,faces,points);
		projections(graph,outgraphs1);
		write_in_out_file(outgraphs1,choice);	
   	infile.open("output_3D.txt");
   	p.setRenderHint(QPainter::Antialiasing);
      p.setPen(QPen(Qt::black, 0.04, Qt::SolidLine, Qt::RoundCap));
      p.drawLine(-900, 0, -901, 0);
   	p.setPen(QPen(Qt::black, 5.5, Qt::SolidLine, Qt::RoundCap));
   	if(choice ==1){
         p.drawText(10,-450,lab);
   		p.drawLine(-800, 0, 800, 0);
   		p.drawLine(0, -500, 0, 500);
         p.setPen(QPen(Qt::black, 8, Qt::SolidLine, Qt::RoundCap));
         p.drawLine(-800,500,800,500);
         p.drawLine(800,500,800,-500);
         p.drawLine(-800,500,-800,-500);
         p.drawLine(-800,-500,800,-500);
   	}
      if(choice == 1){
         lab = QString::fromStdString("Front view");
      }
      else{
         lab = QString::fromStdString("Projection on the desired plane");
      }
      p.setPen(QPen(Qt::black, 3.5, Qt::SolidLine, Qt::RoundCap));
      p.drawText(400,400,lab);
      infile >> n;
      vertex x[n];
      for(int j=0;j<n;j++){
         infile >> x[j].f >> x[j].e >> x[j].b >> x[j].g >> x[j].c >> x[j].d;
         if(max<x[j].b) max=x[j].b;
         if(max<x[j].d) max=x[j].d;
      }
      for(int j=0;j<n;j++){
         vector<string> vect1,vect2;
         tokenize3(x[j].f,vect1);
         tokenize3(x[j].g,vect2);
         for(int t1=0;(unsigned) t1<vect1.size();t1++){
            for(int t2=0;(unsigned) t2<vect2.size();t2++){
               if(points[0].find(vect1.at(t1))!= std::string::npos && points[0].find(vect2.at(t2))!= std::string::npos){
                  p.setPen(QPen(Qt::black, 3.5, Qt::SolidLine, Qt::RoundCap));
                  p.drawLine(x[j].e,max+30-x[j].b,x[j].c,max+30-x[j].d);
               }
               else{
                  p.setPen(QPen(Qt::black, 1.5, Qt::DotLine, Qt::RoundCap));
                  p.drawLine(x[j].e,max+30-x[j].b,x[j].c,max+30-x[j].d);  
               }
            }
         }
         p.setPen(QPen(Qt::black, 3.5, Qt::SolidLine, Qt::RoundCap));
         QString lab1 = QString::fromStdString(x[j].f);
         QString lab2 = QString::fromStdString(x[j].g);
         p.drawText(x[j].e + 10, max + 30 - x[j].b - 10, lab1);
         p.drawText(x[j].c + 10, max + 30 - x[j].d - 10, lab2);
         vector<string> temp1;
         tokenize3(x[j].f,temp1);
         for(int lq=0;(unsigned)lq<temp1.size();lq++){
            m1[temp1.at(lq)] = x[j].e;
            m2[temp1.at(lq)] = max+30-x[j].b;   
         }
         vector<string> temp2;
         tokenize3(x[j].g,temp2);
         for(int lq=0;(unsigned)lq<temp2.size();lq++){
            m1[temp2.at(lq)] = x[j].c;
            m2[temp2.at(lq)] = max+30-x[j].d;   
         }
      }
   	if(choice==1){
         lab = QString::fromStdString("Top view");
         p.drawText(400,-400,lab);
         infile >> n;
         vertex xx[n];
         max = 0;
         for(int j=0;j<n;j++){
            infile >> xx[j].f >> xx[j].e >> xx[j].b >> xx[j].g >> xx[j].c >> xx[j].d;
            if(max<xx[j].b) max=xx[j].b;
            if(max<xx[j].d) max=xx[j].d;
         }
         for(int j=0;j<n;j++){
            vector<string> vect11,vect22;
            tokenize3(xx[j].f,vect11);
            tokenize3(xx[j].g,vect22);
            for(int t1=0;(unsigned) t1<vect11.size();t1++){
               for(int t2=0;(unsigned) t2<vect22.size();t2++){
                  if(points[1].find(vect11.at(t1))!= std::string::npos && points[1].find(vect22.at(t2))!= std::string::npos){
                     p.setPen(QPen(Qt::black, 3.5, Qt::SolidLine, Qt::RoundCap));
                     p.drawLine(xx[j].e,-max-30+xx[j].b,xx[j].c,-max-30+xx[j].d);
                  }
                  else{
                     p.setPen(QPen(Qt::black, 1.5, Qt::DotLine, Qt::RoundCap));
                     p.drawLine(xx[j].e,-max-30+xx[j].b,xx[j].c,-max-30+xx[j].d); 
                  }
               }
            }
            p.setPen(QPen(Qt::black, 3.5, Qt::SolidLine, Qt::RoundCap));
            QString lab1 = QString::fromStdString(xx[j].f);
            QString lab2 = QString::fromStdString(xx[j].g);
            p.drawText(xx[j].e + 10, -max - 30 + xx[j].b + 10, lab1);
            p.drawText(xx[j].c + 10, -max - 30 + xx[j].d + 10, lab2);
            vector<string> t1,t2;
            tokenize3(xx[j].f,t1);
            tokenize3(xx[j].g,t2);
            p.setPen(QPen(Qt::black, 0.25, Qt::DotLine, Qt::RoundCap));
            for(int la = 0;(unsigned)la<t1.size();la++){
               p.drawLine(xx[j].e,-max-30+xx[j].b,m1[t1.at(la)],m2[t1.at(la)]);   
            }
            for(int la = 0;(unsigned)la<t2.size();la++){
               p.drawLine(xx[j].c,-max-30+xx[j].d,m1[t2.at(la)],m2[t2.at(la)]);   
            }
            p.setPen(QPen(Qt::black, 3.5, Qt::SolidLine, Qt::RoundCap));
         }
         lab = QString::fromStdString("Side view");
         p.drawText(-400,400,lab);
         infile >> n;
         vertex xxx[n];
         max=0;
         for(int j=0;j<n;j++){
            infile >> xxx[j].f >> xxx[j].e >> xxx[j].b >> xxx[j].g >> xxx[j].c >> xxx[j].d;
            if(max<xxx[j].e) max=xxx[j].e;
            if(max<xxx[j].c) max=xxx[j].c;
         }
         for(int j=0;j<n;j++){
            infile >> xxx[j].f >> xxx[j].e >> xxx[j].b >> xxx[j].g >> xxx[j].c >> xxx[j].d;
            vector<string> vect111,vect222;
            tokenize3(xxx[j].f,vect111);
            tokenize3(xxx[j].g,vect222);
            for(int t1=0;(unsigned) t1<vect111.size();t1++){
               for(int t2=0;(unsigned) t2<vect222.size();t2++){
                  if(points[2].find(vect111.at(t1))!= std::string::npos && points[2].find(vect222.at(t2))!= std::string::npos){
                     p.setPen(QPen(Qt::black, 3.5, Qt::SolidLine, Qt::RoundCap));
                     p.drawLine(-xxx[j].b,max+30-xxx[j].e,-xxx[j].d,max+30-xxx[j].c);
                  }
                  else{
                     p.setPen(QPen(Qt::black, 1.5, Qt::DotLine, Qt::RoundCap));
                     p.drawLine(-xxx[j].b,max+30-xxx[j].e,-xxx[j].d,max+30-xxx[j].c); 
                  }
               }
            }
            p.setPen(QPen(Qt::black, 3.5, Qt::SolidLine, Qt::RoundCap));
            QString lab1 = QString::fromStdString(xxx[j].f);
            QString lab2 = QString::fromStdString(xxx[j].g);
            p.drawText(-xxx[j].b - 10, max + 30 - xxx[j].e - 10, lab1);
            p.drawText(-xxx[j].d - 10, max + 30 - xxx[j].c - 10, lab2);
            vector<string> ta1,ta2;
            tokenize3(xxx[j].f,ta1);
            tokenize3(xxx[j].g,ta2);
            p.setPen(QPen(Qt::black, 0.25, Qt::DotLine, Qt::RoundCap));
            for(int la = 0;(unsigned)la<ta1.size();la++){
               p.drawLine(-xxx[j].b,max+30-xxx[j].e,m1[ta1.at(la)],m2[ta1.at(la)]);   
            }
            for(int la = 0;(unsigned)la<ta2.size();la++){
               p.drawLine(-xxx[j].d,max+30-xxx[j].c,m1[ta2.at(la)],m2[ta2.at(la)]);   
            }
            p.setPen(QPen(Qt::black, 3.5, Qt::SolidLine, Qt::RoundCap));
         }
   	}
      infile.close();
      infile.open("temp.txt");
      p.setPen(QPen(Qt::black, 0.4, Qt::SolidLine, Qt::RoundCap));
      p.drawLine(-900, 0, -901, 0);
      p.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap));
      p.drawLine(-800,500,800,500);
      p.drawLine(800,500,800,-500);
      p.drawLine(-800,500,-800,-500);
      p.drawLine(-800,-500,800,-500);
      p.setPen(QPen(Qt::black, 3.5, Qt::SolidLine, Qt::RoundCap));
      max=0.0;
      float maxx=0.0;
      infile >> n1;
      lab = QString::fromStdString("Isometric view (with line of sight as (1,1,1))");
      p.drawText(-400,-400,lab);
      vertex xxxx[n1];
      for(int j=0;j<n1;j++){
         infile >> xxxx[j].f >> xxxx[j].e >> xxxx[j].b >> xxxx[j].g >> xxxx[j].c >> xxxx[j].d;
         xxxx[j].b *= -1;
         xxxx[j].d *= -1;
         if(max<xxxx[j].e) max=xxxx[j].e;
         if(max<xxxx[j].c) max=xxxx[j].c;
         if(maxx<xxxx[j].b) maxx=xxxx[j].b;
         if(maxx<xxxx[j].d) maxx=xxxx[j].d;
      }
      for(int j=0;j<n1;j++){
         vector<string> vect1111,vect2222;
         tokenize3(xxxx[j].f,vect1111);
         tokenize3(xxxx[j].g,vect2222);
         for(int t1=0;(unsigned) t1<vect1111.size();t1++){
            for(int t2=0;(unsigned) t2<vect2222.size();t2++){
               if(lala.find(vect1111.at(t1))!= std::string::npos && lala.find(vect2222.at(t2))!= std::string::npos){
                  p.drawLine(xxxx[j].e-max-30,xxxx[j].b-maxx-30,xxxx[j].c-max-30,xxxx[j].d-maxx-30);
                  QString lab1 = QString::fromStdString(xxxx[j].f);
                  QString lab2 = QString::fromStdString(xxxx[j].g);
                  p.drawText(xxxx[j].e-max-25,xxxx[j].b-maxx-25, lab1);
                  p.drawText(xxxx[j].c-max-25,xxxx[j].d-maxx-25, lab2);
               }
            }
         }
         p.setPen(QPen(Qt::black, 3.5, Qt::SolidLine, Qt::RoundCap));

      }
      p.end(); 
      l.setPicture(pi);
      infile.close();
      l.show();
	}
	else{
      string lal;
		lal = get_2D_graph(outgraphs2,edges1,edges2,edges3);
		isometric(outgraphs2,edges1,edges2,edges3);
	   infile.open("output_2D.txt");
   	p.setRenderHint(QPainter::Antialiasing);
      p.setRenderHint(QPainter::Antialiasing);
      p.setPen(QPen(Qt::black, 0.4, Qt::SolidLine, Qt::RoundCap));
      p.drawLine(-900, 0, -901, 0);
      p.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap));
      p.drawLine(-800,500,800,500);
      p.drawLine(800,500,800,-500);
      p.drawLine(-800,500,-800,-500);
      p.drawLine(-800,-500,800,-500);
   	p.setPen(QPen(Qt::black, 3.5, Qt::SolidLine, Qt::RoundCap));
   	infile >> n;
      lab = QString::fromStdString("Isometric view");
      p.drawText(-400,-400,lab);
   	for(int j=0;j<n;j++){
      	infile >> f >> e >> b >> g >> c >> d;
         
         
         vector<string> vec,ve;
         tokenize3(f,vec);
         tokenize3(g,ve);
         for(int t1=0;(unsigned) t1<vec.size();t1++){
            for(int t2=0;(unsigned) t2<ve.size();t2++){
               if(lal.find(vec.at(t1))!= std::string::npos && lal.find(ve.at(t2))!= std::string::npos){
                  p.drawLine(e,b,c,d);
                  lab = QString::fromStdString(f);
                  p.drawText(e+15,b+15,lab);
                  lab = QString::fromStdString(g); 
                  p.drawText(c+15,d+15,lab);
               }
            }
         }
   	}
      p.end(); 
      l.setPicture(pi);
      infile.close();
      l.show();   
	}
   return a.exec();
}