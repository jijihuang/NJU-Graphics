#include "curve.h"

curve::curve()
{
    this->setName("curve");
}

curve::curve(vector<QPoint> points){
    //color=new QColor(Qt::black);
    this->points.assign(points.begin(),points.end());
    this->setName("curve");
}

QPoint curve::getCentralPoint(){
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

vector<QPoint> curve::getPoints(){
    return points;
}

void curve::setInformation(vector<QPoint> points){
    this->points.assign(points.begin(),points.end());
}

double curve::getRatio(double t, double a, double b, double c, double d){
    return a*pow(t,3)+b*pow(t,2)+c*t+d;
}

void curve::draw_Bspline(QImage *image, QColor *color){
    int n=4;
    double m[4][4]={{1.0/6.0,4.0/6.0,1.0/6.0,0.0},{-0.5,0.0,0.5,0.0},{0.5,-1.0,0.5,0.0},{-1.0/6.0,0.5,-0.5,1.0/6.0}};
    int percision=1000;
    double matrix[4];
    for (int i=0;i<percision;i++){
        double t=(double)i/percision;
        float x=0.0;
        float y=0.0;
        matrix[0]=getRatio(t,m[3][0],m[2][0],m[1][0],m[0][0]);
        matrix[1]=getRatio(t,m[3][1],m[2][1],m[1][1],m[0][1]);
        matrix[2]=getRatio(t,m[3][2],m[2][2],m[1][2],m[0][2]);
        matrix[3]=getRatio(t,m[3][3],m[2][3],m[1][3],m[0][3]);
        for (int j=0;j<points.size()-3;j++){
            double x=matrix[0]*points[j].x()+matrix[1]*points[j+1].x()+matrix[2]*points[j+2].x()+matrix[3]*points[j+3].x();
            double y=matrix[0]*points[j].y()+matrix[1]*points[j+1].y()+matrix[2]*points[j+2].y()+matrix[3]*points[j+3].y();
            image->setPixelColor(x,y,*color);
        }
    }
}

void curve::draw_Bezier(QImage *image, QColor *color){
    int n=points.size();
    int *mi=new int[n];
    mi[0]=mi[1]=1;
    for (int i=3;i<=n;i++){
        int *t=new int[i-1];
        for (int j=0;j<i-1;j++){
            t[j]=mi[j];
        }
        mi[0]=mi[i-1]=1;
        for(int j=0;j<i-2;j++){
            mi[j+1]=t[j]+t[j+1];
        }
    }
    int percision=1000;
    for (int i=0;i<percision;i++){
        double t=(double)i/percision;
        float x=0.0;
        float y=0.0;
        for (int j=0;j<n;j++){
            x+=mi[j]*pow(t,j)*pow(1-t,n-j-1)*points[j].x();
            y+=mi[j]*pow(t,j)*pow(1-t,n-j-1)*points[j].y();
        }
        image->setPixelColor(x,y,*color);
    }

}

void curve::translate(int x, int y){
    for(int i=0;i<points.size();i++){
        points[i].setX(points[i].x()+x);
        points[i].setY(points[i].y()+y);
    }
}
void curve::rotate(int x, int y, int r){
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

void curve::scale(int x, int y, float s){
    for(int i=0;i<points.size();i++){
        int x1=int(float(points[i].x()*s+x*(1-s)));
        int y1=int(float(points[i].y()*s+y*(1-s)));
        points[i].setX(x1);
        points[i].setY(y1);
    }
}

