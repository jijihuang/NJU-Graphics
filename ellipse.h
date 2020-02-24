#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"
#include <QPoint>
#define PI 3.14159265358979323846

class ellipse:public shape
{
private:
    int rx;
    int ry;
    int angle;
    QPoint rotatePoint;
    QPoint c;
public:
    ellipse();
    ellipse(int xc,int yc,int a,int b);
    ellipse(int xc,int yc,int a,int b,int angle,QPoint rotatePoint);
    ellipse(QPoint c,int a,int b);
    void draw_Bresenham(QImage *image, QColor *color)override;
    void setPixel(QImage *image,int x,int y,QColor *color);
    void translate(int x,int y)override;
    void rotate(int x, int y,int r) override;
    void setInformation(int cx,int cy,int rx,int ry);
    void setCentralPoint(int r);
    void scale(int x,int y,float s) override;
    QPoint getCentralPoint() override;
    int getRadiusX();
    int getRadiusY();
};

#endif // ELLIPSE_H
