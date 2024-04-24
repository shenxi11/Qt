#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include<QLabel>
#include<QPoint>
#include<QThreadPool>
#include"media.h"
#include"cauclate.h"
class Bullet:public QObject
{
    Q_OBJECT
public:
    Bullet();

    Bullet(int v,int length,bool isPULT);

    Bullet(Bullet*b);

    ~Bullet();

    void setURL(QString url);

    Bullet*& operator=(Bullet*&k);

    QString getURL();

    int getV();

    int getLength();

    QLabel*getLabel();

    int getATK();

    void setATK(int atk);

    void setBulletAttack(bool attack);

    bool getBulletAttack();

    void setLabel(QLabel*a);

    void setNumber(int index);

    int getIndex();

    void setPlantsNumber(int Number);

    int getPlantsNumber();

    void setPult(bool pult);

    bool getPult();

    QPoint getStartPos();

    void setY(int y);

    int getY();

    void setStartPos(QPoint pos);

    int dx=0;

    int isTrue=0;
public slots:
    void Bullet_MOve(int index,float x);


signals:

    void MOve(float x);

    void playMusic();

    void MoveTo(float x);

private:

    QLabel*label;

    int ATK;

    bool isPult;

    //子弹图片路径
    QString url;

    //子弹运动速度
    int v;

    //子弹边长
    int length;

    bool bulletAttack;


    int number;

    int plantsNumber;

    QPoint startPos;

    Cauclate*cc;

    int Y;



};

#endif // BULLET_H
