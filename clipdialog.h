#ifndef CLIPDIALOG_H
#define CLIPDIALOG_H

#include <QDialog>

namespace Ui {
class ClipDialog;
}

class ClipDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClipDialog(QWidget *parent = nullptr);
    ~ClipDialog();
    int getX1();
    int getX2();
    int getY1();
    int getY2();

private:
    Ui::ClipDialog *ui;
};

#endif // CLIPDIALOG_H
