#include "ellipse.h"

ellipse::ellipse()
{
    rx=0;
    ry=0;
    c.setX(0);
    c.setY(0);
    angle=0;
    rotatePoint=c;
    //color=new QColor(Qt::black);
    this->setName("ellipse");
}

ellipse::ellipse(int xc,int yc,int a,int b)
{
    this->rx=a;
    this->ry=b;
    c.setX(xc);
    c.setY(yc);
    this->angle=0;
    rotatePoint=c;
    //color=new QColor(Qt::black);
    this->setName("ellipse");
}

ellipse::ellipse(int xc,int yc,int a,int b,int angle,QPoint rotatePoint)
{
    this->rx=a;
    this->ry=b;
    c.setX(xc);
    c.setY(yc);
    this->angle=angle;
    this->rotatePoint=rotatePoint;
    //color=new QColor(Qt::black);
    this->setName("ellipse");
}

ellipse::ellipse(QPoint c,int a,int b)
{
    this->rx=a;
    this->ry=b;
    this->c=c;
    angle=0;
    rotatePoint=c;
    //color=new QColor(Qt::black);
    this->setName("ellipse");
}

QPoint ellipse::getCentralPoint(){
    return c;
}

int ellipse::getRadiusX(){
    return rx;
}

int ellipse::getRadiusY(){
    return ry;
}

void ellipse::setInformation(int cx, int cy, int rx, int ry){
    this->c.setX(cx);
    this->c.setY(cy);
    this->rx=rx;
    this->ry=ry;
}


void ellipse::setPixel(QImage *image, int x, int y, QColor *color)
{
    double cosAngle=cos(double(angle)*PI/180);
    double sinAngle=sin(double(angle)*PI/180);

    int rotateX=rotatePoint.x();
    int rotateY=rotatePoint.y();

    /*image->setPixelColor(int(rotateX+(x-rotateX)*cosAngle-(y-rotateY)*sinAngle)+c.x(),int(rotateY+(x-rotateX)*sinAngle+(y-rotateY)*cosAngle)+c.y(),*color);
    image->setPixelColor(int(-rotateX-(x-rotateX)*cosAngle-(y-rotateY)*sinAngle)+c.x(),int(rotateY-(x-rotateX)*sinAngle+(y-rotateY)*cosAngle)+c.y(),*color);
    image->setPixelColor(int(rotateX+(x-rotateX)*cosAngle+(y-rotateY)*sinAngle)+c.x(),int(-rotateY+(x-rotateX)*sinAngle-(y-rotateY)*cosAngle)+c.y(),*color);
    image->setPixelColor(int(-rotateX-(x-rotateX)*cosAngle+(y-rotateY)*sinAngle)+c.x(),int(-rotateY-(x-rotateX)*sinAngle-(y-rotateY)*cosAngle)+c.y(),*color);

    image->setPixelColor(int(rotateX+(x-rotateX)*cosAngle-(y-rotateY)*sinAngle)+1+c.x(),int(rotateY+(x-rotateX)*sinAngle+(y-rotateY)*cosAngle)+c.y(),*color);
    image->setPixelColor(int(-rotateX-(x-rotateX)*cosAngle-(y-rotateY)*sinAngle)+1+c.x(),int(rotateY-(x-rotateX)*sinAngle+(y-rotateY)*cosAngle)+c.y(),*color);
    image->setPixelColor(int(rotateX+(x-rotateX)*cosAngle+(y-rotateY)*sinAngle)+1+c.x(),int(-rotateY+(x-rotateX)*sinAngle-(y-rotateY)*cosAngle)+c.y(),*color);
    image->setPixelColor(int(-rotateX-(x-rotateX)*cosAngle+(y-rotateY)*sinAngle)+1+c.x(),int(-rotateY-(x-rotateX)*sinAngle-(y-rotateY)*cosAngle)+c.y(),*color);

    image->setPixelColor(int(rotateX+(x-rotateX)*cosAngle-(y-rotateY)*sinAngle)+c.x(),int(rotateY+(x-rotateX)*sinAngle+(y-rotateY)*cosAngle)+1+c.y(),*color);
    image->setPixelColor(int(-rotateX-(x-rotateX)*cosAngle-(y-rotateY)*sinAngle)+c.x(),int(rotateY-(x-rotateX)*sinAngle+(y-rotateY)*cosAngle)+1+c.y(),*color);
    image->setPixelColor(int(rotateX+(x-rotateX)*cosAngle+(y-rotateY)*sinAngle)+c.x(),int(-rotateY+(x-rotateX)*sinAngle-(y-rotateY)*cosAngle)+1+c.y(),*color);
    image->setPixelColor(int(-rotateX-(x-rotateX)*cosAngle+(y-rotateY)*sinAngle)+c.x(),int(-rotateY-(x-rotateX)*sinAngle-(y-rotateY)*cosAngle)+1+c.y(),*color);*/

    /*image->setPixelColor(int(x*cosAngle-y*sinAngle)+c.x(),int(x*sinAngle+y*cosAngle)+c.y(),*color);
    image->setPixelColor(int(-x*cosAngle-y*sinAngle)+c.x(),int(-x*sinAngle+y*cosAngle)+c.y(),*color);
    image->setPixelColor(int(x*cosAngle+y*sinAngle)+c.x(),int(x*sinAngle-y*cosAngle)+c.y(),*color);
    image->setPixelColor(int(-x*cosAngle+y*sinAngle)+c.x(),int(-x*sinAngle-y*cosAngle)+c.y(),*color);

    image->setPixelColor(int(x*cosAngle-y*sinAngle)+1+c.x(),int(x*sinAngle+y*cosAngle)+c.y(),*color);
    image->setPixelColor(int(-x*cosAngle-y*sinAngle)+1+c.x(),int(-x*sinAngle+y*cosAngle)+c.y(),*color);
    image->setPixelColor(int(x*cosAngle+y*sinAngle)+1+c.x(),int(x*sinAngle-y*cosAngle)+c.y(),*color);
    image->setPixelColor(int(-x*cosAngle+y*sinAngle)+1+c.x(),int(-x*sinAngle-y*cosAngle)+c.y(),*color);

    image->setPixelColor(int(x*cosAngle-y*sinAngle)+c.x(),int(x*sinAngle+y*cosAngle)+1+c.y(),*color);
    image->setPixelColor(int(-x*cosAngle-y*sinAngle)+c.x(),int(-x*sinAngle+y*cosAngle)+1+c.y(),*color);
    image->setPixelColor(int(x*cosAngle+y*sinAngle)+c.x(),int(x*sinAngle-y*cosAngle)+1+c.y(),*color);
    image->setPixelColor(int(-x*cosAngle+y*sinAngle)+c.x(),int(-x*sinAngle-y*cosAngle)+1+c.y(),*color);*/

    //int xx0=int(rotateX+(x+c.x()-rotateX)*cosAngle-(y+c.y()-rotateY)*sinAngle);
    //int yy0=int(rotateY+(x+c.x()-rotateX)*sinAngle+(y+c.y()-rotateY)*cosAngle);

    image->setPixelColor(int(rotateX+(x+c.x()-rotateX)*cosAngle-(y+c.y()-rotateY)*sinAngle),int(rotateY+(x+c.x()-rotateX)*sinAngle+(y+c.y()-rotateY)*cosAngle),*color);
    image->setPixelColor(int(rotateX+(-x+c.x()-rotateX)*cosAngle-(y+c.y()-rotateY)*sinAngle),int(rotateY+(-x+c.x()-rotateX)*sinAngle+(y+c.y()-rotateY)*cosAngle),*color);
    image->setPixelColor(int(rotateX+(x+c.x()-rotateX)*cosAngle-(-y+c.y()-rotateY)*sinAngle),int(rotateY+(x+c.x()-rotateX)*sinAngle+(-y+c.y()-rotateY)*cosAngle),*color);
    image->setPixelColor(int(rotateX+(-x+c.x()-rotateX)*cosAngle-(-y+c.y()-rotateY)*sinAngle),int(rotateY+(-x+c.x()-rotateX)*sinAngle+(-y+c.y()-rotateY)*cosAngle),*color);

    /*image->setPixelColor(x+c.x(),y+c.y(),*color);
    image->setPixelColor(-x+c.x(),y+c.y(),*color);
    image->setPixelColor(x+c.x(),-y+c.y(),*color);
    image->setPixelColor(-x+c.x(),-y+c.y(),*color);*/
}

