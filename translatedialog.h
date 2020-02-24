#ifndef TRANSLATEDIALOG_H
#define TRANSLATEDIALOG_H

#include <QDialog>

namespace Ui {
class TranslateDialog;
}

class TranslateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TranslateDialog(QWidget *parent = nullptr);
    ~TranslateDialog();
    int getX();
    int getY();

private:
    Ui::TranslateDialog *ui;
};

#endif // TRANSLATEDIALOG_H
