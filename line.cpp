#include"line.h"
using namespace std;
line::line()
{
    p0.setX(0);
    p0.setY(0);
    pn.setX(0);
    pn.setY(0);
    //color=new QColor(Qt::black);
    this->setName("line");
}

line::line(QPoint p0,QPoint pn)
{
    this->p0=p0;
    this->pn=pn;
    //color=new QColor(Qt::black);
    this->setName("line");
}

line::line(int x0,int y0,int x1,int y1)
{
    p0.setX(x0);
    p0.setY(y0);
    pn.setX(x1);
    pn.setY(y1);
    //color=new QColor(Qt::black);
    this->setName("line");
}

QPoint line::getP0(){
    return p0;
}

QPoint line::getPn(){
    return pn;
}

QPoint line::getCentralPoint(){
    int retX=(p0.x()+pn.x())/2;
    int retY=(p0.y()+pn.y())/2;
    return QPoint(retX,retY);
}

void line::setInformation(int x1, int x2, int y1, int y2){
    this->p0.setX(x1);
    this->p0.setY(y1);
    this->pn.setX(x2);
    this->pn.setY(y2);
}


void line::translate(int x, int y){
    p0.setX(p0.x()+x);
    p0.setY(p0.y()+y);
    pn.setX(pn.x()+x);
    pn.setY(pn.y()+y);
}

void line::rotate(int x, int y, int r){
    double theta=r*PI/180;
    double c=cos(theta);
    double s=sin(theta);
    int x0=p0.x();
    int y0=p0.y();
    int xn=pn.x();
    int yn=pn.y();
    int xx0=int(x+(x0-x)*c-(y0-y)*s);
    int yy0=int(y+(x0-x)*s+(y0-y)*c);
    int xxn=int(x+(xn-x)*c-(yn-y)*s);
    int yyn=int(y+(xn-x)*s+(yn-y)*c);
    p0.setX(xx0);
    p0.setY(yy0);
    pn.setX(xxn);
    pn.setY(yyn);
}

int line::getClipCode(QPoint p,int x1, int y1, int x2, int y2){
    int code=0;
    int x=p.x();
    int y=p.y();
    if (x<x1) code|=left;
    if (x>x2) code|=right;
    if (y<y1) code|=top;
    if (y>y2) code|=bottom;
    return code;
}

void line::clip_Cohen_Sutherland(int x1, int y1, int x2, int y2){
    int code1=getClipCode(p0,x1,y1,x2,y2);
    int code2=getClipCode(pn,x1,y1,x2,y2);
    if (code1==0&&code2==0)return;
    if (code1&code2){
        p0.setX(0);
        p0.setY(0);
        pn.setX(0);
        pn.setY(0);
        return;
    }
    float x0=p0.x();
    float y0=p0.y();
    float xn=pn.x();
    float yn=pn.y();
    float k=(yn-y0)/(xn-x0);
    int flag=0;
    while(code1!=0||code2!=0){
        int code=0;
        int x=0,y=0;
        if(code1!=0){
            code=code1;
            x=p0.x();
            y=p0.y();
            flag=0;
        }
        else{
            code=code2;
            x=pn.x();
            y=pn.y();
            flag=1;
        }
        if (code &left){
            x=x1;
            y=k*(x1-x0)+y0;
            code=getClipCode(QPoint(x,y),x1,y1,x2,y2);
            if (flag==0){
               code1=code;
               p0.setX(x);
               p0.setY(y);
            }
            else{
                code2=code;
                pn.setX(x);
                pn.setY(y);
            }
        }
        if (code &right){
            x=x2;
            y=k*(x2-x0)+y0;
            code=getClipCode(QPoint(x,y),x1,y1,x2,y2);
            if (flag==0){
               code1=code;
               p0.setX(x);
               p0.setY(y);
            }
            else{
                code2=code;
                pn.setX(x);
                pn.setY(y);
            }
        }
        if (code &top){
            y=y1;
            x=(y1-y0)/k+x0;
            code=getClipCode(QPoint(x,y),x1,y1,x2,y2);
            if (flag==0){
               code1=code;
               p0.setX(x);
               p0.setY(y);
            }
            else{
                code2=code;
                pn.setX(x);
                pn.setY(y);
            }
        }
        if (code &bottom){
            y=y2;
            x=(y2-y0)/k+x0;
            code=getClipCode(QPoint(x,y),x1,y1,x2,y2);
            if (flag==0){
               code1=code;
               p0.setX(x);
               p0.setY(y);
            }
            else{
                code2=code;
                pn.setX(x);
                pn.setY(y);
            }
        }
    }
}

