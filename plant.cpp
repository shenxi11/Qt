#include "plant.h"

Plant::Plant()=default;
Plant::Plant(int number,int HP,int ATK,int times,int isATK,QString url,QString chooseUrl,QString bulletURL,int sunCost,int ATKarea,QString GraychooseUrl)
{
    this->number=number;
    this->HP=HP;
    this->ATK=ATK;
    this->times=times;
    this->isATK=isATK;
    this->url=url;
    this->chooseUrl=chooseUrl;
    this->bulletURL=bulletURL;
    this->sunCost=sunCost;
    this->ATKarea=ATKarea;
    this->GraychooseUrl=GraychooseUrl;
}
Plant::Plant(Plant*a){
    this->number=a->getNumber();
    this->HP=a->getHP();
    this->ATK=a->getATK();
    this->times=a->getTimes();
    this->isATK=a->getIsAtk();
    this->url=a->getURL();
    this->chooseUrl=a->getChooseURL();
    this->bulletURL=a->getBulletURL();
    this->sunCost=a->getSunCost();
    this->ATKarea=a->getATKarea();
    this->GraychooseUrl=a->getGraychooseUrl();
    shotMode();
    if(this->isATK==1||this->isATK==5){
        QMediaPlayer*op=new QMediaPlayer;

        QAudioOutput*uq=new QAudioOutput;

        aa=new Media();

        aa->rec(uq,op,"qrc:/music/hit_2.wav",false);

        QThreadPool::globalInstance()->start(aa);

        connect(this,&Plant::playMusic,aa,&Media::playMedia, Qt::AutoConnection);
    }

}
void Plant::Cabage(int index,float x){
    if(this->index==index){
        emit MOve(x);
    }
}
void Plant::setBoomURL(QString BoomURL){
    this->BoomURL=BoomURL;
}
QString Plant::getBoomURL(){
    return this->BoomURL;
}
QString Plant::getGraychooseUrl(){
    return this->GraychooseUrl;
}
int Plant::getATKarea(){
    return this->ATKarea;
}
void Plant::shot(){
    //qDebug()<<'8';
    emit Shot();
}
void Plant::shot1(int index){
    if(this->index==index){
        //qDebug()<<'q';
        emit Shot();
    }
}
void Plant::setCount1(int Count1){
    this->Count1=Count1;
}

int Plant::getCount1(){
    return this->Count1;
}
bool Plant::getIsready(){
    return this->isready;
}
void Plant::readyToBoom(){
    this->isready=true;
    emit readyBoom();
}
void Plant::shotMode(){
    switch(this->isATK){
    case 0:
        time1=new QTimer();
        time1->setInterval(10000);
        connect(time1,SIGNAL(timeout()),this,SLOT(makeSun()), Qt::AutoConnection);
        time1->start();
        break;
    case 1:
        time1=new QTimer();
        // time1->setInterval(1400);
        connect(time1,SIGNAL(timeout()),this,SLOT(shot()), Qt::AutoConnection);

        break;

    case 4:
        time1=new QTimer();
        time1->setInterval(1000);
        connect(time1,SIGNAL(timeout()),this,SLOT(readyToBoom()),Qt::AutoConnection);
        time1->setSingleShot(true);
        time1->start();
        break;

    }

}
void Plant::setIndex(int index){
    this->index=index;
}

int Plant::getIndex(){
    return this->index;
}
void Plant::stopShot(int index){
    if(this->index==index){
        //qDebug()<<"STOP";
        if(this->isATK==1)
        this->time1->stop();

        if(this->isATK==5){
            emit stopAttack(this->index);
        }
    }
}
void Plant::hit_music(int index){
    if(index==this->index)
        emit playMusic();
}
void Plant::beginShoot(int index){
    if(this->index==index){
        if(this->isATK==1){
            this->time1->start(1000);
        }else if(this->isATK==5){
            //this->time1->start(1150);
            emit attack(this->index);
        }
    }
}
void Plant::setTimer1(QTimer*pi){
    this->time1=pi;
}
void Plant::setIsShooting(bool flag){
    this->isShooting=flag;
}

bool Plant::getIsShooting(){
    return this->isShooting;
}

bool Plant::getIfCD(){
    return this->ifCD;
}
void Plant::setCD(){
    this->ifCD=false;
}
void Plant::setcd(){
    this->ifCD=true;
    emit huifu(this->number);
}
void Plant::inCD(){
    tt=new QTimer();
    connect(tt,SIGNAL(timeout()),this,SLOT(setcd()), Qt::AutoConnection);
    tt->setSingleShot(true);
    tt->start(this->times*1000);
}
void Plant::makeSun(){
    emit MakeSun();
}
int Plant::getSunCost(){
    return this->sunCost;
}
QString Plant::getBulletURL(){
    return this->bulletURL;
}
void Plant::setXY(int x,int y){
    this->X=x;
    this->Y=y;
}
int Plant::getX(){
    return this->X;
}
int Plant::getY(){
    return this->Y;
}
QString Plant::getChooseURL(){
    return this->chooseUrl;
}
QString Plant::getURL(){
    return this->url;
}
int Plant::getHP(){
    return this->HP;
}

int Plant::getATK(){
    return this->ATK;
}
int Plant::getIsAtk(){
    return this->isATK;
}
int Plant::getTimes(){
    return this->times;
}
void Plant::be_attack(int atk){
    this->HP-=atk;
}
int Plant::getNumber(){
    return this->number;
}
Bullet*Plant::getBullet(){
    return this->bullets;
}
void Plant::setBullet(Bullet*a){
    this->bullets=a;
    //this->bullets.push_back(a);
}
void Plant::outBullet(){
    //this->bullets.pop_front();
}
QLabel*Plant::getLabel(){
    return this->label;
}
Plant::~Plant(){
    delete label;

    if(this->isATK==1||this->isATK==5)
        delete aa;

}
void Plant::setLabel(QLabel*a){
    this->label=a;
}
