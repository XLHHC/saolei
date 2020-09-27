#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include<QMessageBox>
#include<QPainter>
#include <QMediaPlayer>
#include"newmain.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置主窗口的大小
    setMinimumSize(500, 800);
    //minimum和maximum是设置窗口大小不可变
    setMaximumSize(500, 800);
    setWindowTitle("游戏");

    PushStart.setText("进入游戏");
    PushStart.setParent(this);
    PushStart.move(150,470);
    PushStart.resize(180,40);

    PushRule.setText("游戏规则");
    PushRule.setParent(this);
    PushRule.move(150,550);
    PushRule.resize(180,40);

    notice=new QLabel(this);
    //设置外观
    notice->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    notice->setAlignment(Qt::AlignBottom|Qt::AlignRight);
    //设置大小和位置
    notice->setGeometry(QRect(10,20,400,100));
    //设置label_notice大小根据文本改变
    notice->adjustSize();

    connect(&PushStart,&QPushButton::clicked,this,&MainWindow::play);
    //connect(&w,&formwindow::mysignal,this,&MainWindow::receive);
    connect(&PushRule,&QPushButton::clicked,
            [=]()
    {
        QMessageBox::about(this,"游戏规则","根据提示的数字，判断雷的位置，显示的数字表示周围八个格子内雷的个数，无数字显示则表示周围八个格子中无雷，在判断有雷的位置插旗，并翻开无雷的格子");//弹窗设置
    });

    //设置字体
    QFont ft;
    //设置字体大小
    ft.setPointSize(20);

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::play(){
    w=new newmain;
   // this->hide(); //隐藏主窗口
    w->show();     //弹出子窗口

}

void MainWindow::receive()
{
    w->hide();//隐藏子窗口
    this->show();  //弹出主窗口
}

void MainWindow::paintEvent(QPaintEvent *)
{
    //创建画家对象
    QPainter p(this);
    p.drawPixmap(this->rect(),QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/i.JPG")); //画背景图
}


