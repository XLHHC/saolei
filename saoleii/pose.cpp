#include "pose.h"
#include "ui_pose.h"
#include "newmain.h"
#include "ui_newmain.h"
#include<QPushButton>
#include<QMessageBox>
#include<QMediaPlayer>
#include<QPainter>
#include <QSound>
#include "mainwindow.h"
pose::pose(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pose)
{
    ui->setupUi(this);
    //设置子窗口的名字
    setWindowTitle("暂停");
    //设置子窗口的大小
    setMinimumSize(350, 150);
    setMaximumSize(350, 150);
    connect(ui->horizontalSlider_2,SIGNAL(QSlider::valueChanged(int)),this,SLOT(on_horizontalSlider_2_valueChanged()));
}

pose::~pose()
{
    delete ui;
}

void pose::paintEvent(QPaintEvent *)
{
    QPainter p(this); //创建画家对象
    p.drawPixmap(this->rect(),QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/pose.JPG")); //画背景图
}
void pose::on_horizontalSlider_2_valueChanged(int value)
{
    m_mediaplayer.setVolume(value);
}

void pose::on_pushButton_3_clicked()
{
    this->hide();
    bola=true;
    QMessageBox::about(this,"提示","再点一下左上角的“继续”哦！");//弹窗设置

}

void pose::on_pushButton_clicked()
{
   this->hide();
    bolb=true;
    QMessageBox::about(this,"提示","再点一下左上角的“继续”哦！");//弹窗设置
}

void pose::on_returnstart_clicked()
{
    this->hide();
    bol=true;
    QMessageBox::about(this,"提示","再点一下左上角的“继续”哦！");//弹窗设置
}
