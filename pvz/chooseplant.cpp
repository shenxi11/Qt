#include "chooseplant.h"

choosePlant::choosePlant()=default;


void choosePlant::setNum(int num){
    this->num=num;
}
void choosePlant::view(QString url){

    QMovie*movie=new QMovie(url);
    this->setMovie(movie);
    //a->setScaledContents(true);
    movie->start();
    this->show();
}
int choosePlant::getNum(){
    return this->num;
}
void choosePlant::setMove(bool flag){
    this->moveAble=true;
}

void choosePlant::moveBack(){
    this->move(startPos);
}

void choosePlant:: mousePressEvent(QMouseEvent *event){
    if(this->ifInCD==false&&event->type()==QEvent::MouseButtonPress){
        //emit choose(event->pos());
        this->moveAble=true;
        //qDebug()<<"choose";
    }
    QLabel::mousePressEvent(event);
}

void choosePlant::inCD(){
    this->moveAble=false;
    this->ifInCD=true;
}
void choosePlant::mouseReleaseEvent(QMouseEvent *event){
    if(this->moveAble==true&&this->ifInCD==false){
        if(event->type()==QEvent::MouseButtonRelease){
            emit makePlants(mapToParent(event->pos()));
            //qDebug()<<"make";
        }
    }QLabel::mouseReleaseEvent(event);
}
void choosePlant::setIfInCD(bool flag){
    this->ifInCD=flag;
}
void choosePlant::mouseMoveEvent(QMouseEvent *event){

    if(event->type()==QEvent::MouseMove){
        if(this->ifInCD==false&&this->moveAble==true){

            this->move(mapToParent(event->pos()));
            //qDebug()<<event->pos();
        update();
        }
        //qDebug()<<"移动";
    }
    QLabel::mouseMoveEvent(event);
}