void ellipse::translate(int x, int y){
    c.setX(c.x()+x);
    c.setY(c.y()+y);
    rotatePoint=c;
}

void ellipse::rotate(int x, int y, int r){
    angle=r;
    rotatePoint.setX(x);
    rotatePoint.setY(y);
}

void ellipse::scale(int x, int y, float s){
    int x1=int(float(c.x()*s+x*(1-s)));
    int y1=int(float(c.y()*s+y*(1-s)));
    rx=rx*s;
    ry=ry*s;
    c.setX(x1);
    c.setY(y1);
}

void ellipse::setCentralPoint(int r){
    int x=rotatePoint.x();
    int y=rotatePoint.y();
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

void ellipse::draw_Bresenham(QImage *image, QColor *color)
{
    int x=0;
    int y=ry;
    int p1=(ry*ry-rx*rx*ry+rx*rx/4);
    //region 1
    while(2*ry*ry*x<2*rx*rx*y){
        setPixel(image,x,y,color);
        if (p1<0){
            x++;
            p1=p1+2*ry*ry*x+ry*ry;
        }
        else{
            y--;
            x++;
            p1=p1+2*ry*ry*x-2*rx*rx*y+ry*ry;
        }
    }
    int p2=ry*ry*x*x+ry*ry*x+ry*ry/4+rx*rx*y*y-2*rx*rx*y+rx*rx-rx*rx*ry*ry;
    //region 2
    while (y>=0){
        setPixel(image,x,y,color);
        if (p2>=0){
            y--;
            p2=p2-2*rx*rx*y+rx*rx;
        }
        else{
            y--;
            x++;
            p2=p2+2*ry*ry*x-2*rx*rx*y+rx*rx;
        }
    }
}
