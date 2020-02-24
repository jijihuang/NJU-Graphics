#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Painting");
    resize(1280,800);
    this->setAutoFillBackground(true);

    //menuBar
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(createNew()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveFile()));
    connect(ui->actionRead,SIGNAL(triggered()),this,SLOT(readFile()));
    connect(ui->actionClear,SIGNAL(triggered()),this,SLOT(clearCanvas()));
    connect(ui->actionWithdraw,SIGNAL(triggered()),this,SLOT(withdrawAction()));
    connect(ui->actionClip,SIGNAL(triggered()),this,SLOT(clipAction()));
    connect(ui->actionTranslate,SIGNAL(triggered()),this,SLOT(translateAction()));
    connect(ui->actionScale,SIGNAL(triggered()),this,SLOT(scaleAction()));
    connect(ui->actionRotate,SIGNAL(triggered()),this,SLOT(rotateAction()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(aboutApp()));



    //canvas
    centralCanvas=new canvas();
    this->setCentralWidget(centralCanvas);

    //toolBar
    toolBar=new QToolBar();
    toolBar->setMovable(false);
    toolBar->setIconSize(QSize(30,30));
    toolBar->setFixedWidth(50);
    toolBar->setFloatable(false);
    this->addToolBar(Qt::LeftToolBarArea,toolBar);



    //vboxLayout
    /*vboxLayout=new QVBoxLayout();
    vboxLayout->addWidget(this);
    setLayout(vboxLayout);*/


    //tool
    color=new QAction(QIcon(":/image/image/color.png"),tr("COLOR"),toolBar);
    color->setToolTip(tr("color"));
    //color->setCheckable(true);
    connect(color,SIGNAL(triggered()),this,SLOT(chooseColor()));
    toolBar->addAction(color);

    pencil=new QAction(QIcon(":/image/image/pencil.png"),tr("PENCIL"),toolBar);
    pencil->setToolTip(tr("pencil"));
    pencil->setCheckable(true);
    connect(pencil,SIGNAL(triggered()),this,SLOT(pencildraw()));
    toolBar->addAction(pencil);

    rubber=new QAction(QIcon(":/image/image/rubber.png"),tr("RUBBER"),toolBar);
    rubber->setToolTip(tr("rubber"));
    rubber->setCheckable(true);
    connect(rubber,SIGNAL(triggered()),this,SLOT(rubberErase()));
    toolBar->addAction(rubber);

    setWidth=new QAction(QIcon(":/image/image/width.png"),tr("WIDTH"),toolBar);
    setWidth->setToolTip(tr("width"));
    //setWidth->setCheckable(true);
    setWidthMenu=new QMenu();
    //setWidthMenu->setVisible(false);
    //setWidthMenu->palette()
    //setWidthMenu->addSeparator();
    //setWidthMenu.addAction(exit);
    setWidth->setMenu(setWidthMenu);
    widthThin=new QAction(QIcon(":/image/image/widthThin.png"),tr(""),this);
    widthMeduim=new QAction(QIcon(":/image/image/widthMedium.png"),tr(""),this);
    widthThick=new QAction(QIcon(":/image/image/widthThick.png"),tr(""),this);

    //widthThin->setVisible(false);
    //widthMeduim->setVisible(false);
    //widthThick->setVisible(false);
    connect(widthThin,SIGNAL(triggered()),this,SLOT(setWidthThin()));
    connect(widthMeduim,SIGNAL(triggered()),this,SLOT(setWidthMedium()));
    connect(widthThick,SIGNAL(triggered()),this,SLOT(setWidthThick()));
    setWidthMenu->addAction(widthThin);
    setWidthMenu->addAction(widthMeduim);
    setWidthMenu->addAction(widthThick);
    //connect(setWidth,SIGNAL(triggered()),this,SLOT(setWidth()));
    toolBar->addAction(setWidth);

    clipCanvasAction=new QAction(QIcon(":/image/image/clip2.png"),tr("CLIP"),toolBar);
    clipCanvasAction->setToolTip(tr("clip"));
    clipCanvasAction->setCheckable(true);
    connect(clipCanvasAction,SIGNAL(triggered()),this,SLOT(canvasClip()));
    toolBar->addAction(clipCanvasAction);

    lineAction=new QAction(QIcon(":/image/image/Line.png"),tr("LINE"),toolBar);
    lineAction->setToolTip(tr("line"));
    lineAction->setCheckable(true);
    connect(lineAction,SIGNAL(triggered()),this,SLOT(drawLine()));
    toolBar->addAction(lineAction);

    curveAction=new QAction(QIcon(":/image/image/Curve.png"),tr("CURVE"),toolBar);
    curveAction->setToolTip(tr("curve"));
    curveAction->setCheckable(true);
    connect(curveAction,SIGNAL(triggered()),this,SLOT(drawCurve()));
    toolBar->addAction(curveAction);

    circleAction=new QAction(QIcon(":/image/image/Circle.png"),tr("CIRCLE"),toolBar);
    circleAction->setToolTip(tr("circle"));
    circleAction->setCheckable(true);
    connect(circleAction,SIGNAL(triggered()),this,SLOT(drawCircle()));
    toolBar->addAction(circleAction);

    ellipseAction=new QAction(QIcon(":/image/image/Ellipse.png"),tr("ELLIPSE"),toolBar);
    ellipseAction->setToolTip(tr("ellipse"));
    ellipseAction->setCheckable(true);
    connect(ellipseAction,SIGNAL(triggered()),this,SLOT(drawEllipse()));
    toolBar->addAction(ellipseAction);

    polygonAction=new QAction(QIcon(":/image/image/polygon.png"),tr("POLYGON"),toolBar);
    polygonAction->setToolTip(tr("polygon"));
    polygonAction->setCheckable(true);
    connect(polygonAction,SIGNAL(triggered()),this,SLOT(drawPolygon()));
    toolBar->addAction(polygonAction);

    //toolGroup
    toolGroup = new QActionGroup(this);
    toolGroup->addAction(color);
    toolGroup->addAction(circleAction);
    toolGroup->addAction(lineAction);
    toolGroup->addAction(ellipseAction);
    toolGroup->addAction(polygonAction);
    toolGroup->addAction(rubber);
    toolGroup->addAction(pencil);
    toolGroup->addAction(setWidth);
    toolGroup->addAction(curveAction);
    toolGroup->addAction(clipCanvasAction);

    //color
    readColorB=0;
    readColorR=0;
    readColorG=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile(){
    QString filePath = QFileDialog::getOpenFileName(this,tr("openFile"),"c:\\",tr("Image (*.bmp *.jpg *.png *.jpeg)"));
    centralCanvas->load(filePath);
}

void MainWindow::createNew(){
    MainWindow *newProject=new MainWindow();
    newProject->show();
}

void MainWindow::saveFile(){
    QString filePath = QFileDialog::getSaveFileName(this,tr("saveFile"),"c:\\",tr("Image (*.bmp *.jpg *.png *.jpeg)"));
    centralCanvas->save(filePath);
}

void MainWindow::saveFile(QString imagePath,QString saveDir){
    QString filePath=saveDir+"/"+imagePath+".bmp";
    centralCanvas->save(filePath);
}

void MainWindow::readFile(){
    QString filePath = QFileDialog::getOpenFileName(this,tr("openFile"),"c:\\",tr("Text (*.txt)"));
    readFile(filePath,QDir::currentPath());
}

void MainWindow::readFile(QString filePath,QString saveDir){
    shapeList.clear();
    CanvasList.clear();
    QFile f(filePath);
    if (!f.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"Open failed!"<<endl;
    }
    QTextStream txtInput(&f);
    QString lineStr;
    while (!txtInput.atEnd())
    {
        lineStr=txtInput.readLine();
        //lineInstructions.push_back(lineStr);
        //qDebug()<<lineStr<<endl;
        QStringList lineStrList=lineStr.split(" ");
        if (lineStrList.at(0)=="resetCanvas"){
            if (lineStrList.length()==3){
                int width=lineStrList.at(1).toInt();
                int height=lineStrList.at(2).toInt();
                if (width>=100&&width<=1000&&height>=100&&height<=1000){
                    CanvasList.clear();
                    clearCanvas(width,height);
                }
                else{
                    qDebug()<<"The width or height of Canvas is out of scope!";
                }
            }
           else{
                qDebug()<<"Wrong format of resetCanvas!"<<endl;
            }
        }
        else if (lineStrList.at(0)=="setColor"){
            if (lineStrList.length()==4){
                int R=lineStrList.at(1).toInt();
                int G=lineStrList.at(2).toInt();
                int B=lineStrList.at(3).toInt();
                if (R>=0&&R<=255&&G>=0&&G<=255&&B>=0&&B<=255){
                    setColor(R,G,B);
                }
                else{
                    qDebug()<<"The value of RGB is out of scope!";
                }
            }
           else{
                qDebug()<<"Wrong format of setColor!"<<endl;
            }
        }
        else if (lineStrList.at(0)=="saveCanvas"){
            if (lineStrList.length()==2){
                QString name=lineStrList.at(1);
                saveFile(name,saveDir);
            }
           else{
                qDebug()<<"Wrong format of resetCanvas!"<<endl;
            }
        }
        else if (lineStrList.at(0)=="drawLine"){
            if (lineStrList.length()==7){
                int id=lineStrList.at(1).toInt();
                int x1=lineStrList.at(2).toInt();
                int y1=lineStrList.at(3).toInt();
                int x2=lineStrList.at(4).toInt();
                int y2=lineStrList.at(5).toInt();
                QString algorithm=lineStrList.at(6);
                shape current;
                current.setAngle(0);
                current.setId(id);
                current.setName("line");
                current.setColor(readColorR,readColorG,readColorB);
                current.setAlgorithm(algorithm);
                current.setInformation(lineStrList.at(2)+" "+lineStrList.at(3)+" "+lineStrList.at(4)+" "+lineStrList.at(5));
                shapeList.push_back(current);
                CanvasList.push_back(current);
                QColor *tempColor=new QColor(current.getColor());
                if (x1>=0&&x1<=centralCanvas->getwidth()&&x2>=0&&x2<=centralCanvas->getwidth()&&y1>=0&&y1<=centralCanvas->getheight()&&y2>=0&&y2<=centralCanvas->getheight()){
                    if (algorithm=="DDA"){
                        centralCanvas->saveCanvas();
                        centralCanvas->drawLine_DDA(QPoint(x1,y1),QPoint(x2,y2),tempColor);
                    }
                    else if (algorithm=="Bresenham"){
                        centralCanvas->saveCanvas();
                        centralCanvas->drawLine_Bresenham(QPoint(x1,y1),QPoint(x2,y2),tempColor);
                    }
                }
                else{
                    qDebug()<<"The value of Line is out of scope!";
                }
            }
           else{
                qDebug()<<"Wrong format of drawLine!"<<endl;
            }
        }
        else if (lineStrList.at(0)=="drawEllipse"){
            if (lineStrList.length()==6){
                int id=lineStrList.at(1).toInt();
                int cx=lineStrList.at(2).toInt();
                int cy=lineStrList.at(3).toInt();
                int rx=lineStrList.at(4).toInt();
                int ry=lineStrList.at(5).toInt();
                QString algorithm="Bresenham";
                if (cx>=0&&cx<=centralCanvas->getwidth()&&rx>=0&&rx<=centralCanvas->getwidth()/2&&cy>=0&&cy<=centralCanvas->getheight()&&ry>=0&&ry<=centralCanvas->getheight()/2){
                    shape current;
                    current.setAngle(0);
                    current.setId(id);
                    current.setColor(readColorR,readColorG,readColorB);
                    current.setAlgorithm(algorithm);
                    current.setRotatePoint(cx,cy);
                    QColor *tempColor=new QColor(current.getColor());
                    if (rx==ry){
                        current.setName("circle");
                        current.setInformation(lineStrList.at(2)+" "+lineStrList.at(3)+" "+lineStrList.at(4));
                        shapeList.push_back(current);
                        CanvasList.push_back(current);
                        centralCanvas->saveCanvas();
                        centralCanvas->drawCircle(cx,cy,rx,tempColor);
                    }
                    else{
                        current.setName("ellipse");
                        current.setInformation(lineStrList.at(2)+" "+lineStrList.at(3)+" "+lineStrList.at(4)+" "+lineStrList.at(5));
                        shapeList.push_back(current);
                        CanvasList.push_back(current);
                        centralCanvas->saveCanvas();
                        centralCanvas->drawEllipse(cx,cy,rx,ry,0,current.getRotatePoint(),tempColor);
                    }
                }
                else{
                    qDebug()<<"The value of Line is out of scope!";
                }
            }
           else{
                qDebug()<<"Wrong format of drawEllipse!"<<endl;
            }

        }
        else if (lineStrList.at(0)=="drawPolygon"){
            if (lineStrList.length()==4){
                shape current;
                vector<QPoint>points;
                int id=lineStrList.at(1).toInt();
                int n=lineStrList.at(2).toInt();
                QString algorithm=lineStrList.at(3);
                lineStr=txtInput.readLine();
                lineStrList=lineStr.split(" ");
                for(int i=0;i<n;i++){
                    QPoint temp;
                    int x,y;
                    x=lineStrList.at(2*i).toInt();
                    y=lineStrList.at(2*i+1).toInt();
                    if (x<0||x>centralCanvas->getwidth()||y<0||y>centralCanvas->getheight()){
                        qDebug()<<"The value of Line is out of scope!"<<endl;
                        return;
                    }
                    else{
                        temp.setX(x);
                        temp.setY(y);
                        points.push_back(temp);
                    }
                }
                current.setId(id);
                current.setAngle(0);
                current.setName("polygon");
                current.setColor(readColorR,readColorG,readColorB);
                current.setAlgorithm(algorithm);
                current.setInformation(lineStr);
                shapeList.push_back(current);
                CanvasList.push_back(current);
                QColor *tempColor=new QColor(current.getColor());
                if (algorithm=="DDA"){
                    centralCanvas->saveCanvas();
                    centralCanvas->drawPolygon_DDA(points,tempColor);
                }
                    else if (algorithm=="Bresenham"){
                        centralCanvas->saveCanvas();
                        centralCanvas->drawPolygon_Bresenham(points,tempColor);
                    }
            }
           else{
                qDebug()<<"Wrong format of drawPolygon!"<<endl;
            }
        }
        else if (lineStrList.at(0)=="drawCurve"){
            if (lineStrList.length()==4){
                shape current;
                vector<QPoint>points;
                int id=lineStrList.at(1).toInt();
                int n=lineStrList.at(2).toInt();
                QString algorithm=lineStrList.at(3);
                lineStr=txtInput.readLine();
                lineStrList=lineStr.split(" ");
                for(int i=0;i<n;i++){
                    QPoint temp;
                    int x,y;
                    x=lineStrList.at(2*i).toInt();
                    y=lineStrList.at(2*i+1).toInt();
                    if (x<0||x>centralCanvas->getwidth()||y<0||y>centralCanvas->getheight()){
                        qDebug()<<"The value of Line is out of scope!"<<endl;
                        return;
                    }
                    else{
                        temp.setX(x);
                        temp.setY(y);
                        points.push_back(temp);
                    }
                }
                current.setId(id);
                current.setAngle(0);
                current.setName("curve");
                current.setColor(readColorR,readColorG,readColorB);
                current.setAlgorithm(algorithm);
                current.setInformation(lineStr);
                shapeList.push_back(current);
                CanvasList.push_back(current);
                QColor *tempColor=new QColor(current.getColor());
                if (algorithm=="Bezier"){
                    centralCanvas->saveCanvas();
                    centralCanvas->drawCurve_Bezier(points,tempColor);
                }
                    else if (algorithm=="B-spline"){
                        centralCanvas->saveCanvas();
                        centralCanvas->drawCurve_Bspline(points,tempColor);
                    }
            }
           else{
                qDebug()<<"Wrong format of drawPolygon!"<<endl;
            }
        }
        else if (lineStrList.at(0)=="translate"){
            if (lineStrList.length()==4){
                int id=lineStrList.at(1).toInt();
                int dx=lineStrList.at(2).toInt();
                int dy=lineStrList.at(3).toInt();
                int i;
                for(i=0;i<shapeList.size();i++){
                    if (shapeList[i].getId()==id){
                        if (shapeList[i].getName()=="line"){
                            line temp;
                            temp=getLineInformation(shapeList[i].getInformation());
                            temp.translate(dx,dy);
                            temp.setColor(shapeList[i].getColor());
                            int x1=temp.getP0().x();
                            int y1=temp.getP0().y();
                            int x2=temp.getPn().x();
                            int y2=temp.getPn().y();
                            if (x1>=0&&x1<=centralCanvas->getwidth()&&x2>=0&&x2<=centralCanvas->getwidth()&&y1>=0&&y1<=centralCanvas->getheight()&&y2>=0&&y2<=centralCanvas->getheight()){
                                QString tempInformation=QString::number(x1)+" "+QString::number(y1)+" "+QString::number(x2)+" "+QString::number(y2);
                                shapeList[i].setInformation(tempInformation);
                                for (int j=0;j<CanvasList.size();j++){
                                    if (CanvasList[j].getId()==id){
                                        CanvasList[j].setInformation(tempInformation);
                                    }
                                }
                                /*if (shapeList[i].getAlgorithm()=="DDA"){
                                    centralCanvas->saveCanvas();
                                    centralCanvas->drawLine_DDA(QPoint(x1,y1),QPoint(x2,y2));
                                }
                                else if (shapeList[i].getAlgorithm()=="Bresenham"){
                                    centralCanvas->saveCanvas();
                                    centralCanvas->drawLine_Bresenham(QPoint(x1,y1),QPoint(x2,y2));
                                }*/
                            }
                            else{
                                qDebug()<<"The value of Line is out of scope!";
                                return;
                            }
                        }
                        if (shapeList[i].getName()=="circle"){
                            circle temp;
                            temp=getCircleInformation(shapeList[i].getInformation());
                            temp.translate(dx,dy);
                            temp.setColor(shapeList[i].getColor());
                            int cx=temp.getCentralPoint().x();
                            int cy=temp.getCentralPoint().y();
                            int rx=temp.getRadius();
                            if (cx>=0&&cx<=centralCanvas->getwidth()&&rx>=0&&rx<=centralCanvas->getwidth()/2&&cy>=0&&cy<=centralCanvas->getheight()){
                                QString tempInformation=QString::number(cx)+" "+QString::number(cy)+" "+QString::number(cy)+" "+QString::number(rx);
                                shapeList[i].setInformation(tempInformation);
                                for (int j=0;j<CanvasList.size();j++){
                                    if (CanvasList[j].getId()==id){
                                        CanvasList[j].setInformation(tempInformation);
                                    }
                                }
                                //centralCanvas->saveCanvas();
                                //centralCanvas->drawCircle(cx,cy,rx);
                            }
                            else{
                                qDebug()<<"The value of Line is out of scope!";
                                return;
                            }
                        }
                        if (shapeList[i].getName()=="ellipse"){
                            ellipse temp;
                            temp=getEllipseInformation(shapeList[i].getInformation());
                            temp.translate(dx,dy);
                            temp.setColor(shapeList[i].getColor());
                            int cx=temp.getCentralPoint().x();
                            int cy=temp.getCentralPoint().y();
                            int rx=temp.getRadiusX();
                            int ry=temp.getRadiusY();
                            if (cx>=0&&cx<=centralCanvas->getwidth()&&rx>=0&&rx<=centralCanvas->getwidth()/2&&cy>=0&&cy<=centralCanvas->getheight()&&ry>=0&&ry<=centralCanvas->getheight()/2){
                                QString tempInformation=QString::number(cx)+" "+QString::number(cy)+" "+QString::number(cy)+" "+QString::number(rx)+" "+QString::number(ry);
                                shapeList[i].setInformation(tempInformation);
                                for (int j=0;j<CanvasList.size();j++){
                                    if (CanvasList[j].getId()==id){
                                        CanvasList[j].setInformation(tempInformation);
                                    }
                                }
                                //centralCanvas->saveCanvas();
                                //centralCanvas->drawEllipse(cx,cy,rx,ry);
                            }
                            else{
                                qDebug()<<"The value of Line is out of scope!";
                                return;
                            }
                        }
                        if (shapeList[i].getName()=="polygon"){
                            polygon temp;
                            temp=getPolygonInformation(shapeList[i].getInformation());
                            temp.translate(dx,dy);
                            temp.setColor(shapeList[i].getColor());
                            vector<QPoint> points=temp.getPoints();
                            int n=points.size();
                            QString information;
                            for(int j=0;j<n;j++){
                                int x,y;
                                x=points[j].x();
                                y=points[j].y();
                                if (x<0||x>centralCanvas->getwidth()||y<0||y>centralCanvas->getheight()){
                                    qDebug()<<"The value of Line is out of scope!"<<endl;
                                    return;
                                }
                                else{
                                    information=information+QString::number(x)+" "+QString::number(y)+" ";
                                }
                            }
                            shapeList[i].setInformation(information);
                            for (int j=0;j<CanvasList.size();j++){
                                if (CanvasList[j].getId()==id){
                                    CanvasList[j].setInformation(information);
                                }
                            }
                            /*if (shapeList[i].getAlgorithm()=="DDA"){
                                centralCanvas->saveCanvas();
                                centralCanvas->drawPolygon_DDA(points);
                            }
                            else if (shapeList[i].getAlgorithm()=="Bresenham"){
                                    centralCanvas->saveCanvas();
                                    centralCanvas->drawPolygon_Bresenham(points);
                            }*/
                        }
                        if (shapeList[i].getName()=="curve"){
                            curve temp;
                            temp=getCurveInformation(shapeList[i].getInformation());
                            temp.translate(dx,dy);
                            temp.setColor(shapeList[i].getColor());
                            vector<QPoint> points=temp.getPoints();
                            int n=points.size();
                            QString information;
                            for(int j=0;j<n;j++){
                                int x,y;
                                x=points[j].x();
                                y=points[j].y();
                                if (x<0||x>centralCanvas->getwidth()||y<0||y>centralCanvas->getheight()){
                                    qDebug()<<"The value of Line is out of scope!"<<endl;
                                    return;
                                }
                                else{
                                    information=information+QString::number(x)+" "+QString::number(y)+" ";
                                }
                            }
                            shapeList[i].setInformation(information);
                            for (int j=0;j<CanvasList.size();j++){
                                if (CanvasList[j].getId()==id){
                                    CanvasList[j].setInformation(information);
                                }
                            }
                        }
                        clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
                        drawAllPartern();
                    }
                }
                if (i>shapeList.size()){
                    qDebug()<<"Can not find the id!"<<endl;
                }
            }
           else{
                qDebug()<<"Wrong format of translate!"<<endl;
            }
            //clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
            //drawAllPartern();
        }
        else if (lineStrList.at(0)=="rotate"){
            if (lineStrList.length()==5){
                int id=lineStrList.at(1).toInt();
                int x=lineStrList.at(2).toInt();
                int y=lineStrList.at(3).toInt();
                int r=lineStrList.at(4).toInt();
                int i;
                if (x>=0&&x<=centralCanvas->getwidth()&&y>=0&&y<=centralCanvas->getheight()){
                    for(i=0;i<shapeList.size();i++){
                        if (shapeList[i].getId()==id){
                            if (shapeList[i].getName()=="line"){
                                line temp;
                                temp=getLineInformation(shapeList[i].getInformation());
                                temp.rotate(x,y,r);
                                temp.setColor(shapeList[i].getColor());
                                int x1=temp.getP0().x();
                                int y1=temp.getP0().y();
                                int x2=temp.getPn().x();
                                int y2=temp.getPn().y();
                                QString tempInformation=QString::number(x1)+" "+QString::number(y1)+" "+QString::number(x2)+" "+QString::number(y2);
                                shapeList[i].setInformation(tempInformation);
                                for (int j=0;j<CanvasList.size();j++){
                                    if (CanvasList[j].getId()==id){
                                        CanvasList[j].setInformation(tempInformation);
                                    }
                                }
                                clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
                                drawAllPartern();
                                    /*if (shapeList[i].getAlgorithm()=="DDA"){
                                        centralCanvas->saveCanvas();
                                        centralCanvas->drawLine_DDA(QPoint(x1,y1),QPoint(x2,y2));
                                    }
                                    else if (shapeList[i].getAlgorithm()=="Bresenham"){
                                        centralCanvas->saveCanvas();
                                        centralCanvas->drawLine_Bresenham(QPoint(x1,y1),QPoint(x2,y2));
                                    }*/
                            }
                            if (shapeList[i].getName()=="circle"){
                                circle temp;
                                temp=getCircleInformation(shapeList[i].getInformation());
                                temp.rotate(x,y,r);
                                temp.setColor(shapeList[i].getColor());
                                int cx=temp.getCentralPoint().x();
                                int cy=temp.getCentralPoint().y();
                                int rx=temp.getRadius();
                                QString tempInformation=QString::number(cx)+" "+QString::number(cy)+" "+QString::number(cy)+" "+QString::number(rx);
                                shapeList[i].setInformation(tempInformation);
                                for (int j=0;j<CanvasList.size();j++){
                                    if (CanvasList[j].getId()==id){
                                        CanvasList[j].setInformation(tempInformation);
                                    }
                                }
                                //centralCanvas->saveCanvas();
                                //centralCanvas->drawCircle(cx,cy,rx);
                                clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
                                drawAllPartern();
                            }
                            if (shapeList[i].getName()=="ellipse"){
                                shapeList[i].setAngle(shapeList[i].getAngle()+r);
                                shapeList[i].setRotatePoint(x,y);
                                for (int j=0;j<CanvasList.size();j++){
                                    if (CanvasList[j].getId()==id){
                                        CanvasList[j].setAngle(CanvasList[j].getAngle()+r);
                                        CanvasList[j].setRotatePoint(x,y);
                                    }
                                }
                                /*ellipse temp;
                                temp=getEllipseInformation(shapeList[i].getInformation());
                                temp.rotate(x,y,r);
                                temp.setColor(shapeList[i].getColor());
                                int cx=temp.getCentralPoint().x();
                                int cy=temp.getCentralPoint().y();
                                int rx=temp.getRadiusX();
                                int ry=temp.getRadiusY();
                                QString tempInformation=QString::number(cx)+" "+QString::number(cy)+" "+QString::number(rx)+" "+QString::number(ry);
                                shapeList[i].setInformation(tempInformation);*/
                                //centralCanvas->saveCanvas();
                               // centralCanvas->drawEllipse(cx,cy,rx,ry);
                                clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
                                drawAllPartern();
                                ellipse temp;
                                temp=getEllipseInformation(shapeList[i].getInformation());
                                temp.rotate(x,y,r);
                                temp.setCentralPoint(r);
                                int cx=temp.getCentralPoint().x();
                                int cy=temp.getCentralPoint().y();
                                int rx=temp.getRadiusX();
                                int ry=temp.getRadiusY();
                                QString tempInformation=QString::number(cx)+" "+QString::number(cy)+" "+QString::number(rx)+" "+QString::number(ry);
                                shapeList[i].setInformation(tempInformation);
                                for (int j=0;j<CanvasList.size();j++){
                                    if (CanvasList[j].getId()==id){
                                        CanvasList[j].setInformation(tempInformation);
                                    }
                                }
                            }
                            if (shapeList[i].getName()=="polygon"){
                                polygon temp;
                                temp=getPolygonInformation(shapeList[i].getInformation());
                                temp.rotate(x,y,r);
                                temp.setColor(shapeList[i].getColor());
                                vector<QPoint> points=temp.getPoints();
                                int n=points.size();
                                QString information;
                                for(int j=0;j<n;j++){
                                    int x,y;
                                    x=points[j].x();
                                    y=points[j].y();
                                    information=information+QString::number(x)+" "+QString::number(y)+" ";
                                }
                                shapeList[i].setInformation(information);
                                for (int j=0;j<CanvasList.size();j++){
                                    if (CanvasList[j].getId()==id){
                                        CanvasList[j].setInformation(information);
                                    }
                                }
                                /*if (shapeList[i].getAlgorithm()=="DDA"){
                                    centralCanvas->saveCanvas();
                                    centralCanvas->drawPolygon_DDA(points);
                                }
                                else if (shapeList[i].getAlgorithm()=="Bresenham"){
                                        centralCanvas->saveCanvas();
                                        centralCanvas->drawPolygon_Bresenham(points);
                                }*/
                                clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
                                drawAllPartern();
                            }
                            if (shapeList[i].getName()=="curve"){
                                curve temp;
                                temp=getCurveInformation(shapeList[i].getInformation());
                                temp.rotate(x,y,r);
                                temp.setColor(shapeList[i].getColor());
                                vector<QPoint> points=temp.getPoints();
                                int n=points.size();
                                QString information;
                                for(int j=0;j<n;j++){
                                    int x,y;
                                    x=points[j].x();
                                    y=points[j].y();
                                    information=information+QString::number(x)+" "+QString::number(y)+" ";
                                }
                                shapeList[i].setInformation(information);
                                for (int j=0;j<CanvasList.size();j++){
                                    if (CanvasList[j].getId()==id){
                                        CanvasList[j].setInformation(information);
                                    }
                                }
                                /*if (shapeList[i].getAlgorithm()=="DDA"){
                                    centralCanvas->saveCanvas();
                                    centralCanvas->drawPolygon_DDA(points);
                                }
                                else if (shapeList[i].getAlgorithm()=="Bresenham"){
                                        centralCanvas->saveCanvas();
                                        centralCanvas->drawPolygon_Bresenham(points);
                                }*/
                                clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
                                drawAllPartern();
                            }
                        }
                    }
                    if (i>shapeList.size()){
                        qDebug()<<"Can not find the id!"<<endl;
                    }
                }
                else{
                    qDebug()<<"The value of Line is out of scope!";
                    return;
                }
            }
            else{
                qDebug()<<"Wrong format of rotate!"<<endl;
            }
            //clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
            //drawAllPartern();
        }
        else if (lineStrList.at(0)=="scale"){
            if (lineStrList.length()==5){
                int id=lineStrList.at(1).toInt();
                int x=lineStrList.at(2).toInt();
                int y=lineStrList.at(3).toInt();
                float s=lineStrList.at(4).toFloat();
                int i;
                if (x>=0&&x<=centralCanvas->getwidth()&&y>=0&&y<=centralCanvas->getheight()){
                    for(i=0;i<shapeList.size();i++){
                        if (shapeList[i].getId()==id){
                            if (shapeList[i].getName()=="line"){
                                line temp;
                                temp=getLineInformation(shapeList[i].getInformation());
                                temp.scale(x,y,s);
                                temp.setColor(shapeList[i].getColor());
                                int x1=temp.getP0().x();
                                int y1=temp.getP0().y();
                                int x2=temp.getPn().x();
                                int y2=temp.getPn().y();
                                QString tempInformation=QString::number(x1)+" "+QString::number(y1)+" "+QString::number(x2)+" "+QString::number(y2);
                                shapeList[i].setInformation(tempInformation);
                                for (int j=0;j<CanvasList.size();j++){
                                    if (CanvasList[j].getId()==id){
                                        CanvasList[j].setInformation(tempInformation);
                                    }
                                }
                                clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
                                drawAllPartern();
                                    /*if (shapeList[i].getAlgorithm()=="DDA"){
                                        centralCanvas->saveCanvas();
                                        centralCanvas->drawLine_DDA(QPoint(x1,y1),QPoint(x2,y2));
                                    }
                                    else if (shapeList[i].getAlgorithm()=="Bresenham"){
                                        centralCanvas->saveCanvas();
                                        centralCanvas->drawLine_Bresenham(QPoint(x1,y1),QPoint(x2,y2));
                                    }*/
                            }
                            if (shapeList[i].getName()=="circle"){
                                circle temp;
                                temp=getCircleInformation(shapeList[i].getInformation());
                                temp.scale(x,y,s);
                                temp.setColor(shapeList[i].getColor());
                                int cx=temp.getCentralPoint().x();
                                int cy=temp.getCentralPoint().y();
                                int rx=temp.getRadius();
                                QString tempInformation=QString::number(cx)+" "+QString::number(cy)+" "+QString::number(cy)+" "+QString::number(rx);
                                shapeList[i].setInformation(tempInformation);
                                for (int j=0;j<CanvasList.size();j++){
                                    if (CanvasList[j].getId()==id){
                                        CanvasList[j].setInformation(tempInformation);
                                    }
                                }
                                //centralCanvas->saveCanvas();
                                //centralCanvas->drawCircle(cx,cy,rx);
                                clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
                                drawAllPartern();
                            }
                            if (shapeList[i].getName()=="ellipse"){
                                ellipse temp;
                                temp=getEllipseInformation(shapeList[i].getInformation());
                                temp.scale(x,y,s);
                                int cx=temp.getCentralPoint().x();
                                int cy=temp.getCentralPoint().y();
                                int rx=temp.getRadiusX();
                                int ry=temp.getRadiusY();
                                QString tempInformation=QString::number(cx)+" "+QString::number(cy)+" "+QString::number(rx)+" "+QString::number(ry);
                                shapeList[i].setInformation(tempInformation);
                                for (int j=0;j<CanvasList.size();j++){
                                    if (CanvasList[j].getId()==id){
                                        CanvasList[j].setInformation(tempInformation);
                                    }
                                }
                                /*ellipse temp;
                                temp=getEllipseInformation(shapeList[i].getInformation());
                                temp.rotate(x,y,r);
                                temp.setColor(shapeList[i].getColor());
                                int cx=temp.getCentralPoint().x();
                                int cy=temp.getCentralPoint().y();
                                int rx=temp.getRadiusX();
                                int ry=temp.getRadiusY();
                                QString tempInformation=QString::number(cx)+" "+QString::number(cy)+" "+QString::number(rx)+" "+QString::number(ry);
                                shapeList[i].setInformation(tempInformation);*/
                                //centralCanvas->saveCanvas();
                               // centralCanvas->drawEllipse(cx,cy,rx,ry);
                                clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
                                drawAllPartern();
                            }
                            if (shapeList[i].getName()=="polygon"){
                                polygon temp;
                                temp=getPolygonInformation(shapeList[i].getInformation());
                                temp.scale(x,y,s);
                                temp.setColor(shapeList[i].getColor());
                                vector<QPoint> points=temp.getPoints();
                                int n=points.size();
                                QString information;
                                for(int j=0;j<n;j++){
                                    int x,y;
                                    x=points[j].x();
                                    y=points[j].y();
                                    information=information+QString::number(x)+" "+QString::number(y)+" ";
                                }
                                shapeList[i].setInformation(information);
                                for (int j=0;j<CanvasList.size();j++){
                                    if (CanvasList[j].getId()==id){
                                        CanvasList[j].setInformation(information);
                                    }
                                }
                                clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
                                drawAllPartern();
                                /*if (shapeList[i].getAlgorithm()=="DDA"){
                                    centralCanvas->saveCanvas();
                                    centralCanvas->drawPolygon_DDA(points);
                                }
                                else if (shapeList[i].getAlgorithm()=="Bresenham"){
                                        centralCanvas->saveCanvas();
                                        centralCanvas->drawPolygon_Bresenham(points);
                                }*/
                            }
                            if (shapeList[i].getName()=="curve"){
                                curve temp;
                                temp=getCurveInformation(shapeList[i].getInformation());
                                temp.scale(x,y,s);
                                temp.setColor(shapeList[i].getColor());
                                vector<QPoint> points=temp.getPoints();
                                int n=points.size();
                                QString information;
                                for(int j=0;j<n;j++){
                                    int x,y;
                                    x=points[j].x();
                                    y=points[j].y();
                                    information=information+QString::number(x)+" "+QString::number(y)+" ";
                                }
                                shapeList[i].setInformation(information);
                                for (int j=0;j<CanvasList.size();j++){
                                    if (CanvasList[j].getId()==id){
                                        CanvasList[j].setInformation(information);
                                    }
                                }
                                clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
                                drawAllPartern();
                                /*if (shapeList[i].getAlgorithm()=="DDA"){
                                    centralCanvas->saveCanvas();
                                    centralCanvas->drawPolygon_DDA(points);
                                }
                                else if (shapeList[i].getAlgorithm()=="Bresenham"){
                                        centralCanvas->saveCanvas();
                                        centralCanvas->drawPolygon_Bresenham(points);
                                }*/
                            }
                        }
                    }
                    if (i>shapeList.size()){
                        qDebug()<<"Can not find the id!"<<endl;
                    }
                }
                else{
                    qDebug()<<"The value of Line is out of scope!";
                    return;
                }
            }
            else{
                qDebug()<<"Wrong format of scale!"<<endl;
            }
            //clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
            //drawAllPartern();
        }
        else if (lineStrList.at(0)=="clip"){
            if (lineStrList.length()==7){
                int id=lineStrList.at(1).toInt();
                int x1=lineStrList.at(2).toInt();
                int y1=lineStrList.at(3).toInt();
                int x2=lineStrList.at(4).toInt();
                int y2=lineStrList.at(5).toInt();
                QString algorithm=lineStrList.at(6);
                int i;
                if (x1>=0&&x1<=centralCanvas->getwidth()&&y1>=0&&y1<=centralCanvas->getheight()&&x2>=0&&x2<=centralCanvas->getwidth()&&y2>=0&&y2<=centralCanvas->getheight()){
                    for(i=0;i<shapeList.size();i++){
                        if (shapeList[i].getId()==id){
                            if (shapeList[i].getName()=="line"){
                                if (algorithm=="Cohen-Sutherland"){
                                    line temp;
                                    temp=getLineInformation(shapeList[i].getInformation());
                                    temp.clip_Cohen_Sutherland(x1,y1,x2,y2);
                                    temp.setColor(shapeList[i].getColor());
                                    int xx1=temp.getP0().x();
                                    int yy1=temp.getP0().y();
                                    int xx2=temp.getPn().x();
                                    int yy2=temp.getPn().y();
                                    QString tempInformation=QString::number(xx1)+" "+QString::number(yy1)+" "+QString::number(xx2)+" "+QString::number(yy2);
                                    shapeList[i].setInformation(tempInformation);
                                    for (int j=0;j<CanvasList.size();j++){
                                        if (CanvasList[j].getId()==id){
                                            CanvasList[j].setInformation(tempInformation);
                                        }
                                    }
                                    clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
                                    drawAllPartern();
                                        /*if (shapeList[i].getAlgorithm()=="DDA"){
                                            centralCanvas->saveCanvas();
                                            centralCanvas->drawLine_DDA(QPoint(x1,y1),QPoint(x2,y2));
                                        }
                                        else if (shapeList[i].getAlgorithm()=="Bresenham"){
                                            centralCanvas->saveCanvas();
                                            centralCanvas->drawLine_Bresenham(QPoint(x1,y1),QPoint(x2,y2));
                                        }*/
                                }
                                else if (algorithm=="Liang-Barsky"){
                                    line temp;
                                    temp=getLineInformation(shapeList[i].getInformation());
                                    temp.clip_Liang_Barsky(x1,y1,x2,y2);
                                    temp.setColor(shapeList[i].getColor());
                                    int xx1=temp.getP0().x();
                                    int yy1=temp.getP0().y();
                                    int xx2=temp.getPn().x();
                                    int yy2=temp.getPn().y();
                                    QString tempInformation=QString::number(xx1)+" "+QString::number(yy1)+" "+QString::number(xx2)+" "+QString::number(yy2);
                                    shapeList[i].setInformation(tempInformation);
                                    for (int j=0;j<CanvasList.size();j++){
                                        if (CanvasList[j].getId()==id){
                                            CanvasList[j].setInformation(tempInformation);
                                        }
                                    }
                                    clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
                                    drawAllPartern();
                                        /*if (shapeList[i].getAlgorithm()=="DDA"){
                                            centralCanvas->saveCanvas();
                                            centralCanvas->drawLine_DDA(QPoint(x1,y1),QPoint(x2,y2));
                                        }
                                        else if (shapeList[i].getAlgorithm()=="Bresenham"){
                                            centralCanvas->saveCanvas();
                                            centralCanvas->drawLine_Bresenham(QPoint(x1,y1),QPoint(x2,y2));
                                        }*/
                                }
                            }
                            else{
                                qDebug()<<"clip can just be applied to line!"<<endl;
                            }
                    }
                    }
                    if (i>shapeList.size()){
                        qDebug()<<"Can not find the id!"<<endl;
                    }
                }
                else{
                    qDebug()<<"The value of Line is out of scope!";
                    return;
                }
            }
            else{
                qDebug()<<"Wrong format of clip!"<<endl;
            }
            //clearCanvas(centralCanvas->getwidth(),centralCanvas->getheight());
            //drawAllPartern();
        }else{
            qDebug()<<"Unknown instructions!"<<endl;
        }
    }
    f.close();
}

void MainWindow::clearCanvas(){
    centralCanvas->clear();
}

void MainWindow::clearCanvas(int width,int height){
    centralCanvas->clear(width,height);
}

void MainWindow::setColor(int R,int G,int B){
    readColorR=R;
    readColorG=G;
    readColorB=B;
    QColor color;
    color.setRgb(R,G,B);
    centralCanvas->setColor(color);
}

void MainWindow::rubberErase(){
    centralCanvas->setCurrentAction(RUBBER);
}

void MainWindow::withdrawAction(){
    centralCanvas->withdrawAction();
}

void MainWindow::aboutApp(){
    QMessageBox::about(NULL,"About","programmed by HuangJiaying\n Email:951493085@qq.com");

}

void MainWindow::chooseColor(){
    QColorDialog colorDialog;
    QColor color=colorDialog.getColor();
    centralCanvas->setColor(color);
}

void MainWindow::drawCircle(){
    centralCanvas->setCurrentAction(CIRCLE);
    //setCursor(QCursor(Qt::CrossCursor));
}

void MainWindow::drawLine(){
    centralCanvas->setCurrentAction(LINE);
}

void MainWindow::drawEllipse(){
    centralCanvas->setCurrentAction(ELLIPSE);
}

void MainWindow::pencildraw(){
    centralCanvas->setCurrentAction(PENCIL);
}

void MainWindow::drawPolygon(){
    centralCanvas->setCurrentAction(POLYGON);
}

void MainWindow::drawCurve(){
    centralCanvas->setCurrentAction(CURVE);
}

class circle MainWindow::getCircleInformation(QString information){
    QStringList lineStrList=information.split(" ");
    int cx=lineStrList.at(0).toInt();
    int cy=lineStrList.at(1).toInt();
    int rx=lineStrList.at(2).toInt();
    circle res;
    res.setInformation(cx,cy,rx);
    return res;
}

class line MainWindow::getLineInformation(QString information){
    QStringList lineStrList=information.split(" ");
    int x1=lineStrList.at(0).toInt();
    int y1=lineStrList.at(1).toInt();
    int x2=lineStrList.at(2).toInt();
    int y2=lineStrList.at(3).toInt();
    line res;
    res.setInformation(x1,x2,y1,y2);
    return res;
}

class ellipse MainWindow::getEllipseInformation(QString information){
    QStringList lineStrList=information.split(" ");
    int cx=lineStrList.at(0).toInt();
    int cy=lineStrList.at(1).toInt();
    int rx=lineStrList.at(2).toInt();
    int ry=lineStrList.at(3).toInt();
    ellipse res;
    res.setInformation(cx,cy,rx,ry);
    return res;
}

class polygon MainWindow::getPolygonInformation(QString information){
    QStringList lineStrList=information.split(" ");
    int n=lineStrList.size()/2;
    vector<QPoint>points;
    for(int i=0;i<n;i++){
        QPoint temp;
        int x,y;
        x=lineStrList[2*i].toInt();
        y=lineStrList[2*i+1].toInt();
        temp.setX(x);
        temp.setY(y);
        points.push_back(temp);
    }
    polygon res;
    res.setInformation(points);
    return res;
}

class curve MainWindow::getCurveInformation(QString information){
    QStringList lineStrList=information.split(" ");
    int n=lineStrList.size()/2;
    vector<QPoint>points;
    for(int i=0;i<n;i++){
        QPoint temp;
        int x,y;
        x=lineStrList[2*i].toInt();
        y=lineStrList[2*i+1].toInt();
        temp.setX(x);
        temp.setY(y);
        points.push_back(temp);
    }
    curve res;
    res.setInformation(points);
    return res;
}

void MainWindow::setWidthThin(){
    centralCanvas->setWidthThin();
}

void MainWindow::setWidthMedium(){
    centralCanvas->setWidthMedium();
}

void MainWindow::setWidthThick(){
    centralCanvas->setWidthThick();
}

void MainWindow::drawAllPartern(){
    for (int i=0;i<CanvasList.size();i++){
        QColor *tempColor=new QColor(CanvasList[i].getColor());
        if (CanvasList[i].getName()=="line"){
            line temp;
            temp=getLineInformation(CanvasList[i].getInformation());
            if (CanvasList[i].getAlgorithm()=="DDA"){
                centralCanvas->saveCanvas();
                centralCanvas->drawLine_DDA(temp.getP0(),temp.getPn(),tempColor);
            }
            else if (CanvasList[i].getAlgorithm()=="Bresenham"){
                 centralCanvas->saveCanvas();
                 centralCanvas->drawLine_Bresenham(temp.getP0(),temp.getPn(),tempColor);
            }
        }
        if (CanvasList[i].getName()=="cirlce"){
            circle temp;
            temp=getCircleInformation(CanvasList[i].getInformation());
            centralCanvas->saveCanvas();
            centralCanvas->drawCircle(temp.getCentralPoint().x(),temp.getCentralPoint().y(),temp.getRadius(),tempColor);
        }
        if (CanvasList[i].getName()=="ellipse"){
            ellipse temp;
            temp=getEllipseInformation(CanvasList[i].getInformation());
            centralCanvas->saveCanvas();
            centralCanvas->drawEllipse(temp.getCentralPoint().x(),temp.getCentralPoint().y(),temp.getRadiusX(),temp.getRadiusY(),shapeList[i].getAngle(),shapeList[i].getRotatePoint(),tempColor);
        }
        if (CanvasList[i].getName()=="polygon"){
            polygon temp;
            temp=getPolygonInformation(CanvasList[i].getInformation());
            if (CanvasList[i].getAlgorithm()=="DDA"){
                centralCanvas->saveCanvas();
                centralCanvas->drawPolygon_DDA(temp.getPoints(),tempColor);
            }
            else if (CanvasList[i].getAlgorithm()=="Bresenham"){
                 centralCanvas->saveCanvas();
                 centralCanvas->drawPolygon_Bresenham(temp.getPoints(),tempColor);
            }
        }
        if (CanvasList[i].getName()=="curve"){
            curve temp;
            temp=getCurveInformation(CanvasList[i].getInformation());
            if (CanvasList[i].getAlgorithm()=="Bezier"){
                centralCanvas->saveCanvas();
                centralCanvas->drawCurve_Bezier(temp.getPoints(),tempColor);
            }
            else if (CanvasList[i].getAlgorithm()=="B-spline"){
                 centralCanvas->saveCanvas();
                 centralCanvas->drawCurve_Bspline(temp.getPoints(),tempColor);
            }
        }
    }
}

void MainWindow::translateAction(){
    centralCanvas->translateAction();
}

void MainWindow::clipAction(){
    centralCanvas->clipAction();
}

void MainWindow::rotateAction(){
    centralCanvas->rotateAction();
}

void MainWindow::scaleAction(){
    centralCanvas->scaleAction();
}

void MainWindow::canvasClip(){
    centralCanvas->setCurrentAction(CLIP);
}
