#include "translatedialog.h"
#include "ui_translatedialog.h"

TranslateDialog::TranslateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TranslateDialog)
{
    ui->setupUi(this);
}

TranslateDialog::~TranslateDialog()
{
    delete ui;
}

int TranslateDialog::getX(){
    return ui->spinBoxX->value();
}

int TranslateDialog::getY(){
    return ui->spinBoxY->value();
}
