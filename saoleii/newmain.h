#ifndef NEWMAIN_H
#define NEWMAIN_H
#include"pose.h"
#include <QPushButton>
#include <QSound>
#include <QLabel>
#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include<QMouseEvent>
#include<qstring.h>

namespace Ui {

class newmain;

}

enum Type
{
    Easy,       //简单模式
    Medium,     //一般模式
    Hard        //困哪模式
};

//游戏状态
enum Status
{
  Playing,   //游戏进行中
  End        //游戏结束
};

enum Dian{
    fan,
    qi,
    wen
};

struct score{       //单次成绩

    int minute;
    int second;

    //构造函数
    score(int min,int sec){
        minute=min;
        second=sec;

    }
};

class newmain : public QMainWindow
{
    Q_OBJECT

public:

    explicit newmain(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

    QPushButton Pushpos;
    void timeChange(int sec);   //将时间转换成标准格式分秒
    pose *a;
    ~newmain();

    //设置游戏模式
    Type type;
    Status status;
    Dian dian;

    //设置简单模式的基本信息
    void modelE();

    void soundchange();

    //设置一般模式的基本信息
    void modelM();

    //设置困难模式的基本信息
    void modelH();

    //随机生成地雷的位置并计算地雷周围的提示数字
    void draw();

    void init();

    //用于存放这个位置是否有雷，有雷存1，无雷存0
    int lei[10][10];

    //用于存放该位置周围雷的个数
    int num[10][10];

    //存储点击情况
    int dianji[10][10];
    int chaqi[10][10];

    int bestMinute1=0x7fffffff;  //初始化最好成绩为int最大值
    int bestSecond1=0x7fffffff;

    int bestMinute2=0x7fffffff;  //初始化最好成绩为int最大值
    int bestSecond2=0x7fffffff;

    int bestMinute3=0x7fffffff;  //初始化最好成绩为int最大值
    int bestSecond3=0x7fffffff;
    //初始化棋盘数据
    int getBestMin();   //返回最好成绩的分
    int getBestSec();
    void setlei();
    void setBestScore(score &test);//设置最好成绩

private slots:
    void poschange();
    void slot_timer_timeout();

private:

    //记录多少分钟
    int minute;
    //记录多少秒钟
    int second;
    //放时间的label
    QLabel *labTime;

    //记录鼠标点击的位置
    int mousex,mousey;

    //QTime类提供时间函数给用户使用，主要用于对时间的操作
    QTime *time;
    //QTimer计时器类
    QTimer *timer;

    //定义六个按钮
    QPushButton  c1;
    QPushButton  c2;
    QPushButton  c3;
    QPushButton  a1;
    QPushButton  a2;
    QPushButton  a3;

    int sec=0;

    QPushButton Pushsound;
    QTimer *pTimer;
    QTime baseTime;
    QMediaPlayer *sound1;
    QMediaPlayer *sound2;

    //显示的时间
    QString timeStr;

    //雷的个数
    int n=0;

    bool bol;

    int SoundTimes=0;

    Ui::newmain *ui;

    int times=0;

    //监听鼠标
    void mousePressEvent(QMouseEvent *e);

    //改变格子的状态
    void fankai();
    void chaqizi();
    void wenhao();
    void Fan();
    void Qi();
    void Wen();

    //用递归实现一次性翻开多个格子
    void digui(int x,int y);

};

#endif // NEWMAIN_H
