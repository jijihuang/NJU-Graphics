#include"shape.h"

shape::shape(){
    id=-1;
    angle=0;
    rotatePoint.setX(0);
    rotatePoint.setY(0);
    color=new QColor(Qt::black);
}


int shape::getId(){
    return id;
}

QColor shape::getColor(){
    return *color;
}

QString shape::getAlgorithm(){
    return algorithm;
}

QString shape::getName(){
    return name;
}

QString shape::getInformation(){
    return information;
}

void shape::setId(int id){
    this->id=id;
}

void shape::setColor(int R,int G,int B){
    color->setRgb(R,G,B);
}

void shape::setColor(QColor color){
    *this->color=color;
}

void shape::setAlgorithm(QString algorithm){
    this->algorithm=algorithm;
}

void shape::setName(QString name){
    this->name=name;
}

void shape::setInformation(QString information){
    this->information=information;
}

void shape::setAngle(int angle){
    this->angle=angle;
}

int shape::getAngle(){
    return angle;
}

void shape::setRotatePoint(int x, int y){
    rotatePoint.setX(x);
    rotatePoint.setY(y);
}

QPoint shape::getRotatePoint(){
    return rotatePoint;
}
