#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QLabel>
#include<QTimer>
#include<QDateTime>
#include<QKeyEvent>
#include<QList>
#include<QKeyEvent>

const int MAX_X=35;
const int MAX_Y=25;
const int NORMAL_LABEL = 0;  // 普通label
const int BORDER_LABEL=1;    // 边界label
const int SNAKE_LABEL=2;     // 蛇身label
const int FOOD_LABEL=3;      // 食物label



namespace Ui {
class Widget;
}

struct Node
{
   QLabel *label;
   int type;    // 0 普通 1 边界 2 蛇身  3 食物
   int x;
   int y;
};


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public:
    void startGame();    // 开始游戏
    void exitGame();     // 退出游戏
    void deleteData();   // 清除数据
    void InitCtrls();   // 初始化控件
    void InitData();    // 初始化数据

    void DrawSnake();   // 画蛇身
    void DrawBorder();  // 画边界
    void CreatFood();   // 产生食物

    void getSnakeHeadTail();  // 获取蛇的头和尾
    void MoveStep();    // 移动
    bool Up();          // 向上移动
    bool Down();        // 向下移动
    bool Left();        // 向左移动
    bool Right();       // 向右移动

public slots:
    void slotMoveStep();
protected:
    void keyPressEvent(QKeyEvent *e);    // 键盘按下事件
  //  void timerEvent(QTimerEvent *e);     // 定时器事件
private:
    int  m_ndx;        // 很坐标方向
    int  m_ndy;        // 纵坐标方向
    Node *m_nTail;     // 蛇尾指针
    Node *m_nHead;     // 蛇头指针
    Node *matrix[MAX_X][MAX_Y];  // 地图背景
   QList<Node*>  m_nSnake;  // 蛇身
    QTimer m_nTimer;   // 定时器
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
