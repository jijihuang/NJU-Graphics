#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include <QPoint>
#define PI 3.14159265358979323846

class circle: public shape
{
private:
    QPoint c;
    int r;
public:
    circle();
    circle(QPoint c,int r);
    circle(int xc,int yc,int r);
    void draw_Bresenham(QImage *image, QColor *color)override;
    void setPixel(QImage *image,int x,int y,QColor *color);
    void translate(int x,int y)override;
    void rotate(int x, int y,int r) override;
    void scale(int x,int y,float s) override;
    void setInformation(int xc,int yc,int r);
    QPoint getCentralPoint() override;
    int getRadius();
};

#endif // CIRCLE_H
