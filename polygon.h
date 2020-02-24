#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <QPoint>
#include "shape.h"
#include "line.h"
#define PI 3.14159265358979323846

class polygon:public shape
{
private:
    vector<QPoint> points;
public:
    polygon();
    polygon(vector<QPoint> points);
    void draw_DDA(QImage *image, QColor *color) override;
    void draw_Bresenham(QImage *image, QColor *color) override;
    void translate(int x,int y)override;
    void rotate(int x, int y,int r) override;
    void scale(int x,int y,float s) override;
    QPoint getCentralPoint() override;
    void setInformation(vector<QPoint>points);
    vector<QPoint> getPoints()override;
};

#endif // POLYGON_H
