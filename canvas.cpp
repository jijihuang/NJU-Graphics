#include "canvas.h"
#include "ui_canvas.h"

canvas::canvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::canvas)
{
    ui->setupUi(this);
    currentAction=NOACTION;
    current=NULL;
    start.setX(0);
    start.setY(0);
    end.setX(0);
    end.setY(0);
    width=CANVAS_WIDTH;
    height=CANVAS_HEIGHT;

    rectPen.setStyle(Qt::DashLine);
    rectPen.setWidth(2);
    rectPen.setBrush(Qt::green);
    rectPen.setCapStyle(Qt::SquareCap);

    image=new QImage(CANVAS_WIDTH,CANVAS_HEIGHT,QImage::Format_RGB32);
    image->fill(Qt::white);
    background=new QImage(CANVAS_WIDTH,CANVAS_HEIGHT,QImage::Format_RGB32);
    background->fill(Qt::white);
    withdrawBackground=new QImage(CANVAS_WIDTH,CANVAS_HEIGHT,QImage::Format_RGB32);
    withdrawBackground->fill(Qt::white);

    this->setAutoFillBackground(true);
    palette=QPalette();
    palette.setColor(QPalette::Background,QColor(225,225,225));
    this->setPalette(palette);

    pen=new QPen();
    penWidth=1;
    pen->setWidth(penWidth);
    penColor=new QColor(Qt::black);
    pen->setColor(*penColor);

    rubberWidth=10;
    rubberColor=new QColor(Qt::white);
    currentNode=-1;
    //timer=new QTimer(this);
    //connect(timer,SIGNAL(timeout()),this,SLOT(mouseClick()));
}

int canvas::getwidth(){
    return width;
}

int canvas::getheight(){
    return height;
}

canvas::~canvas()
{
    delete ui;
}

void canvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(0,0,*image);
    if (currentAction==CURVE){
        if (!curvePoints.empty()){
            QPen ctrlPen1(QColor(0,0,255));
            ctrlPen1.setWidth(7);
            painter.setPen(ctrlPen1);
            for (int i=0;i<curvePoints.size();i++){
                painter.drawPoint(curvePoints[i]);
            }
            QPen ctrlPen2(QColor(0,255,0));
            ctrlPen2.setWidth(2);
            ctrlPen2.setStyle(Qt::DashDotDotLine);
            painter.setPen(ctrlPen2);
            for (int i=0;i<curvePoints.size()-1;i++){
                painter.drawLine(curvePoints[i],curvePoints[i+1]);
            }
        }
    }
}

void canvas::load(QString imagePath){
    image->load(imagePath);
    *background=*image;
    //qDebug()<<image->size().width()<<" "<<image->size().height();
}

void canvas::load(QImage *loadImage){
    *image=*loadImage;
    *background=*image;
}

void canvas::save(QString imagePath){
    image->save(imagePath);
}

void canvas::clear(){
    whiteBackground=new QImage(CANVAS_WIDTH,CANVAS_HEIGHT,QImage::Format_RGB32);
    whiteBackground->fill(Qt::white);
    points.clear();
    curvePoints.clear();
    *image=*whiteBackground;
    *background=*whiteBackground;
    *withdrawBackground=*whiteBackground;
    current=NULL;
    update();
}

void canvas::clear(int width,int height){
    this->width=width;
    this->height=height;
    points.clear();
    curvePoints.clear();
    whiteBackground=new QImage(width,height,QImage::Format_RGB32);
    whiteBackground->fill(Qt::white);
    *image=*whiteBackground;
    *background=*whiteBackground;
    *withdrawBackground=*whiteBackground;
    current=NULL;
    update();
}

void canvas::setCurrentAction(DRAWACTION action){
    currentAction=action;
}

void canvas::setColor(QColor& chooseColor){
    *penColor=chooseColor;
}

QColor canvas::getColor(){
    return *penColor;
}

