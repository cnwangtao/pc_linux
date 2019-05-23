#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>

int c=0;bool ok;bool fbl;bool geshi;
QRect labelrec;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   timer=new QTimer(this);
   capture.open("/dev/video0");
   geshi= capture.set(CAP_PROP_FOURCC,CAP_OPENCV_MJPEG);
     ok=capture.set(CAP_PROP_FPS,60);
   connect(timer,SIGNAL(timeout()),this,SLOT(readframe()));
   opencamera();

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
    ui->label->resize(ui->label->width(),ui->label->height());
    ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::opencamera()
{
    timer->start(1000/60);

}

MainWindow:: ~MainWindow()
{
capture.release();
    delete ui;
}

