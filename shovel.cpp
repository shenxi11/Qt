#include "shovel.h"

Shovel::Shovel(QPoint pos,QWidget *parent):QLabel(parent){
    startPos=pos;
};
void Shovel::mousePressEvent(QMouseEvent *event) {
    if(event->type()==QMouseEvent::MouseButtonPress){
        this->moveAble=true;
    }
    QLabel::mousePressEvent(event);
}

void Shovel::mouseReleaseEvent(QMouseEvent *event){
    if(event->type()==QMouseEvent::MouseButtonRelease&&this->moveAble==true){
        QPoint pos(event->pos().x()-(this->width()/2),event->pos().y()-(this->height()/2));
        emit clearPlants(mapToParent(pos));
        this->move(startPos);
        this->moveAble=false;
    }
    QLabel::mouseReleaseEvent(event);
}

void Shovel::view(QString url){
    QMovie*movie=new QMovie(url);
    this->setMovie(movie);
    movie->start();
    this->show();
}
void Shovel::mouseMoveEvent(QMouseEvent *event){
    if(event->type()==QMouseEvent::MouseMove&&this->moveAble==true){
        QPoint pos(event->pos().x()-(this->width()/2),event->pos().y()-(this->height()/2));
        this->move(mapToParent(pos));
    }
    QLabel::mouseMoveEvent(event);
}
