#include "scaledialog.h"
#include "ui_scaledialog.h"

ScaleDialog::ScaleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScaleDialog)
{
    ui->setupUi(this);
}

ScaleDialog::~ScaleDialog()
{
    delete ui;
}

int ScaleDialog::getX(){
    return ui->spinBoxX->value();
}

int ScaleDialog::getY(){
    return ui->spinBoxY->value();
}

double ScaleDialog::getS(){
    return ui->doubleSpinBoxS->value();
}

void ScaleDialog::setXY(QPoint p){
    ui->spinBoxX->setValue(p.x());
    ui->spinBoxY->setValue(p.y());
}