void canvas::enterEvent(QEvent *event){
    if (currentAction==LINE||currentAction==CIRCLE||currentAction==ELLIPSE||currentAction==CLIP){
        setCursor(Qt::CrossCursor);
    }
    else if(currentAction==PENCIL){
        QPixmap pencil(":/image/image/pencilcursor.png");
        setCursor(QCursor(pencil.scaled(30,30),5,20));
    }
    else if(currentAction==POLYGON||currentAction==CURVE){
        QPixmap pencil(":/image/image/edit.png");
        setCursor(QCursor(pencil.scaled(30,30),6,5));
    }
    else if(currentAction==RUBBER){
        if (rubberWidth==10){
            QPixmap pencil(":/image/image/rubberThin.png");
            setCursor(QCursor(pencil.scaled(50,50),15,15));
        }
        else if (rubberWidth==15){
            QPixmap pencil(":/image/image/rubberMedium.png");
            setCursor(QCursor(pencil.scaled(50,50),15,15));
        }
        else if (rubberWidth==20){
            QPixmap pencil(":/image/image/rubberThick.png");
            setCursor(QCursor(pencil.scaled(50,50),15,15));
        }
    }
}

void canvas::leaveEvent(QEvent *event){
    setCursor(Qt::ArrowCursor);
}

void canvas::mouseDoubleClickEvent(QMouseEvent *event){
   // timer->stop();
   // qDebug()<<"mouseDoubleClick!"<<endl;
   // int currentX=event->pos().x();
  //  int currentY=event->pos().y();
    //if((points[0].x()-currentX))
  //  qDebug()<<"x:"<<currentX<<"y:"<<currentY<<endl;
    if (currentAction==POLYGON){
        if (!points.empty()&&points.size()>1){
            drawPolygon_Bresenham(points,penColor);
            points.clear();
        }
    }
    if (currentAction==CURVE){
        if (!curvePoints.empty()&&curvePoints.size()>3){
            drawCurve_Bspline(points,penColor);
            curvePoints.clear();
        }
    }
    *background=*withdrawBackground;
    //*background=*image;
}

void canvas::mouseMoveEvent(QMouseEvent * event)
{
    // qDebug()<<tr("%1,%2").arg(event->pos().x()).arg(event->pos().y());
    if (event->buttons()&Qt::LeftButton){
        end=event->pos();
        if (currentAction==LINE){
            line currentLine(start,end);
            *image=*background;
            currentLine.draw_Bresenham(image,penColor);
        }
        if (currentAction==CIRCLE){
            circle currentcircle((start.x()+end.x())/2,(start.y()+end.y())/2,abs(start.x()-end.x())/2);
            *image=*background;
            currentcircle.draw_Bresenham(image,penColor);
        }
        if (currentAction==ELLIPSE){
            ellipse currentellipse((start.x()+end.x())/2,(start.y()+end.y())/2,abs(start.x()-end.x())/2,abs(start.y()-end.y())/2);
            *image=*background;
            currentellipse.draw_Bresenham(image,penColor);
        }
        if (currentAction==PENCIL){
            line currentLine(start,end);
            currentLine.draw_Bresenham(image,penColor);
            *background=*image;
            update();
            start=end;
        }
        if (currentAction==RUBBER){
            QRectF *rubber=new QRectF(end.x(),end.y(),rubberWidth,rubberWidth);
            rubberErase(*rubber,image,rubberColor);
        }
        if (currentAction==CURVE){
            if (currentNode!=-1){
                setCursor(Qt::SizeAllCursor);
                curvePoints[currentNode]=end;
                if (curvePoints.size()>3){
                    *image=*withdrawBackground;
                    drawCurve_Bspline(curvePoints,penColor);
                    //*image=*background;
                }
                //*image=*background;
            }
        }
        if (currentAction==CLIP){
            if (end!=canvasClipA&&end.x()!=canvasClipA.x()&&end.y()!=canvasClipA.y()){
                line line1(canvasClipA.x(),canvasClipA.y(),end.x(),canvasClipA.y());
                line line2(canvasClipA.x(),canvasClipA.y(),canvasClipA.x(),end.y());
                line line3(end.x(),end.y(),end.x(),canvasClipA.y());
                line line4(end.x(),end.y(),canvasClipA.x(),end.y());
                *image=*background;
                line1.draw_Bresenham(image,penColor);
                line2.draw_Bresenham(image,penColor);
                line3.draw_Bresenham(image,penColor);
                line4.draw_Bresenham(image,penColor);
                /*QPainter rectPainter(this);
                rectPainter.setPen(rectPen);
                rectPainter.drawRect(start.x(),start.y(),end.x()-start.x(),end.y()-start.y());*/
            }
        }
        update();
        //*image=*background;
    }
}

