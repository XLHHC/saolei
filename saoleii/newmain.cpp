#include "newmain.h"
#include "ui_newmain.h"
#include<QPushButton>
#include<QMessageBox>
#include<QPainter>
#include <QMediaPlayer>
#include<QPainter>
#include<QPen>
#include<QBrush>
#include<QTime>
#include<QTimer>
#include<QDebug>
#include <QString>
#include<QMouseEvent>
#include <QLabel>
#include<QSound>
#include <QTimerEvent>
#include "mainwindow.h"

//初始化棋盘数据
void newmain::setlei(){
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            lei[i][j]=0;
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            num[i][j]=0;
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            dianji[i][j]=0;
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            chaqi[i][j]=0;
}

newmain::newmain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::newmain)
{

    ui->setupUi(this);
    //设置子窗口的名字
    setWindowTitle("扫雷");
    //设置子窗口的大小
    setMinimumSize(600, 850);
    //用maximum和minimum是固定窗口大小
    setMaximumSize(600, 850);

    Pushpos.setText("暂停");
    Pushpos.setParent(this);
    Pushpos.resize(100,50);
    Pushpos.move(10,10);
    connect(&Pushpos,&QPushButton::clicked,this,&newmain::poschange);

    Pushsound.setText("更换音乐");
    Pushsound.setParent(this);
    Pushsound.resize(100,50);
    Pushsound.move(10,60);
    //改变音乐
    connect(&Pushsound,&QPushButton::clicked,this,&newmain::soundchange);

    //设置背景音乐
    sound1 = new QMediaPlayer(this);
    sound1->setMedia(QUrl::fromLocalFile("C:/Users/lenovo/Desktop/tdks/saoleii/sound/music1.wav"));
    sound1->setVolume(30);

    //设置背景音乐
    sound2 = new QMediaPlayer(this);
    sound2->setMedia(QUrl::fromLocalFile("C:/Users/lenovo/Desktop/tdks/saoleii/sound/music2.wav"));
    sound2->play();
    sound2->setVolume(30);

   //设置三个选择按钮的名字，大小，位置
    c1.setParent(this);
    c2.setParent(this);
    c3.setParent(this);

    c1.setText("简单模式");
    c2.setText("一般模式");
    c3.setText("困难模式");

    c1.setGeometry(50,150,130,50);
    c2.setGeometry(235,150,130,50);
    c3.setGeometry(420,150,130,50);

    connect(&c1,&QPushButton::pressed,this,&newmain:: modelE);
    connect(&c2,&QPushButton::pressed,this,&newmain:: modelM);
    connect(&c3,&QPushButton::pressed,this,&newmain:: modelH);

    a1.setParent(this);
    a2.setParent(this);
    a3.setParent(this);

    a1.setText("翻开");
    a2.setText("画问号");
    a3.setText("插旗");

    a1.setGeometry(50,760,130,50);
    a2.setGeometry(235,760,130,50);
    a3.setGeometry(420,760,130,50);

    connect(&a1,&QPushButton::pressed,this,&newmain:: Fan);
    connect(&a2,&QPushButton::pressed,this,&newmain:: Wen);
    connect(&a3,&QPushButton::pressed,this,&newmain:: Qi);


     setlei();
     labTime=new QLabel(this);
     //设置外观，Panel画一个平板看起来凹陷
     labTime->setFrameStyle(QFrame::Panel|QFrame::Sunken);
     //对齐方式
     labTime->setAlignment(Qt::AlignBottom|Qt::AlignRight);
     //设置大小和位置
     labTime->setGeometry(QRect(150,20,210,50));
     //设置时间label的显示
     labTime->setText(QString("<center><h1>Time(00:00)</h1></center>"));

     //提供时间函数给用户使用 用于对时间的操作
     time = new QTime();
     this->timer=new QTimer;
 //SIGNAL(timeout())表示：每当计时结束，计时器归零并重新计时，并发送一个信号激活slot函数
     connect(this->timer,SIGNAL(timeout()),this,SLOT(slot_timer_timeout()));


    a=new pose;
     //随机数种子
     qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
     //默认简单模式
     modelE();

}

//翻开格子
void newmain::Fan(){
    dian=fan;
}

//插旗子
void newmain::Qi(){
    dian=qi;
}

