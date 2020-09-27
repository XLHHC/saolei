#ifndef POSE_H
#define POSE_H
#include <QPushButton>
#include <QSound>
#include <QLabel>
#include <QMainWindow>
#include<QtMultimedia/QMediaPlayer>
#include<QTime>
#include<QTimer>
namespace Ui {
class pose;
}

class pose : public QMainWindow
{
    Q_OBJECT

public:
    explicit pose(QWidget *parent = 0);
    QPushButton pushagain;

    //重新开始
    bool bol=false;
    //继续
    bool bola=false;
    //返回主界面
    bool bolb=false;

    void paintEvent(QPaintEvent *);
    ~pose();

private slots:

    void on_horizontalSlider_2_valueChanged(int value);

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_returnstart_clicked();

private:
    Ui::pose *ui;
    QMediaPlayer m_mediaplayer;
};

#endif // POSE_H