void canvas::mousePressEvent(QMouseEvent *event){
   // timer->start(300);
    //qDebug()<<"mousePressClick!"<<endl;
    //int currentX=event->pos().x();
    //int currentY=event->pos().y();
    //if((points[0].x()-currentX))
    //qDebug()<<"x:"<<currentX<<"y:"<<currentY<<endl;
    if (event->button()==Qt::LeftButton){
        if (currentAction!=NOACTION&&currentAction!=POLYGON&&currentAction!=CURVE){
            *withdrawBackground=*image;
            //*background=*image;
        }
        start=event->pos();
        /*if (current!=NULL){
            *image=*background;
            current->draw_Bresenham(image,penColor);
            update();
        }*/
        if (currentAction==CLIP){
            canvasClipA=start;
        }
        if (currentAction==POLYGON){
            if(points.empty()){
                *withdrawBackground=*image;
                *background=*image;
                //current=NULL;
                int currentX=start.x();
                int currentY=start.y();
                //if((points[0].x()-currentX))
                //qDebug()<<"x:"<<currentX<<"y:"<<currentY<<endl;
                points.push_back(start);
            }
            else{
                int currentX=start.x();
                int currentY=start.y();
                QPoint last=points[points.size()-1];
                if (currentX!=last.x()||currentY!=last.y()){
                    points.push_back(start);
                    if((points[0].x()-currentX)*(points[0].x()-currentX)+(points[0].y()-currentY)*(points[0].y()-currentY)<=50){
                        current=new polygon(points);
                        drawPolygon_Bresenham(points,penColor);
                        *background=*image;
                        points.clear();
                    }
                    //qDebug()<<"x:"<<currentX<<"y:"<<currentY<<endl;
                    //*image=*background;
                    else{
                         drawLine_Bresenham(last,start,penColor);
                         *background=*image;
                         current=NULL;
                    }
                    //update();
                   // polygon currentPolygon(points);
                    //currentPolygon.draw_Bresenham(image,penColor);
                }
            }
        }
        if (currentAction==CURVE){
            if(curvePoints.empty()){
                *withdrawBackground=*image;
                *background=*image;
            }
            int flag=0;
            for (int i=0;i<curvePoints.size();i++){
                double dx=curvePoints[i].x()-start.x();
                double dy=curvePoints[i].y()-start.y();
                if (dx*dx+dy*dy<100){
                    currentNode=i;
                    flag=1;
                    break;
                }
            }
            if (flag==0){
                curvePoints.push_back(start);
                currentNode=curvePoints.size()-1;
                if (curvePoints.size()>3){
                    drawCurve_Bspline(curvePoints,penColor);
                    *background=*image;
                }
                else{
                    update();
                }
            }
        }
        else{
            *background=*image;
            current=NULL;
        }
    }
}

