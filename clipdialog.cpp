#include "clipdialog.h"
#include "ui_clipdialog.h"

ClipDialog::ClipDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClipDialog)
{
    ui->setupUi(this);
}

ClipDialog::~ClipDialog()
{
    delete ui;
}

int ClipDialog::getX1(){
    return ui->spinBoxX1->value();
}

int ClipDialog::getX2(){
    return ui->spinBoxX2->value();
}

int ClipDialog::getY1(){
    return ui->spinBoxY1->value();
}

int ClipDialog::getY2(){
    return ui->spinBoxY2->value();
}
