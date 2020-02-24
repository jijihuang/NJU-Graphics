#ifndef SHAPE_H
#define SHAPE_H
#include <QImage>
#include <QColor>
#include <vector>
#include "drawaction.h"
using namespace std;

class shape
{
public:
    shape();
    int getId();
    QColor getColor();
    QString getAlgorithm();
    QString getName();
    QString getInformation();
    QPoint getRotatePoint();
    int getAngle();
    void setRotatePoint(int x,int y);
    void setAngle(int angle);
    void setId(int id);
    void setColor(int R,int G,int B);
    void setColor(QColor color);
    void setAlgorithm(QString algorithm);
    void setName(QString name);
    void setInformation(QString information);
    virtual void draw_Bresenham(QImage *image,QColor *color){}
    virtual void draw_DDA(QImage *image,QColor *color){}
    virtual void clip_Cohen_Sutherland(int x1,int y1,int x2,int y2){}
    virtual void clip_Liang_Barsky(int x1,int y1,int x2,int y2){}
    virtual void draw_Bezier(QImage *image, QColor *color){}
    virtual void draw_Bspline(QImage *image, QColor *color){}
    virtual void translate(int x,int y){}
    virtual void rotate(int x,int y,int r){}
    virtual void scale(int x,int y,float s){}
    virtual vector<QPoint> getPoints(){vector<QPoint>res; return res;}
    virtual QPoint getCentralPoint(){return QPoint(0,0);}
    virtual ~shape(){}
private:
    int id;
    QColor *color;
    QString algorithm;
    QString name;
    QString information;
    int angle;
    QPoint rotatePoint;
};

#endif // SHAPE_H
