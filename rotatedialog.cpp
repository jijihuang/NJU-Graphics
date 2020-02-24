#include "rotatedialog.h"
#include "ui_rotatedialog.h"

rotateDialog::rotateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rotateDialog)
{
    ui->setupUi(this);
}

rotateDialog::~rotateDialog()
{
    delete ui;
}

int rotateDialog::getX(){
    return ui->spinBoxX->value();
}

int rotateDialog::getY(){
    return ui->spinBoxY->value();
}

int rotateDialog::getR(){
    return ui->spinBoxR->value();
}

void rotateDialog::setXY(QPoint p){
    ui->spinBoxX->setValue(p.x());
    ui->spinBoxY->setValue(p.y());
}
