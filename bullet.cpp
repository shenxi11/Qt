#include "bullet.h"

Bullet::Bullet()=default;

Bullet::Bullet(int v,int length,bool isPULT)
{
    this->v=v;
    this->length=length;
    this->isPult=isPULT;
}
Bullet::Bullet(Bullet*b){

//    qDebug()<<"gouzao";

//    this->url=b->getURL();
//    this->v=b->getV();
//    this->length=b->getLength();
//    this->isPult=b->getPult();

//    if(b->getPult()==true){
//        cc=new Cauclate;

////        cc->start();

//        QThreadPool::globalInstance()->start(cc);

//      //  connect(this,&Bullet::MOve,cc,&Cauclate::rec,Qt::AutoConnection);

//        connect(this,&Bullet::MOve,cc,&Cauclate::rec);

//        connect(cc,&Cauclate::MOVE,this,[=](float x){

//                emit MoveTo(x);
//            },Qt::AutoConnection);


//    }


//    QMediaPlayer*op=new QMediaPlayer;

//    QAudioOutput*uq=new QAudioOutput;

//    a=new Media();

//    a->rec(uq,op,"qrc:/music/hit_2.wav",false);

//    QThreadPool::globalInstance()->start(a);

//    connect(this,&Bullet::playMusic,a,&Media::playMedia, Qt::AutoConnection);
}
Bullet*& Bullet::operator=( Bullet*&k){
    return k;
}

Bullet::~Bullet(){
//    if(this->isPult==true){
//        delete cc;
//    }
    delete this->label;

    qDebug()<<"xigou";

}
void Bullet:: Bullet_MOve(int index,float x){
    if(this->number==index){
       // qDebug()<<'k';
    emit MOve(x);
    }
}
void Bullet::setStartPos(QPoint pos){
    this->startPos=pos;
}
QPoint Bullet::getStartPos(){
    return this->startPos;
}
void Bullet::setY(int y){
    this->Y=y;
}

int Bullet::getY(){
    return this->Y;

}

void Bullet::setPult(bool pult){

    this->isPult=pult;
}

bool Bullet::getPult(){
    return this->isPult;
}
void Bullet::setPlantsNumber(int Number){
    this->plantsNumber=Number;
}
int Bullet::getPlantsNumber(){
    return this->plantsNumber;
}
void Bullet::setNumber(int index){
    this->number=index;
}

int Bullet::getIndex(){
    return this->number;
}
void Bullet::setURL(QString url){
    this->url=url;
}
bool Bullet::getBulletAttack(){
    return this->bulletAttack;
}

QString Bullet::getURL(){
    return this->url;
}
int Bullet::getV(){
    return this->v;
}

int Bullet::getLength(){
    return this->length;
}
QLabel*Bullet::getLabel(){
    return this->label;
}
void Bullet::setATK(int atk){
    this->ATK=atk;
}
int Bullet::getATK(){
    return this->ATK;
}
void Bullet::setBulletAttack(bool attack){
    this->bulletAttack=attack;
}
void Bullet::setLabel(QLabel*a){
    this->label=a;
}
