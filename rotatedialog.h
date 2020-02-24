#ifndef ROTATEDIALOG_H
#define ROTATEDIALOG_H

#include <QDialog>
#include <QPoint>
namespace Ui {
class rotateDialog;
}

class rotateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit rotateDialog(QWidget *parent = nullptr);
    ~rotateDialog();
    int getX();
    int getY();
    int getR();
    void setXY(QPoint p);

private:
    Ui::rotateDialog *ui;
};

#endif // ROTATEDIALOG_H
