#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//opencv
#include<opencv2/imgproc/imgproc_c.h>
#include<opencv2/highgui/highgui_c.h>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core_c.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/highgui.hpp"
#include<iostream>
#include<math.h>
#include<vector>
//qt
#include <QMainWindow>
#include<QLabel>
#include<QPushButton>
#include<QTimer>
#include<QComboBox>
#include<QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
namespace Ui {
class MainWindow;
}
using namespace cv;
using namespace std;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
void freshcamera();
void readframe();
void on_pushButton_clicked();//cam
void on_pushButton_2_clicked();//serial
void on_pushButton_3_clicked();//serial
void serialread();
void on_comboBox_currentIndexChanged(const QString&);
private:
    Ui::MainWindow *ui;
    QSerialPort serial;
    void initserialport();
    VideoCapture capture;
    QTimer *timer;
    Mat frame;
};

#endif // MAINWINDOW_H
