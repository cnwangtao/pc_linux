#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>

int c=0;
bool cam_ok,s;
QFont ft;
QList<QSerialPortInfo> IN_c;
QString a_read;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   timer=new QTimer(this);
   ft.setPointSize(12);
   connect(timer,SIGNAL(timeout()),this,SLOT(readframe()));
   connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
   connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
   connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()),Qt::UniqueConnection);
   connect(&serial,SIGNAL(readyRead()),this,SLOT(serialread()));
   connect(ui->comboBox,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(on_comboBox_currentIndexChanged(const QString&)));
   initserialport();
   cam_ok=capture.open("/dev/video0");
      if(cam_ok==1)
   {
   capture.set(CAP_PROP_FOURCC,CAP_OPENCV_MJPEG);
   capture.set(CAP_PROP_FPS,60);
   ui->pushButton->setEnabled(false);
   ui->label_2->setText("cam_is_opened");
   ui->label_2->setFont(ft);
   freshcamera();
   }
      else{ ui->label_2->setText("cam_not_open");
             ui->label_2->setFont(ft);}
}

void MainWindow::readframe()
{
if(capture.isOpened())
 {
    capture >> frame;
    if(c==0)
    {
        c=1;
    }
    cvtColor(frame,frame,COLOR_BGR2RGB);
    QImage image((const uchar*)frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image));
 }
else{   ui->pushButton->setEnabled(true);
        ui->label_2->setText("cam_not_open");
        ui->label_2->setFont(ft);
    }
}

void MainWindow::freshcamera()
{
    timer->start(1000/60);
}

void MainWindow::on_pushButton_clicked()//open camera
{
    cam_ok=capture.open("/dev/video0");
       if(cam_ok==1)
    {
    capture.set(CAP_PROP_FOURCC,CAP_OPENCV_MJPEG);
    capture.set(CAP_PROP_FPS,60);
    ui->pushButton->setEnabled(false);
    ui->label_2->setText("cam_is_opened");
    ui->label_2->setFont(ft);
    freshcamera();
    }
       else{ ui->label_2->setText("cam_not_open");
              ui->label_2->setFont(ft);}

}
void MainWindow::on_comboBox_currentIndexChanged(const QString &)
{
   const QString arg1=ui->comboBox->currentText();
    QSerialPortInfo info;
    QList<QSerialPortInfo> infos=QSerialPortInfo::availablePorts();
    int i=0;
    foreach (info, infos)
    {
       if(info.portName()==arg1) break;
       i++;
    }
    if(i!=infos.size())
    {
        ui->pushButton_3->setText("open_serialport");
        serial.close();
        serial.setPort(info);
        serial.setBaudRate(QSerialPort::Baud9600);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
    }else
    {
        serial.close();
        ui->pushButton_3->setText("choose_serialport");
    }
}
void MainWindow::initserialport()
{
    IN_c=QSerialPortInfo::availablePorts();
    if(IN_c.isEmpty())
    {
        return;
    }
    ui->comboBox->addItem("choose_serialport");
    foreach(QSerialPortInfo info,IN_c)
    {
        ui->comboBox->addItem(info.portName());
    }
}
void MainWindow::on_pushButton_2_clicked()//saomiao serialport
{
QList<QSerialPortInfo> infos=QSerialPortInfo::availablePorts();
ui->pushButton_3->setText("open_serialport");
if(infos.isEmpty())
{ ui->comboBox->clear();
     ui->comboBox->addItem("choose_serialport");
}
else
    {
     ui->comboBox->clear();
     ui->comboBox->addItem("choose_serialport");
     foreach (QSerialPortInfo info,infos )
      {
        ui->comboBox->addItem(info.portName());
      }
    }
}
void MainWindow::serialread()
{
    a_read=serial.readAll();
}
void MainWindow::on_pushButton_3_clicked()
{
       s=serial.open(QIODevice::ReadWrite);
        cout<<s;
   if(s)
   {
     ui->pushButton_3->setText("opened_yes");
    }
   else {ui->pushButton_3->setText("opened_no");}
}

MainWindow:: ~MainWindow()
{
capture.release();
    delete ui;
}