int line::clipCal(float p, float q, float *tl, float *tu){
    int flag=1;
    float r;
    if (p<0.0){
        r=q/p;
        if (r>*tu){
            flag=0;
        }
        else if (r>*tl){
            *tl=r;
        }
    }
    else if (p>0.0){
        r=q/p;
        if (r<*tl){
            flag=0;
        }
        else if (r<*tu){
            *tu=r;
        }
    }
    else if (q<0&&p==0){
        flag=0;
    }
    return flag;
}

void line::clip_Liang_Barsky(int x1, int y1, int x2, int y2){
    float dx,dy,x0,xn,y0,yn,tl,tu;
    x0=p0.x();
    y0=p0.y();
    xn=pn.x();
    yn=pn.y();
    dx=xn-x0;
    tl=0.0;
    tu=1.0;
    if (clipCal(-dx,x0-x1,&tl,&tu))
        if (clipCal(dx,x2-x0,&tl,&tu)){
            dy=yn-y0;
            if (clipCal(-dy,y0-y1,&tl,&tu))
                if (clipCal(dy,y2-y0,&tl,&tu)){
                    if (tu<1.0){
                        xn=x0+tu*dx;
                        yn=y0+tu*dy;
                    }
                    if (tl>0.0){
                        x0=x0+tl*dx;
                        y0=y0+tl*dy;
                    }
                    p0.setX(x0);
                    p0.setY(y0);
                    pn.setX(xn);
                    pn.setY(yn);
                }
        }
}


void line::draw_Bresenham(QImage *image,QColor *color)
{
    int x0=p0.x();
    int y0=p0.y();
    int x1=pn.x();
    int y1=pn.y();
    int dx=abs(x1-x0);
    int dy=abs(y1-y0);
    int mflag=0;
    if (dx<dy){
        mflag=1;
        int temp=x0;
        x0=y0;
        y0=temp;
        temp=x1;
        x1=y1;
        y1=temp;
        temp=dx;
        dx=dy;
        dy=temp;
    }
    int detaX=1;
    int detaY=1;
    if (x1-x0<0)detaX=-1;
    if (y1-y0<0)detaY=-1;
    int x=x0;
    int y=y0;
    int p=2*dy-dx;
    int d2y=2*dy;
    int d2yx=2*(dy-dx);
    if (mflag==0){
        while (x!=x1){
            image->setPixelColor(x,y,*color);
            if (p<0) p=p+d2y;
            else{
                y=y+detaY;
                p=p+d2yx;
            }
            x+=detaX;
        }
        image->setPixelColor(x,y,*color);
    }
    else{
        while (x!=x1){
            image->setPixelColor(y,x,*color);
            if (p<0) p=p+d2y;
            else{
                y=y+detaY;
                p=p+d2yx;
            }
            x+=detaX;
        }
        image->setPixelColor(y,x,*color);
    }
}

void line::draw_DDA(QImage *image, QColor *color){
    int x0=p0.x();
    int y0=p0.y();
    int x1=pn.x();
    int y1=pn.y();
    float delta_x,delta_y,x,y;
    int dx,dy,len;
    dx=x1-x0;
    dy=y1-y0;
    if(abs(dx)>abs(dy))len=abs(dx);
    else len=abs(dy);
    delta_x=(float)dx/(float)len;
    delta_y=(float)dy/(float)len;
    x=x0;
    y=y0;
    image->setPixelColor(x,y,*color);
    for (int k=1;k<=len;k++){
        x+=delta_x;
        y+=delta_y;
        image->setPixelColor(x,y,*color);
    }
}

void line::scale(int x, int y, float s){
    int x1=int(float(p0.x()*s+x*(1-s)));
    int y1=int(float(p0.y()*s+y*(1-s)));
    int x2=int(float(pn.x()*s+x*(1-s)));
    int y2=int(float(pn.y()*s+y*(1-s)));
    p0.setX(x1);
    p0.setY(y1);
    pn.setX(x2);
    pn.setY(y2);
}