void canvas::mouseReleaseEvent(QMouseEvent *event){
    if (event->button()==Qt::LeftButton){
        end=event->pos();
        if (currentAction==NOACTION){
            return;
        }
        if (currentAction==LINE){
            //*withdrawBackground=*image;
            drawLine_Bresenham(start,end,penColor);
            //*withdrawBackground=*image;
        }
        if (currentAction==CIRCLE){
            //*withdrawBackground=*image;
            drawCircle((start.x()+end.x())/2,(start.y()+end.y())/2,abs(start.x()-end.x())/2,penColor);
            //*withdrawBackground=*image;
        }
        if (currentAction==ELLIPSE){
           // *withdrawBackground=*image;
            QPoint rotatePoint((start.x()+end.x())/2,(start.y()+end.y())/2);
            drawEllipse((start.x()+end.x())/2,(start.y()+end.y())/2,abs(start.x()-end.x())/2,abs(start.y()-end.y())/2,0,rotatePoint,penColor);
            //*withdrawBackground=*image;
        }
        if (currentAction==PENCIL){
            line currentLine(start,end);
            currentLine.draw_Bresenham(image,penColor);
            *background=*image;
            update();
            current=NULL;
        }
        if (currentAction==RUBBER){
            //*withdrawBackground=*image;
            QRectF *rubber=new QRectF(end.x(),end.y(),rubberWidth,rubberWidth);
            rubberErase(*rubber,image,rubberColor);
            *background=*image;
            current=NULL;
            //*withdrawBackground=*image;
        }
        if (currentAction==CURVE){
            if (curvePoints.size()>3){
                drawCurve_Bspline(curvePoints,penColor);
            }
        }
        if (currentAction==CLIP){
            if (end!=canvasClipA&&end.x()!=canvasClipA.x()&&end.y()!=canvasClipA.y()){
                canvasClipB=end;
                canvasClip(image,canvasClipA,canvasClipB);
            }
        }
        //update();
    }
}

void canvas::saveCanvas(){
    *background=*image;
}

void canvas::drawLine_Bresenham(QPoint x1, QPoint x2,QColor *color){
    current=new line(x1,x2);
    //saveCanvas();
    current->draw_Bresenham(image,color);
    update();
}

void canvas::drawLine_DDA(QPoint x1, QPoint x2,QColor *color){
    current=new line(x1,x2);
    //saveCanvas();
    current->draw_DDA(image,color);
    update();
}

void canvas::drawCircle(int cx, int cy, int r,QColor *color){
    current=new circle(cx,cy,r);
    //saveCanvas();
    current->draw_Bresenham(image,color);
    update();
}

void canvas::drawEllipse(int cx, int cy, int rx, int ry,int angle,QPoint rotatePoint,QColor *color){
    current=new ellipse(cx,cy,rx,ry,angle,rotatePoint);
    //saveCanvas();
    current->draw_Bresenham(image,color);
    update();
}

void canvas::drawPolygon_DDA(vector<QPoint> points,QColor *color){
    current=new polygon(points);
    //saveCanvas();
    current->draw_DDA(image,color);
    update();
}

void canvas::drawPolygon_Bresenham(vector<QPoint> points,QColor *color){
    current=new polygon(points);
    //saveCanvas();
    current->draw_Bresenham(image,color);
    update();
}

void canvas::drawCurve_Bezier(vector<QPoint> points,QColor *color){
    current=new curve(points);
    //saveCanvas();
    current->draw_Bezier(image,color);
    update();
}

void canvas::drawCurve_Bspline(vector<QPoint> points,QColor *color){
    current=new curve(points);
    //saveCanvas();
    current->draw_Bspline(image,color);
    update();
}

void canvas::rubberErase(QRectF &rect, QImage *image, QColor *color){
    //saveCanvas();
    for(int i=rect.x();i<rect.x()+rect.width();i++){
        for(int j=rect.y();j<rect.y()+rect.height();j++){
            image->setPixelColor(i,j,*color);
        }
    }
}

void canvas::setWidthThin(){
    rubberWidth=10;
    penWidth=1;
}

void canvas::setWidthMedium(){
    rubberWidth=15;
    penWidth=4;
}