//画问号
void newmain::Wen(){
    dian=wen;
}

//将秒数转换成分秒格式
void newmain::timeChange(int sec){
       minute =sec/60;
       second =sec%60;
}

void newmain::slot_timer_timeout()
{
    timeChange(sec);
    sec++;

    //center居中，h1加粗
    if(second>=10)
    {
        labTime->setText(QString("<center><h1>(0%1:%2)</h1></center>").arg(minute).arg(second));
    }
    else
    {
        labTime->setText(QString("<center><h1>(0%1:0%2)</h1></center>").arg(minute).arg(second));
    }
}

void newmain::init()
{
    if(status==Playing){
        this->timer->start(1000);
    }
}

//简单模式
void newmain:: modelE(){

    //初始化
    setlei();

    if(bestMinute1!=0x7fffffff){
        if(bestSecond1>=10)
            QMessageBox::about(this,tr("扫雷"),tr("您简单模式的最佳成绩为：0%1:%2").arg(bestMinute1).arg(bestSecond1));
        else
            QMessageBox::about(this,tr("扫雷"),tr("您简单模式的最佳成绩为：0%1:0%2").arg(bestMinute1).arg(bestSecond1));
    }

    type=Easy;
    status=Playing;
    dian=fan;
    sec=0;
    init();
    n=10;
    draw();
    update();
}

//一般模式
void newmain:: modelM(){

    //初始化
    setlei();

    if(bestMinute2!=0x7fffffff){
        if(bestSecond2>=10)
            QMessageBox::about(this,tr("扫雷"),tr("您一般模式的最佳成绩为：0%1:%2").arg(bestMinute2).arg(bestSecond2));
        else
            QMessageBox::about(this,tr("扫雷"),tr("您一般模式的最佳成绩为：0%1:0%2").arg(bestMinute2).arg(bestSecond2));

    }

    type=Medium;
    status=Playing;
    dian=fan;
    sec=0;
    init();
    n=20;
    draw();
    update();
}

//困难模式
void newmain:: modelH(){

    //初始化
    setlei();

    if(bestMinute3!=0x7fffffff){
        if(bestSecond3>=10)
            QMessageBox::about(this,tr("扫雷"),tr("您困难模式的最佳成绩为：0%1:%2").arg(bestMinute3).arg(bestSecond3));
        else
            QMessageBox::about(this,tr("扫雷"),tr("您困难模式的最佳成绩为：0%1:0%2").arg(bestMinute3).arg(bestSecond3));

    }

    type=Hard;
    status=Playing;
    dian=fan;
    sec=0;
    init();
    n=30;
    draw();
    update();
}

void newmain::draw(){

    //随机确定雷的位置
    for(int i=0;i<n;i++){
        int l=rand()%(99-i+1);
        int m=0;
        for(int j=0;j<10;j++)
            for(int k=0;k<10;k++){
                if(lei[j][k]==0){
                    if(m==l){
                      lei[j][k]=1;
                     //p.drawPixmap(50+j*50,250+k*50,50,50,QPixmap("E:/saoleii/image/lei.JPG"));
                       m+=1;
                   }
                   else
                       m+=1;
                   }
                else
                    continue;
            }
    }

    //计算提示数字
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            //改点无雷，可显示提示数字
            if(lei[i][j]==0){
                //历遍周围八个格子
                for(int x=-1;x<=1;x++)
                    for(int y=-1;y<=1;y++)
                        //避免查询的点超出范围
                        if(!(x==0&&y==0)&&i+x>=0&&i+x<10&&j+y>=0&&j+y<10)
                            //该点有雷
                            if(lei[i+x][j+y]==1)
                                num[i][j]+=1;
            }

}

void newmain::poschange(){
    times++;
    static QTime pauseTime;

    if(times%2==1){
        pauseTime = QTime::currentTime();
        this->timer->stop();
         Pushpos.setText("继续");
         a->show();
         a->bol=false;
         a->bola=false;
         a->bolb=false;
    }

    else if(times%2==0){

         Pushpos.setText("暂停");

         if(a->bol){
             sec=0;
             this->timer->start(1000);
         }

         if(a->bola){
             QTime cut = QTime::currentTime();
             int t = pauseTime.msecsTo(cut);
             this->baseTime = this->baseTime.addMSecs(t);
             this->timer->start();
         }

         if(a->bolb){
             if (!(QMessageBox::information(this,tr("CT Control View"),tr("确定放弃当前进度吗?"),tr("Yes"),tr("No"))))
                      {
                           this->close();
                       }
         }
    }
}

