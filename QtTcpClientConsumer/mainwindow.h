#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <cstdlib>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT


public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  int randNumber();

  
signals:



public slots:
  void tcpConnect();
  void getData();
  void getMax(int _max);
  void  getMin(int _min);
private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  int max;
  int min;
};

#endif // MAINWINDOW_H