void canvas::setWidthThick(){
    rubberWidth=20;
    penWidth=8;
}

void canvas::withdrawAction(){
    if (currentAction==CURVE){
        if (!curvePoints.empty()){
            curvePoints.clear();
        }
    }
    *image=*withdrawBackground;
    *background=*withdrawBackground;
    current=NULL;
    update();
}

void canvas::translateAction(){
    if (current!=NULL){
        TranslateDialog *translateDialog=new TranslateDialog(this);
        int ret=translateDialog->exec();
        if(ret==QDialog::Accepted){
            int x=translateDialog->getX();
            int y=translateDialog->getY();
            current->translate(x,y);
            if (currentAction!=CURVE){
                *withdrawBackground=*image;
                *image=*background;
                current->draw_Bresenham(image,penColor);
            }
            else{
                *background=*image;
                *image=*withdrawBackground;
                *withdrawBackground=*image;
                current->draw_Bspline(image,penColor);
                curvePoints=current->getPoints();
            }
            update();
        }
        delete translateDialog;
    }
}

void canvas::clipAction(){
    if(currentAction==LINE&&current!=NULL){
        ClipDialog *clipDialog=new ClipDialog(this);
        int ret=clipDialog->exec();
        if(ret==QDialog::Accepted){
            int x1=clipDialog->getX1();
            int y1=clipDialog->getY1();
            int x2=clipDialog->getX2();
            int y2=clipDialog->getY2();
            current->clip_Cohen_Sutherland(x1,y1,x2,y2);
            *withdrawBackground=*image;
            *image=*background;
            current->draw_Bresenham(image,penColor);
            update();
        }
        delete clipDialog;
    }
}

void canvas::rotateAction(){
    if (current!=NULL){
        rotateDialog *rotatedialog=new rotateDialog(this);
        QPoint p=current->getCentralPoint();
        rotatedialog->setXY(p);
        int ret=rotatedialog->exec();
        if(ret==QDialog::Accepted){
            int x=rotatedialog->getX();
            int y=rotatedialog->getY();
            int r=rotatedialog->getR();
            current->rotate(x,y,r);
            if (currentAction!=CURVE){
                *withdrawBackground=*image;
                *image=*background;
                current->draw_Bresenham(image,penColor);
            }
            else{
                *background=*image;
                *image=*withdrawBackground;
                *withdrawBackground=*image;
                current->draw_Bspline(image,penColor);
                curvePoints=current->getPoints();
            }
            update();
        }
        delete rotatedialog;
    }
}

void canvas::scaleAction(){
    if (current!=NULL){
        ScaleDialog *scaleDialog=new ScaleDialog(this);
        QPoint p=current->getCentralPoint();
        scaleDialog->setXY(p);
        int ret=scaleDialog->exec();
        if(ret==QDialog::Accepted){
            int x=scaleDialog->getX();
            int y=scaleDialog->getY();
            double s=scaleDialog->getS();
            current->scale(x,y,s);
            if (currentAction!=CURVE){
                *withdrawBackground=*image;
                *image=*background;
                current->draw_Bresenham(image,penColor);
            }
            else{
                *background=*image;
                *image=*withdrawBackground;
                *withdrawBackground=*image;
                current->draw_Bspline(image,penColor);
                curvePoints=current->getPoints();
            }
            update();
        }
        delete scaleDialog;
    }
}

void canvas::canvasClip(QImage *image, QPoint a, QPoint b){
    int x1,x2,y1,y2;
    if (a.x()>b.x()){
        x1=b.x();
        x2=a.x();
    }
    else{
        x1=a.x();
        x2=b.x();
    }
    if (a.y()>b.y()){
        y1=b.y();
        y2=a.y();
    }
    else{
        y1=a.y();
        y2=b.y();
    }
    *image=image->copy(x1+1,y1+1,x2-x1-1,y2-y1-1);
    update();
}
