#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>

int c=0,t=0;
bool ok,fbl,geshi;
QRect labelrec;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   timer=new QTimer(this);
   connect(timer,SIGNAL(timeout()),this,SLOT(readframe()));
   connect(pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
   connect(pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
}

void MainWindow::readframe()
{

    capture >> frame;
    if(c==0)
    {
        c=1;
            cout<< capture.get(CAP_PROP_FPS);
            cout<<ok;
            cout<<geshi;
          //  cout<<fbl;
             cout<< capture.get(CAP_PROP_FRAME_WIDTH);
              cout<< capture.get(CAP_PROP_FRAME_HEIGHT);

    }
    //cvtColor(frame,frame,COLOR_BGR2RGB);
    QImage image((const uchar*)frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);  
    ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::opencamera()
{ 
    timer->start(1000/60);
}
void MainWindow::on_pushButton_clicked()
{

   capture.open("/dev/video0");
   geshi= capture.set(CAP_PROP_FOURCC,CAP_OPENCV_MJPEG);
   ok=capture.set(CAP_PROP_FPS,60);
   opencamera();
   ui->pushButton->setEnabled(false);
   ui->pushButton_2->setEnabled(true);
}
void MainWindow::on_pushButton_2_clicked()
{   timer->stop();
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
}
MainWindow:: ~MainWindow()
{
capture.release();
    delete ui;
}