void newmain::paintEvent(QPaintEvent *)
{
    QPainter p(this); //创建画家对象
    //p.drawPixmap(this->rect(),QPixmap("E:/saoleii/image/i.JPG")); //画背景图

    //定义画笔，确定线宽，颜色,风格
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);

    //定义画刷
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    p.setPen(pen);//将画笔交给画家

    //画棋盘
    for(int i=0;i<11;i++)
    {
        //横线
        p.drawLine(50,250+i*50,550,250+i*50);

        //竖线
        p.drawLine(50+i*50,250,50+i*50,750);
    }

    //画雷
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            if(lei[i][j]==1&&dianji[i][j]==1)
                p.drawPixmap(55+j*50,255+i*50,40,40,QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/lei.JPG"));

    //填充提示数字
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++){
            if(dianji[i][j]==1&&chaqi[i][j]!=1){
               if(num[i][j]==1)
                   p.drawPixmap(55+j*50,255+i*50,40,40,QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/1.JPG"));
               else if(num[i][j]==2)
                   p.drawPixmap(55+j*50,255+i*50,40,40,QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/2.JPG"));
               else if(num[i][j]==3)
                   p.drawPixmap(55+j*50,255+i*50,40,40,QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/3.JPG"));
               else if(num[i][j]==4)
                   p.drawPixmap(55+j*50,255+i*50,40,40,QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/4.JPG"));
               else if(num[i][j]==5)
                   p.drawPixmap(55+j*50,255+i*50,40,40,QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/5.JPG"));
               else if(num[i][j]==6)
                   p.drawPixmap(55+j*50,255+i*50,40,40,QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/6.JPG"));
               else if(num[i][j]==7)
                   p.drawPixmap(55+j*50,255+i*50,40,40,QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/7.JPG"));
               else if(num[i][j]==8)
                   p.drawPixmap(55+j*50,255+i*50,40,40,QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/8.JPG"));
               else if(num[i][j]==0&&lei[i][j]==0)
                   p.drawPixmap(55+j*50,255+i*50,40,40,QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/00.JPG"));
            }
            else if(dianji[i][j]==0&&chaqi[i][j]==0)
                p.drawPixmap(52+j*50,252+i*50,44,44,QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/0.JPG"));
            else if(chaqi[i][j]==1&&dianji[i][j]==0)
                p.drawPixmap(52+j*50,252+i*50,44,44,QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/qizi.JPG"));
            else if(chaqi[i][j]==2&&dianji[i][j]==0)
                p.drawPixmap(52+j*50,252+i*50,44,44,QPixmap("C:/Users/lenovo/Desktop/tdks/saoleii/image/wenhao.JPG"));
        }
}

void newmain:: mousePressEvent(QMouseEvent *e){

    int x=0,y=0;
    //获取点击坐标
     x=e->x();
     y=e->y();

     //确保点击的点正确，不超出范围
     if(x>=50&&x<=550&&y>=250&&y<=750){

         //将点击的位置转化为棋盘中的点
         mousex=(y-250)/50;
         mousey=(x-50)/50;

         if(dian==fan)
                 fankai();
         else if(dian== qi)
                 chaqizi();
         else if(dian==wen)
                 wenhao();
     }
     update();
}

void newmain::fankai(){

    if(chaqi[mousex][mousey]!=1){

    //点中雷所在位置，游戏结束，显示失败
    if(lei[mousex][mousey]==1){
        dianji[mousex][mousey]=1;
        update();
        QMessageBox::StandardButton btnValue = QMessageBox::information(this, "游戏结束", "很遗憾，您未取得胜利，请再接再厉！");

        // 重置游戏状态
        if (btnValue == QMessageBox::Ok)
        {
              modelE();
              update();
         }
    }

    //点击提示数字所在位置，继续游戏
    else if(lei[mousex][mousey]==0&&num[mousex][mousey]!=0){
        dianji[mousex][mousey]=1;
        update();
    }

    //点击的点无雷且没有提示数字
    else{
        dianji[mousex][mousey]=1;
        digui(mousex,mousey);
        update();
    }

    int rest=0;
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            if(lei[i][j]==0&&dianji[i][j]==1)
                rest+=1;

    if(rest+n==100){
        //QMessageBox::StandardButton btnValue = QMessageBox::information(this, "游戏结束", "恭喜你取得胜利，用时！");
        this->timer->stop();
        if(second>=10){
            QMessageBox::about(this,tr("扫雷"),tr("恭喜你取得胜利！\n您本次用时为：0%1:%2").arg(minute).arg(second));
            //记录本次成绩
            score nowScore(minute,second);
            //比较每次输入成绩 设置最好成绩
            this->setBestScore(nowScore);
                  modelE();
                  update();

        }
        else{
            QMessageBox::about(this,tr("扫雷"),tr("恭喜你取得胜利！\n您本次用时为：0%1:0%2").arg(minute).arg(second));
            //记录本次成绩
            score nowScore(minute,second);
            //比较每次输入成绩 设置最好成绩
            this->setBestScore(nowScore);
                modelE();
                update();
        }

    }

    mousex=-1;
    mousey=-1;
  }
}

//比较每次输入成绩 设置最好成绩
void newmain::setBestScore(score &test){
    //简单模式
    if(type==Easy){

        if((test.minute<bestMinute1)||(test.minute==bestMinute1&&test.second<bestSecond1))
        {
            bestMinute1=test.minute;
            bestSecond1=test.second;
        }
    }

    //一般模式
    if(type==Medium){
        if((test.minute<bestMinute2)||(test.minute==bestMinute2&&test.second<bestSecond2))
        {
            bestMinute2=test.minute;
            bestSecond2=test.second;
        }
    }

    //困难模式
    if(type==Hard){
        if((test.minute<bestMinute3)||(test.minute==bestMinute3&&test.second<bestSecond3))
        {
            bestMinute3=test.minute;
            bestSecond3=test.second;
        }
    }

}

//插旗子
void newmain::chaqizi(){

    if(dianji[mousex][mousey]==0&&chaqi[mousex][mousey]!=1){
        dian=qi;
        chaqi[mousex][mousey]=1;

        mousex=-1;
        mousey=-1;

    }

    //再次点击棋子使棋子转变为问号
    else if(dianji[mousex][mousey]==0&&chaqi[mousex][mousey]==1){
        dian=qi;
        chaqi[mousex][mousey]=2;

        mousex=-1;
        mousey=-1;
    }
}

//画问号
void newmain::wenhao(){

    if(dianji[mousex][mousey]==0){
        dian=wen;
        chaqi[mousex][mousey]=2;

        mousex=-1;
        mousey=-1;

    }
}

void newmain::digui(int x, int y){

    //确保判断的点在范围内
    if(x>=0&&x<10&&y>=0&&y<10){

         dianji[x][y]=1;

         //历遍周围八个方位
         for(int i=-1;i<=1;i++)
             for(int j=-1;j<=1;j++)
                 //未超出范围
                 if(x+i>=0&&x+i<10&&y+j>=0&&y+j<10)
                        if(lei[x+i][y+j]==0&&!(i==0&&j==0)&&dianji[x+i][y+j]==0){
                            //非本点且该点无雷

                            if(num[x+i][y+j]!=0){
                                //该点显示提示数字
                                dianji[x+i][y+j]=1;
                                continue;
                            }

                            else if(num[x+i][y+j]==0);
                                //该点为空点
                                digui(x+i,y+j);
                        }
     }
}

newmain::~newmain()
{
    delete ui;
}

void newmain::soundchange()
{
     SoundTimes++;

     //当按下“关闭音效”时
     if(SoundTimes%3==1)
     {
         sound2->stop();
         Pushsound.setText("关闭音效");
     }

     //当按下“音效1”时
     else if(SoundTimes%3==2)
     {
         sound1->play();
         sound1->setVolume(30);
         Pushsound.setText("音效1");
     }

     //当按下“音效2”时
     else if(SoundTimes%3==0)
     {
         sound1->stop();
         sound2->play();
         sound2->setVolume(30);
         Pushsound.setText("音效2");
     }
}
