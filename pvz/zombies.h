#ifndef ZOMBIES_H
#define ZOMBIES_H

#include <QObject>
#include<QLabel>
#include<QThreadPool>
#include"media.h"
class Zombies:public QObject
{
    Q_OBJECT
public:
    Zombies();

    ~Zombies();

    Zombies(int HP,int ATK,QString URL,QString eatURL,QString dieURL);

    Zombies(Zombies*a);

    int getHP();

    int getATK();

    QString getEatURL();

    //僵尸遭受攻击
    void be_attack(int atk);

    QString getURL();

    void sety(int num);

    void minusx(int num);

    int getY();

    QString getDieURL();

    void setDieURL(QString dieURL);

    bool getZombiMove();

    int getZombieInt();

    void setZombieMove(bool flag);

    void setZombieInt(int zombieint);

    QLabel*getLabel();

    void setLabel(QLabel*a);

    void setIfCome(bool flag);

    bool getIfCome();

    void setIndex(int index);

    int getIndex();



signals:
    void eatMusic();

public slots:
    void EATmusic(int index);

    void stopEat(int index);


private:
    QMediaPlayer*op;


    //僵尸正常行走gif路径
    QString URL;

    //僵尸吃植物时候的路径
    QString eatURL;

    //僵尸死亡时候的路径
    QString dieURL;

    int index;

    int x;

    int y;

    //僵尸血量
    int HP;

    //僵尸攻击力
    int ATK;

    //僵尸移动速度
    int v;

    QLabel*label;

    //是否在移动
    bool zombiemove;

    //是否与植物相碰
    int zombieint;

    //是否进入草坪
    bool ifCome;

    Media*a;
};

#endif // ZOMBIES_H
