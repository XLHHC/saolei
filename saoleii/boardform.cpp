#include "boardform.h"
#include<iomanip>
#include<iostream>
#include<math.h>
#include<QTime>
#include<QTimer>

boardform::boardform()
{

}

using namespace std;
const int direction[3]{ -1,0,1 };   //方向增量
void boardform::reSet(){        //重设表格
    setBoard();
    flagNumber=totalBomb;       //剩余旗子数等于炸弹总数
}
void boardform::setBoard() {    //初始化所有格子都没有被翻开 flip[][]都是0
    for (int xx = 0; xx < boundaryM; xx++) {
        for (int yy = 0; yy < boundaryN; yy++) {
            flipped[xx][yy] = 0;
            board[xx][yy] = 0;
        }
    }
}
void boardform::setBomb(int xx,int yy) {    //这是随机设置炸弹的 输入的参数xx yy是第一次点击的坐标
    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));//随机种子
    for (int i = 0; i <10; )
    {
        int x = qrand() % boundaryM;
        int y = qrand() % boundaryN;
        if (board[x][y] != 9 && !(abs(x-xx) <= 1 && abs(y-yy) <= 1))    //当这个格子没有炸弹而且不在第一次点击的周围时
        {
            board[x][y] = 9;    //设置炸弹
            i++;                //炸弹数减少
        }
    }
}
int boardform::setANumber(int x, int y) {   //和下面一个函数一起看的
    int count = 0;                          //这个函数主要是设置（x，y）周围到底有多少个炸弹的
    for (int ix = 0; ix < 3; ix++) {
        for (int iy = 0; iy < 3; iy++) {
            if (x + direction[ix] < 0 || x + direction[ix] >= boundaryM)    //如果x越界
                continue;
            else if (y + direction[iy] < 0 || y + direction[iy] >= boundaryN)//如果y越界
                continue;
            else if (direction[ix] == 0 && direction[iy] == 0)continue;     //排除自身格子
            else if (board[x + direction[ix]][y + direction[iy]] == 9)count++;
        }
    }
    return count;
}
void boardform::setNumber() {   //这是初始化整个表格数字的
    for (int xx = 0; xx < boundaryM; xx++) {
        for (int yy = 0; yy < boundaryN; yy++) {
            if(board[xx][yy]!=9)
                board[xx][yy]=setANumber(xx, yy);
        }
    }
}
void boardform::boardform::printBoard(bool overJudge) {    //这是vs中打印表格的函数
    //炸弹用@
    //数字直接写
    //没翻开的用#
    if (overJudge) {    //如果游戏结束 反正游戏结束了所有炸弹都要用@表示 没结束就用#
        cout << "   ";  //第65-69行主要是保持表格整齐
        for (int i = 1; i <= boundaryM; i++) {
            cout << i << " ";
        }
        cout << endl;
        for (int xx = 0; xx < boundaryM; xx++) {
            cout << setw(2) << xx + 1 << " ";
            for (int yy = 0; yy < boundaryN; yy++) {
                if (board[xx][yy] == 9)cout << "@ ";
                else if (flipped[xx][yy] && board[xx][yy])cout << board[xx][yy] << " ";
                else if (flipped[xx][yy] == 0)cout << "# ";
                else cout << 0 << " ";
            }
            cout << endl;
        }
    }
    else {//如果游戏没结束
        cout << "   ";
        for (int i = 1; i <= boundaryM; i++) {
            cout << i << " ";
        }
        cout << endl;
        for (int xx = 0; xx < boundaryM; xx++) {
            cout << setw(2) << xx + 1 << " ";
            for (int yy = 0; yy < boundaryN; yy++) {
                if (flipped[xx][yy]==0)cout << "# ";
                else if (flipped[xx][yy] && board[xx][yy])cout << board[xx][yy] << " ";
                else cout << 0 << " ";
            }
            cout << endl;
        }
    }
    cout << endl;
}
int boardform::getTotalBomb(){
    return totalBomb;
}
int boardform::getBoundaryM() {
    return boundaryM;
}
int boardform::getBoundaryN() {
    return boundaryN;
}
void boardform::minusFlagNumber(bool minus){//剩余旗子数减少
    if(minus==true)
        flagNumber--;
}
int boardform::getFlagNumber(){
    return flagNumber;
}
void boardform::setFlipped(int xx, int yy, int status) {//翻了一个格子
    if(flipped[xx][yy]==2&&status!=2){  //如果原来插了旗子但是后来又不插旗子了
        flagNumber++;                   //剩余的旗子数增加
    }
    flipped[xx][yy] = status;   //（x，y）这个格子被翻开了
}
int boardform::getNumber(int x, int y) {    //返回这个格子周围的炸弹数
    return board[x][y];
}
int boardform::getFlipped(int x, int y) {   //返回这个格子是否被翻开了
//    int tst=flipped[x][y];
    return flipped[x][y];
}
void next(boardform &game, int x, int y) {  //递归翻开格子
    int BoundaryM = game.getBoundaryM();    //因为不是成员函数所以要再设置新变量
    int BoundaryN = game.getBoundaryN();
    game.setFlipped(x, y, 1);
    if (game.getNumber(x, y) == 0) {
        for (int ix = 0; ix < 3; ix++) {
            for (int iy = 0; iy < 3; iy++) {
                if (x + direction[ix] >= 0 && x + direction[ix] < BoundaryM &&
                    y + direction[iy] >= 0 && y + direction[iy] < BoundaryN) {  //如果没有越界就递归
                    if (!(direction[ix]==0 && direction[iy]==0)) {  //而且不等于自身
                        if (game.getFlipped(x + direction[ix], y + direction[iy]) == 0) {
                            next(game, x + direction[ix], y + direction[iy]);
                        }
                    }
                }
            }
        }
    }
}
bool boardform::isBomb(int x, int y) {  //某一格子是否是炸弹
    if (board[x][y] == 9)return true;
    else return false;
}
bool boardform::check() {   //检查炸弹是否已经全部被找到
    //全部找到返回true 还有没找到返回false
    //cout<<countFlipped<<endl;
    int countBombs=0;   //局部
    for(int xx=0;xx<boundaryM;xx++){
        for(int yy=0;yy<boundaryN;yy++){
            if(flipped[xx][yy]!=1)countBombs++; //格子没有被翻开或者已经被插旗
        }
    }
    if (countBombs==totalBomb)return true;
    else return false;
}
void boardform::askAgain() {    //vs询问是否再来一局
    cout << "Do you want to try again ?" << endl;
    cout << "你想再玩儿一局吗？" << endl;
    cout << "If you want to try again ,please input 'Y'." << endl;
    cout << "如果你想要再玩儿一局，请输入'Y'" << endl;
    cout << "If you want to quit ,please input 'N'." << endl;
    cout << "如果你怂了，那就输'N'吧，垃圾玩意儿" << endl;
}
void boardform::test() {    //测试用函数
    cout << "this is board[][]" << endl;
    for (int xx = 0; xx < boundaryM; xx++) {
        for (int yy = 0; yy < boundaryN; yy++) {
            cout << board[xx][yy] << " ";
        }
        cout << endl;
    }
    cout << "this is flipped[][]" << endl;
    for (int xx = 0; xx < boundaryM; xx++) {
        for (int yy = 0; yy < boundaryN; yy++) {
            cout << flipped[xx][yy] << " ";
        }
        cout << endl;
    }
}
