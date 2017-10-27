#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  max = 0;
  min = 0;


  /*
  connect(ui->horizontalSliderVeloc,
          SIGNAL(valueChanged(int)),
          ui->widgetPlotter,
          SLOT(mudaVelocidade(int)));
  */

   connect ( ui->horizontalSlider_max,SIGNAL(valueChanged(int)),SLOT(getMax(int) ));
   connect ( ui->horizontalSlider_min,SIGNAL(valueChanged(int)),SLOT(getMin(int) ));



 // tcpConnect();


}

void MainWindow::tcpConnect(){
  socket->connectToHost("127.0.0.1",1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }

}

void MainWindow::getData(){
  QString str;
  QByteArray array;
  QStringList list;
  QDateTime datetime;
  qDebug() << "to get data...";
  if(socket->state() == QAbstractSocket::ConnectedState){
    if(socket->isOpen()){
      qDebug() << "reading...";
      socket->write("get 127.0.0.1\r\n");
      socket->waitForBytesWritten();
      socket->waitForReadyRead();
      qDebug() << socket->bytesAvailable();
      while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        list = str.split(" ");
        if(list.size() == 2){
          datetime.fromString(list.at(0),Qt::ISODate);
          str = list.at(1);
          qDebug() << datetime << ": " << str;
        }
      }
    }
  }
}


MainWindow::~MainWindow()
{
  delete socket;
    delete ui;
}

int MainWindow::randNumber()
{



  srand(time(0));

  qDebug() << "rand value: " << rand() % max +  min;

  return  rand() % max  + min;




}

void MainWindow::getMax(int _max )
{
     qDebug() << "max= "<< _max;

     max = _max;
}

void MainWindow::getMin(int _min)
{
    qDebug() << "min= "<< _min;

    min = _min;
}
