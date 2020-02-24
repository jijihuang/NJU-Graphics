#include "circle.h"

circle::circle()
{
    c.setX(0);
    c.setY(0);
    //color=new QColor(Qt::black);
    this->setName("circle");
}

circle::circle(QPoint c,int r)
{
    this->c=c;
    this->r=r;
    //color=new QColor(Qt::black);
    this->setName("circle");
}

circle::circle(int xc,int yc,int r)
{
    this->r=r;
    c.setX(xc);
    c.setY(yc);
    //color=new QColor(Qt::black);
    this->setName("circle");
}

void circle::setPixel(QImage *image,int x, int y, QColor *color)
{
    image->setPixelColor(x+c.x(),y+c.y(),*color);
    image->setPixelColor(x+c.x(),-y+c.y(),*color);
    image->setPixelColor(-x+c.x(),y+c.y(),*color);
    image->setPixelColor(-x+c.x(),-y+c.y(),*color);
    image->setPixelColor(y+c.x(),x+c.y(),*color);
    image->setPixelColor(-y+c.x(),x+c.y(),*color);
    image->setPixelColor(y+c.x(),-x+c.y(),*color);
    image->setPixelColor(-y+c.x(),-x+c.y(),*color);
}

void circle::setInformation(int xc, int yc, int r){
    this->c.setX(xc);
    this->c.setY(yc);
    this->r=r;
}

int circle::getRadius(){
    return r;
}

QPoint circle::getCentralPoint(){
    return c;
}

void circle::translate(int x, int y){
    c.setX(c.x()+x);
    c.setY(c.y()+y);
}

void circle::rotate(int x, int y, int r){
    double theta=r*PI/180;
    double cosTheta=cos(theta);
    double sinTheta=sin(theta);
    int x0=c.x();
    int y0=c.y();
    int xx0=int(x+(x0-x)*cosTheta-(y0-y)*sinTheta);
    int yy0=int(y+(x0-x)*sinTheta+(y0-y)*cosTheta);
    c.setX(xx0);
    c.setY(yy0);
}

void circle::scale(int x, int y, float s){
    int x1=int(float(c.x()*s+x*(1-s)));
    int y1=int(float(c.y()*s+y*(1-s)));
    r=r*s;
    c.setX(x1);
    c.setY(y1);
}

void circle::draw_Bresenham(QImage *image, QColor *color)
{
    int x=0;
    int y=r;
    int p=3-2*r;
    for (;x<=y;x++){
        setPixel(image,x,y,color);
        if (p>=0){
            p+=4*(x-y)+10;
            y--;
        }
        else{
            p+=4*x+6;
        }
    }
}
