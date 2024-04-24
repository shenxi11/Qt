#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QLabel>
#include"cauclate.h"
#include"plant.h"
#include"zombies.h"
#include"bullet.h"
#include<vector>
#include<list>
#include <QMouseEvent>
#include<QPoint>
#include<QSoundEffect>
#include<QRect>
#include<QMediaPlayer>
#include<QAudioOutput>
#include"media.h"
#include<QThreadPool>
#include<QMovie>
#include"gifplayer.h"
#include"sun.h"
#include<QVBoxLayout>
#include"chooseplant.h"
#include"musicplayer.h"
#include"shovel.h"
#include"hole.h"
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:


    Widget(QWidget *parent = nullptr);
    ~Widget();

    //用于展示贴图
    void view(QLabel*a,QString url,bool isBoom,int index);

    //初始化植物信息
    void initPlants();

    //初始化僵尸信息
    void initZombies();

    //初始化子弹信息
    void initBullet();

    //初始化选择植物卡片
    void initChoose();
    void  initCHOOSE();

    //初始化格子
    void initmap();

    void initShovel();


    void sound(QAudioOutput*a,QMediaPlayer*b,QString url);


    void initCar();

    bool searchRect(QPoint p);

    void viewSun(Sun*a,QString urll);

    //查找植物攻击范围内是否有僵尸
    bool searchZombies(Zombies*zz,Plant*pp);

    //更新下标
    void renewZombieIndex();

    void renewBulletsIndex();

    void renewPlantIndex();
    //

    void zombiesDie();

    float qfsind(float x);


        protected:


        public slots:


        //用于移动贴图
        void timevent(QLabel*&b,double a,bool flag);

    //定时器事件
    void timerEvent(QTimerEvent*t);

    //    void setNum(int y);

    void setSunNum(int d,bool flag);

    void backToMenu();

signals:
    void CabageMove(int index,float x);

    void CabageShot(int index);

    void Cabage_huifu(int index);

    void destruct(int index);

    void destruct1(int index);

    void ShotMode();

    void stopMEDIA();

    void shooting(int index);

    void stopShooting(int index);

    void stopEAT(int index);

    void eatMUSIC(int index);

    //    void numchanged(int*Zombienum);

    void musiC(QMediaPlayer*p);

    void MU(int index);

    void mu(int index);

    void menu();

    void send(QAudioOutput*a,QMediaPlayer*b,QString url);

    void die(int index);

    void Car(int y);

    void sunNumChanged(int num);

    //植物进入冷却
    void CD();

    void gameOver(bool win);

private:
    Ui::Widget *ui;

    int place=-1;

    Media*media;

    int CCP=0;

    QLabel *po;

    QRect rect;

    QRect rect1;

    QPoint startPos;



    vector<GifPlayer*>diezombie;

    //背景音乐
    MusicPlayer*backMusic;

    //铲子
    Shovel*shovel;



    //当前阳光值
    int sunNum=150;

    //阳光图片
    vector<Sun*>Sun1;
    vector<Sun*>Sun2;

    //所有植物的信息
    vector<Plant*>plants;

    //所有僵尸的信息
    vector<Zombies*>zombies;

    //所有植物子弹的信息
    vector<Bullet*>bullet;

    //子弹贴图

    vector<Bullet*>bullets;


    //僵尸列表
    vector<Zombies*>zombie;

    //植物列表
    vector<Plant*>plant;

    //可选植物列表
    vector<choosePlant*>ChoosePlant;

    vector<QLabel*>car;

    bool carMove[5];

    vector<Hole*>holes;

    //表示某个格子上是否有植物，false代表没有
    bool map[10][6];

    //    int ZombieNum[5]={0};

    int id1;
    int id2;
    int id3;
    int id4;
    int id5;
    int id6;
    int id7;
    int id8;

};

#endif // WIDGET_H
