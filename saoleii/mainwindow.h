#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSound>
#include <QLabel>
#include "newmain.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void receive();
    void paintEvent(QPaintEvent *) ;

    void poschange();

    QPushButton * mainButton;
    newmain *w;
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    //进入游戏按钮
    QPushButton PushStart;

    //进入规则
    QPushButton PushRule;

    //音效
    QPushButton PushSound;

    //"加油"&记录最好成绩
    QLabel *notice;

    //记录点击音效按钮次数
    int SoundTimes=0;

private slots:
     void play();
//    void tomainSlot();
//    void tosubSlot();
};

#endif // MAINWINDOW_H



