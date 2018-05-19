#include "widget.h"
#include "ui_widget.h"
#include<QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // startGame();

    InitCtrls();
    InitData();
    DrawBorder();
    DrawSnake();
    CreatFood();

    // 初始化随机树种子
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    //m_nTimer=startTimer(1000);

    connect(&m_nTimer,SIGNAL(timeout()),this,SLOT(slotMoveStep()));
    m_nTimer.start(100);

}

Widget::~Widget()
{
    // killTimer(m_nTimer);
    delete ui;
}
// 开始游戏
void Widget::startGame()
{
    InitCtrls();
    InitData();
    DrawBorder();
    DrawSnake();
    CreatFood();
}
// 退出游戏
void Widget::exitGame()
{
    exit(1);
}
// 清除数据
void Widget::deleteData()
{
    m_ndx=0;
    m_ndy=0;
    if(m_nHead!=NULL)
    {
        delete m_nHead;
        m_nHead=NULL;
    }
    if(m_nTail!=NULL)
    {
        delete m_nTail;
        m_nTail=NULL;
    }
    m_nTimer.stop();
    m_nSnake.clear();
}
// 初始化控件
void Widget::InitCtrls()
{
    setWindowTitle("Snake Game");
    resize(875,625);
    m_ndx=0;
    m_ndy=0;
    m_nHead=NULL;
    m_nTail=NULL;


}
// 初始化数据
void Widget::InitData()
{
    int gridSize=25;

    for(int i=0;i<MAX_X;i++)
    {
        for(int j=0;j<MAX_Y;j++)
        {
            QLabel *label=new QLabel(this);
            label->setStyleSheet("background:rgb(226,44,20)");
            label->setGeometry(i*gridSize,j*gridSize,gridSize,gridSize);
            label->hide();

            matrix[i][j]=new Node;
            matrix[i][j]->label=label;
            matrix[i][j]->type=NORMAL_LABEL;
            matrix[i][j]->x=i;
            matrix[i][j]->y=j;

        }
    }
}
// 画蛇身
void Widget::DrawSnake()
{
    int x0=10;   // 初始化蛇的位置坐标 x0
    int y0=10;   // 初始化蛇的位置坐标 y0
    int nSnakeSize=3;   // 初始化蛇的长度 为 3

    // 设置蛇的初始运动方向

    // 清空蛇的链表
    m_nSnake.clear();

    // 设置蛇开始时向右移动

    m_ndx=1;
    m_ndy=0;

    for(int x=x0;x<x0+nSnakeSize;x++)
    {
        m_nSnake.append(matrix[x][y0]);
        m_nSnake.at(m_nSnake.length()-1)->x=x;
        m_nSnake.at(m_nSnake.length()-1)->y=y0;

        matrix[x][y0]->type=SNAKE_LABEL;
        matrix[x][y0]->label->show();
    }


}
// 画边界
void Widget::DrawBorder()
{
    for(int x=0;x<MAX_X;x++)
    {
        for(int y=0;y<MAX_Y;y++)
        {
            if(x==0||y==0||x==MAX_X-1||y==MAX_Y-1)
            {
                matrix[x][y]->label->show();
                matrix[x][y]->type=BORDER_LABEL;
            }

        }
    }
}
// 产生食物
void Widget::CreatFood()
{
    int food_x=qrand()%MAX_X;
    int food_y=qrand()%MAX_Y;

    if(matrix[food_x][food_y]->type!=NORMAL_LABEL)
    {
        CreatFood();

    }
    else
    {
        matrix[food_x][food_y]->type=FOOD_LABEL;

        matrix[food_x][food_y]->label->show();
    }
}
// 获取蛇的头和尾
void Widget::getSnakeHeadTail()
{
    m_nHead=m_nSnake.at(m_nSnake.length()-1);  // 蛇的尾就是头
    m_nTail=m_nSnake.at(0);   // 蛇的尾其实是List的第一个元素
}

void Widget::MoveStep()
{
    // 获取蛇的头和尾指针
    getSnakeHeadTail();

    Node *n=matrix[m_nHead->x+m_ndx][m_nHead->y+m_ndy];
    n->label->show();
    // n 是即将变成蛇头的那个 label
    if(n->type==BORDER_LABEL||n->type==SNAKE_LABEL)
    {
        m_nTimer.stop();
        int res=QMessageBox::question(this,"应用程序提示","Game Over!","确定","取消");
        if(res==QMessageBox::Yes)
        {
            //exitGame();
            exit(1);
        }
        else
        {
            //  startGame();
            return;
        }
    }

    else
    {
        if(n->type==FOOD_LABEL)  // 吃到食物了
        {
            n->type=SNAKE_LABEL;
            m_nSnake.append(n);

            // 不移除尾巴
            CreatFood();
        }
        else
        {
            n->type=FOOD_LABEL;
            m_nSnake.append(n);
            m_nTail->label->hide();

            m_nTail->type=NORMAL_LABEL;
            m_nSnake.removeFirst();

        }

    }

}
// 向上移动
bool Widget::Up()
{
    if(m_ndx==0)
    {
        return false;
    }
    return true;
}
// 向下移动
bool Widget::Down()
{
    if(m_ndx==0)
    {
        return false;
    }
    return true;
}
// 向左移动
bool Widget::Left()
{
    if(m_ndy==0)
    {
        return false;
    }
    return true;

}
// 向右移动
bool Widget::Right()
{
    if(m_ndy==0)
    {
        return false;
    }
    return true;
}

// 键盘按下事件
void Widget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_W:
        if(Up())
        {
            m_ndx=0;
            m_ndy=-1;
        }
        break;
    case Qt::Key_S:
        if(Down())
        {
            m_ndx=0;
            m_ndy=1;
        }
        break;
    case Qt::Key_A:
        if(Left())
        {
            m_ndx=0;
            m_ndy=-1;
        }
        break;
    case Qt::Key_D:
        if(Right())
        {
            m_ndx=0;
            m_ndy=1;
        }
        break;
    case Qt::Key_Up:
        if(Up())
        {
            m_ndx=0;
            m_ndy=-1;
        }
        break;
    case Qt::Key_Down:
        if(Down())
        {
            m_ndx=0;
            m_ndy=1;
        }
        break;
    case Qt::Key_Left:
        if(Left())
        {
            m_ndx=-1;
            m_ndy=0;
        }
        break;
    case Qt::Key_Right:
        if(Right())
        {
            m_ndx=1;
            m_ndy=0;
        }
        break;
    default:
        break;
    }

}

void Widget::slotMoveStep()
{
    MoveStep();
}

