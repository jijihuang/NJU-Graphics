#ifndef SCALEDIALOG_H
#define SCALEDIALOG_H

#include <QDialog>

namespace Ui {
class ScaleDialog;
}

class ScaleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScaleDialog(QWidget *parent = nullptr);
    ~ScaleDialog();
    int getX();
    int getY();
    double getS();
    void setXY(QPoint p);

private:
    Ui::ScaleDialog *ui;
};

#endif // SCALEDIALOG_H
