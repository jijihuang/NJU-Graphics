#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QDebug>
#include <QFileDialog>
#include <QToolBar>
#include <QVBoxLayout>
#include <QAction>
#include <QColorDialog>
#include <QColor>
#include <QActionGroup>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QLabel>
#include <vector>
#include <QMouseEvent>
#include <QMessageBox>
#include "canvas.h"
#include "drawaction.h"
#include "shape.h"
#include "line.h"
#include "circle.h"
#include "ellipse.h"
#include "curve.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void readFile(QString filePath,QString saveDir);
    void saveFile(QString imagePath,QString saveDir);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QToolBar *toolBar;
    canvas *centralCanvas;
    QAction *color;
    QAction *pencil;
    QAction *rubber;
    QAction *setWidth;
    QMenu *setWidthMenu;
    QAction *widthThin;
    QAction *widthMeduim;
    QAction *widthThick;
    QAction *circleAction;
    QAction *lineAction;
    QAction *ellipseAction;
    QAction *polygonAction;
    QAction *curveAction;
    QAction *clipCanvasAction;
    QActionGroup *toolGroup;
    vector<shape> shapeList;
    vector<shape> CanvasList;
    int readColorR;
    int readColorG;
    int readColorB;
private slots:
    void createNew();
    void openFile();
    void readFile();
    void saveFile();
    void clearCanvas();
    void clearCanvas(int width,int height);
    void setColor(int R,int G,int B);
    void withdrawAction();
    void translateAction();
    void rotateAction();
    void clipAction();
    void scaleAction();
    void aboutApp();
    void chooseColor();
    void drawCircle();
    void drawLine();
    void drawEllipse();
    void drawPolygon();
    void drawCurve();
    void rubberErase();
    void canvasClip();
    circle getCircleInformation(QString information);
    line getLineInformation(QString information);
    ellipse getEllipseInformation(QString information);
    polygon getPolygonInformation(QString information);
    curve getCurveInformation(QString information);
    void setWidthThin();
    void setWidthMedium();
    void setWidthThick();
    void pencildraw();
    void drawAllPartern();
};

#endif // MAINWINDOW_H
