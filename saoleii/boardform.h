//这个头文件里我放了类的成员说明 只要cpp里面包含了这个头文件都可以用这个类的
#ifndef BOMBBOARD_H
#define BOMBBOARD_H

class boardform {
//按照规范 成员默认private
    int boundaryM=9 ;
    int boundaryN=9 ;
    int board[9][9];    //先确定一个10*10的矩阵
                        //每个格子里0-8表示周围3*3方格中炸弹的数量
                        //格子是9的话表示有炸弹
    int flipped[9][9];  //表示有没有被翻开过 ques为3 flag为2 翻开为1 不翻开为0
    int totalBomb=10;   //确定炸弹总数为10
    int flagNumber=totalBomb;
public:         //成员函数：<-这边只是声明了一下 具体实现看.cpp那个文件
    boardform();
    ~boardform();
    void reSet();       //重设表格
    void setBoard();    //初始化表格 最初所有格子都没有被翻开过 所以flipped都为0
    void printBoard(bool overJudge);//打印表格 参数是为了区别游戏是否已经结束（打印的东西不太一样）
    void setBomb(int xx,int yy);    //随机设置炸弹位置
    int setANumber(int x,int y);    //设置（x，y）周围的炸弹数
    void setNumber();   //设置全表每个格子的炸弹数
    void minusFlagNumber(bool minus);   //剩余炸弹(旗子)数--
    int getFlagNumber();//返回剩余旗子数
    int getTotalBomb(); //返回炸弹总数
    int getBoundaryM(); //返回边界值
    int getBoundaryN(); //返回边界值
    int getNumber(int x, int y);    //返回这个格子周围的炸弹数
    int getFlipped(int x, int y);   //返回这个格子有没有被翻开过
    void setFlipped(int x, int y, int status);//把这个格子翻开
    bool isBomb(int x, int y);      //如果这个格子是炸
    bool check();       //检查炸弹是不是已经全部被找出来了
    void askAgain();    //询问是否进行下一局

    void test();    //只是测试用
};
    void next(boardform &a, int x, int y);  //扩展空白格子 递归函数

#endif //BOMBBOARD_H
