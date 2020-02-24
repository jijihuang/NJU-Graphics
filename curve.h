#ifndef CURVE_H
#define CURVE_H

#include<vector>
#include<QPoint>
#include<math.h>
#include<algorithm>
#include "shape.h"
#include "line.h"
#define PI 3.14159265358979323846

class curve:public shape
{
private:
    vector<QPoint> points;
public:
    curve();
    curve(vector<QPoint> points);
    void draw_Bezier(QImage *image, QColor *color)override;
    void draw_Bspline(QImage *image, QColor *color)override;
    void translate(int x,int y)override;
    void rotate(int x, int y,int r) override;
    void scale(int x,int y,float s) override;
    QPoint getCentralPoint() override;
    void setInformation(vector<QPoint>points);
    vector<QPoint> getPoints()override;
    double getRatio(double t,double a,double b,double c,double d);
    double BsplineCal(int i,double u);
    double getMatrix(double x0,double x1,double x2,double x3,double t);

};

#endif // CURVE_H
