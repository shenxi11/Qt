#ifndef CHOOSEPLANT_H
#define CHOOSEPLANT_H

#include <QObject>
#include<QLabel>
#include<QPixmap>
#include<QMouseEvent>
#include<QMovie>
#include<QDebug>
class choosePlant:public QLabel
{
    Q_OBJECT
public:
    choosePlant();

    choosePlant(int num,QPoint pos,QWidget *parent = nullptr):QLabel(parent){
        startPos=pos;
        this->num=num;
    }

    void setNum(int num);

    void view(QString url);

    int getNum();

    void LabelMove(int x,int y);


    //移动回原点
    void moveBack();

    void setIfInCD(bool flag);

protected:
    void mousePressEvent(QMouseEvent *event) override ;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void makePlants(QPoint pos);

    void choose(QPoint pos);

    void Move(QPoint pos);


public slots:
    void inCD();

    void setMove(bool flag);

private:
    int num;

    //是否可以移动
    bool moveAble=false;

    //是否处于冷却
    bool ifInCD=true;

    //起点坐标
    QPoint startPos;


};

#endif // CHOOSEPLANT_H
