#include "hole.h"

Hole::~Hole(){
    delete this->time1;
}
void Hole::view(QString url){
    QMovie*movie=new QMovie(url);
    this->setMovie(movie);
    movie->start();
    this->show();
}
void Hole::setX(int X){
    this->X=X;
}
void Hole::destruct(){
    emit des(this->X,this->Y);
}
void Hole::setY(int Y){
    this->Y=Y;
}

int Hole::getX(){
    return this->X;
}

int Hole::getY(){
    return this->Y;
}
