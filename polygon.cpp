#include "polygon.h"

polygon::polygon()
{
    //color=new QColor(Qt::black);
    this->setName("polygon");
}

polygon::polygon(vector<QPoint> points){
    //color=new QColor(Qt::black);
    this->points.assign(points.begin(),points.end());
    this->setName("polygon");
}

QPoint polygon::getCentralPoint(){
    int leftX=10000000;
    int leftY=10000000;
    int rightX=0;
    int rightY=0;
    for(int i=0;i<points.size();i++){
        if (points[i].x()<leftX) leftX=points[i].x();
        if (points[i].x()>=rightX) rightX=points[i].x();
        if (points[i].y()<leftY) leftY=points[i].y();
        if (points[i].y()>=rightY) rightY=points[i].y();
    }
    int retX=(leftX+rightX)/2;
    int retY=(leftY+rightY)/2;
    return QPoint(retX,retY);
}

vector<QPoint> polygon::getPoints(){
    return points;
}

void polygon::setInformation(vector<QPoint> points){
    this->points.assign(points.begin(),points.end());
}


void polygon::translate(int x, int y){
    for(int i=0;i<points.size();i++){
        points[i].setX(points[i].x()+x);
        points[i].setY(points[i].y()+y);
    }
}

void polygon::draw_DDA(QImage *image, QColor *color){
    for (int i=0;i<points.size()-1;i++){
        line temp(points[i],points[i+1]);
        temp.draw_DDA(image,color);
    }
    line temp(points[points.size()-1],points[0]);
    temp.draw_DDA(image,color);
}

void polygon::rotate(int x, int y, int r){
    for (int i=0;i<points.size();i++){
       // double theta=r*PI/180;
        double c=cos(r*PI/180);
        double s=sin(r*PI/180);
        int x0=points[i].x();
        int y0=points[i].y();
        int xx=int(x+(x0-x)*c-(y0-y)*s);
        int yy=int(y+(x0-x)*s+(y0-y)*c);
        points[i].setX(xx);
        points[i].setY(yy);
    }
}

void polygon::scale(int x, int y, float s){
    for(int i=0;i<points.size();i++){
        int x1=int(float(points[i].x()*s+x*(1-s)));
        int y1=int(float(points[i].y()*s+y*(1-s)));
        points[i].setX(x1);
        points[i].setY(y1);
    }
}

void polygon::draw_Bresenham(QImage *image, QColor *color){
    for (int i=0;i<points.size()-1;i++){
        line temp(points[i],points[i+1]);
        temp.draw_Bresenham(image,color);
    }
    line temp(points[points.size()-1],points[0]);
    temp.draw_Bresenham(image,color);
}
