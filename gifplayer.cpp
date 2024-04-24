#include "gifplayer.h"
#include<QDebug>
GifPlayer::GifPlayer()=default;

GifPlayer::GifPlayer(QString gifPath, QLabel *label){
    this->label=label;
    this->movie = new QMovie(gifPath);
    this->label->setMovie(movie);

    connect(movie,&QMovie::frameChanged,[=](int frameNumber){
        if(frameNumber==movie->frameCount()-1){
            onFinished();
        }
    });
}
void GifPlayer::setDieURL(QString dieURL){
    disconnect(movie,&QMovie::frameChanged,this,nullptr);
    delete movie;
    this->movie=new QMovie(dieURL);
    this->label->clear();
    this->label->setMovie(movie);
    connect(movie,&QMovie::frameChanged,[=](int frameNumber){
        if(frameNumber==movie->frameCount()-1){
            onFinished();
        }
    });
}
void GifPlayer::start() {
    movie->start();
    label->show();
    //qDebug()<<"倒地";
}

void GifPlayer::LabelMove(int x,int y){
    label->move(x,y);
}
int GifPlayer::getWidth(){
    return label->width();
}
void GifPlayer::onFinished() {
    emit destruct(Index);
    movie->setPaused(true);
}
QLabel*GifPlayer::getLabel(){
    return this->label;
}
GifPlayer::~GifPlayer(){
    delete label;
    delete movie;

}
