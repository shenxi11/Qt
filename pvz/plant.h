#ifndef PLANT_H
#define PLANT_H

#include <QObject>
#include<QTimer>
#include<list>
#include"bullet.h"
#include"sun.h"
#include<QMediaPlayer>
#include<QAudioOutput>
#include<QThreadPool>
#include"media.h"
#include"cauclate.h"
using namespace std;
class Plant : public QObject
{
    Q_OBJECT
public:
    Plant();

    ~Plant();

    Plant(int number,int HP,int ATK,int times,int isATK,QString url,QString chooseUrl,QString bulletURL,int sunCost,int ATKarea,QString GraychooseUrl);

    Plant(Plant*a);

    int getHP();

    int getATK();

    int getTimes();

    int getIsAtk();

    int getNumber();

    Bullet*getBullet();

    void setBullet(Bullet*a);

    void outBullet();

    QString getURL();

    QString getChooseURL();

    QString getBulletURL();

    QString getGraychooseUrl();

    int getX();

    int getY();

    int getSunCost();


    void setBoomURL(QString BoomURL);

    QString getBoomURL();

    //射击模式
    void shotMode();

    //设定坐标
    void setXY(int x,int y);

    //植物遭受攻击
    void be_attack(int atk);

    QLabel*getLabel();

    void setLabel(QLabel*a);

    int getATKarea();

    void inCD();

    bool getIfCD();

    void setIsShooting(bool flag);

    bool getIsShooting();

    void stopShot(int index);

    void beginShoot(int index);

    void setIndex(int index);

    int getIndex();

    void setCount1(int Count1);

    int getCount1();

    bool getIsready();

public slots:
    void setCD();

    void setTimer1(QTimer*pi);

    void hit_music(int index);

    void shot1(int index);

    void Cabage(int index,float x);

private slots:

    void makeSun();

    void setcd();

    void shot();



    void readyToBoom();

signals:
    void MOve(float x);

    void MoveTo(float x);

    void attack(int index);

    void stopAttack(int index);

    void MakeSun();

    void huifu(int index);

    void Shot();

    void playMusic();

    void readyBoom();
private:
    int X;

    int Y;

    Media*aa;

    Cauclate*cc;

    bool isready=false;

    //植物的序号
    int number;

    QString url;

    //种植所需阳光
    int sunCost;

    //植物血量
    int HP;

    //植物攻击力
    int ATK;

    //冷却时间
    int times;

    //攻击模式区分
    int isATK;

    int ATKarea;



    QString GraychooseUrl;
    QString chooseUrl;
    QString BoomURL;
    //子弹
    Bullet*bullets;

    QString bulletURL;

    QLabel*label;

    QTimer*time1;
    QTimer*tt;

    bool isShooting=false;

    //是否处于冷却状态
    bool ifCD=false;

    int index;

    int id1;

    int Count1=0;
};

#endif // PLANT_H
