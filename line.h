#ifndef LINE_H
#define LINE_H
#include "shape.h"
#include <QPoint>
#include <cmath>
#include <algorithm>
#define PI 3.14159265358979323846
#define left 1
#define right 2
#define bottom 4
#define top 8

class line: public shape
{
private:
    QPoint p0;
    QPoint pn;
public:
    line();
    line(QPoint p0,QPoint pn);
    line(int x0,int y0,int xn,int yn);
    void draw_Bresenham(QImage *image, QColor *color)override;
    void draw_DDA(QImage *image, QColor *color)override;
    void translate(int x,int y)override;
    void rotate(int x, int y,int r) override;
    void scale(int x,int y,float s) override;
    void clip_Cohen_Sutherland(int x1,int y1,int x2,int y2) override;
    void clip_Liang_Barsky(int x1, int y1, int x2, int y2) override;
    void setInformation(int x1,int x2,int y1,int y2);
    QPoint getP0();
    QPoint getPn();
    QPoint getCentralPoint() override;
    int getClipCode(QPoint p,int x1, int y1, int x2, int y2);
    int clipCal(float p,float q,float *tl,float*tu);
};

#endif // LINE_H
