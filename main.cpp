#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <QTextStream>
#include <QDir>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTextStream cout(stdout);
    if(argc==1){
      //cout<<argv[0]<<endl;
      //QApplication a(argc, argv);
      //MainWindow w;
      a.quit();
      w.show();
      return a.exec();
    }
    else if (argc==3){
        QString filepath=QString(QLatin1String(argv[1]));
        QString savedir=QString(QLatin1String(argv[2]));
        w.readFile(filepath,savedir);
        return 0;
    }
}
