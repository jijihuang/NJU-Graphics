#ifndef CANVAS_H
#define CANVAS_H


#include <QWidget>
#include <QImage>
#include <QColor>
#include <QPen>
#include <QPoint>
#include <QPixmap>
#include <QPushButton>
#include <QPainter>
#include <QString>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QTimer>
#include <QRectF>
#include <vector>
#include <QInputDialog>
#include <QDialog>
#include <QFormLayout>
#include "drawaction.h"
#include "shape.h"
#include "circle.h"
#include "ellipse.h"
#include "line.h"
#include "polygon.h"
#include "curve.h"
#include "translatedialog.h"
#include "rotatedialog.h"
#include "scaledialog.h"
#include "clipdialog.h"
using namespace std;

#define CANVAS_WIDTH 1152
#define CANVAS_HEIGHT 648


namespace Ui {
class canvas;
}

class canvas : public QWidget
{
    Q_OBJECT

public:
    explicit canvas(QWidget *parent = nullptr);
    ~canvas();
    void paintEvent(QPaintEvent *event);
    void load(QString imagePath);
    void load(QImage *loadImage);
    void save(QString imagePath);
    void clear();
    void clear(int width,int height);
    void setCurrentAction(DRAWACTION action);
    void setColor(QColor& chooseColor);
    int getwidth();
    int getheight();
    QColor getColor();
    void saveCanvas();
    void canvasClip(QImage *image, QPoint a,QPoint b);
    void enterEvent(QEvent *event)override;//鼠标移入
    void leaveEvent(QEvent *event)override;//鼠标移出
    void mouseMoveEvent(QMouseEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void drawLine_DDA(QPoint x1,QPoint x2,QColor *color);
    void drawLine_Bresenham(QPoint x1,QPoint x2,QColor *color);
    void drawCircle(int cx,int cy,int r,QColor *color);
    void drawEllipse(int cx,int cy,int rx,int ry,int angle,QPoint rotatePoint,QColor *color);
    void drawPolygon_DDA(vector<QPoint> points,QColor *color);
    void drawPolygon_Bresenham(vector<QPoint> points,QColor *color);
    void drawCurve_Bezier(vector<QPoint> points,QColor *color);
    void drawCurve_Bspline(vector<QPoint> points,QColor *color);
    void rubberErase(QRectF &rect,QImage *image, QColor *color);
    void setWidthThin();
    void setWidthMedium();
    void setWidthThick();
    void withdrawAction();
    void translateAction();
    void clipAction();
    void scaleAction();
    void rotateAction();
private:
    Ui::canvas *ui;
    QPalette palette;
    QImage *image;
    QImage *whiteBackground;
    QImage *withdrawBackground;
    QImage *background;
    QColor *penColor;
    QPen *pen;
    int rubberWidth;
    QColor *rubberColor;
    int penWidth;
    int width;
    int height;
    DRAWACTION currentAction;
    QPoint start;
    QPoint end;
    QPoint canvasClipA;
    QPoint canvasClipB;
    QPen rectPen;
    shape *current;
    QPixmap *pixmap;
    vector<QPoint> points;
    vector<QPoint> curvePoints;
    int currentNode;
};

#endif // CANVAS_H
