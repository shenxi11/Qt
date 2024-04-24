#include "zombies.h"

Zombies::Zombies()=default;

Zombies::Zombies(int HP,int ATK,QString URL,QString eatURL,QString dieURL)
{
    this->HP=HP;
    this->ATK=ATK;
    this->URL=URL;
    this->eatURL=eatURL;
    this->dieURL=dieURL;
}
Zombies::Zombies(Zombies*b){
    this->HP=b->getHP();
    this->ATK=b->getATK();
    this->URL=b->getURL();
    this->eatURL=b->getEatURL();
    this->dieURL=b->getDieURL();
    op=new QMediaPlayer;

    QAudioOutput*uq=new QAudioOutput;

    a=new Media();

    a->rec(uq,op,"qrc:/music/eat1.wav",true);



    QThreadPool::globalInstance()->start(a);

    connect(this,&Zombies::eatMusic,a,&Media::playMedia, Qt::AutoConnection);

}
void Zombies::setDieURL(QString dieURL){
    this->dieURL=dieURL;
}
void Zombies::setIndex(int index){
    this->index=index;
}
void Zombies::EATmusic(int index){
    if(this->index==index){
        emit eatMusic();
    }
}
void Zombies::stopEat(int index){
    if(this->index==index){
        this->op->stop();
    }
}
int Zombies::getIndex(){
    return this->index;
}

int Zombies::getY(){
    return this->y;
}
int Zombies::getHP(){
    return this->HP;
}
QString Zombies::getDieURL(){
    return this->dieURL;
}
int Zombies::getATK(){
    return this->ATK;
}
void Zombies::be_attack(int atk){
    this->HP-=atk;
}
QString Zombies::getURL(){
    return this->URL;
}
QString Zombies::getEatURL(){
    return this->eatURL;
}
void Zombies::sety(int num){
    this->y=num;
}
void Zombies::minusx(int num){
    this->x-=num;
}
bool Zombies::getZombiMove(){
    return this->zombiemove;
}

int Zombies::getZombieInt(){
    return this->zombieint;
}

void Zombies::setZombieMove(bool flag){
    this->zombiemove=flag;
}

void Zombies::setZombieInt(int zombieint){
    this->zombieint=zombieint;
}

QLabel*Zombies::getLabel(){
    return this->label;
}

void Zombies::setLabel(QLabel*a){
    this->label=a;
}
bool Zombies::getIfCome(){
    return this->ifCome;
}
void Zombies::setIfCome(bool flag){
    this->ifCome=flag;
}
Zombies::~Zombies(){
    qDebug()<<'die';
    delete label;
    delete a;

}

