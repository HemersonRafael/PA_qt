#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QString>
#include <QTextBrowser>
#include <QTimer>
#include<QTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          SLOT(tcpConnect()));

  connect(ui->pushButtonDisconnect,
          SIGNAL(clicked(bool)),
          SLOT(tcpDisconnect()));

  connect(ui->pushButtonConnectStart,
          SIGNAL(clicked(bool)),
          this,
          SLOT(startTime()));
  connect(ui->pushButtonConnectStop,
          SIGNAL(clicked(bool)),
          this,
          SLOT(stopTime()));

}

void MainWindow::tcpConnect(){
  socket->connectToHost(ui->lineEditIp->text(),1234);
  if(socket->state() == QAbstractSocket::ConnectedState ||socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}

void MainWindow::tcpDisconnect()
{
    socket->disconnectFromHost();

    if(socket->state() == QAbstractSocket::UnconnectedState ||
            socket->waitForDisconnected(3000)){
      qDebug() << "Disconnected";
    }


}

void MainWindow::startTime()
{
    timer = startTimer(ui->horizontalSliderTiming->value()*1000);
}

void MainWindow::stopTime()
{
    killTimer(timer);
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    putData();

}

void MainWindow::putData(){
  QDateTime datetime;
  QString str;
  qint64 msecdate;


  if(socket->state()== QAbstractSocket::ConnectedState){

    msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
    str = "set "+ QString::number(msecdate) + " " + QString::number(qrand()%ui->horizontalSliderMax->value()+ui->horizontalSliderMin->value())+"\r\n";

      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
      ui->textBrowser->append(str);
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "wrote";
      }
  }

}

MainWindow::~MainWindow(){
  delete socket;
    delete ui;
}



void MainWindow::on_actionQuit_triggered()
{
    close();
}
