#include "media.h"
#include<QDebug>
Media::Media(QObject *parent)
    : QObject{parent},QRunnable()
{
    setAutoDelete(false);
}
void Media::rec(QAudioOutput*a,QMediaPlayer*b,QString url,bool flag){
    this->audioOutput=a;
    this->player=b;
    this->URL=url;
    this->flag=flag;



}
void Media::deal(){
    player->stop();
    player->play();

}

void Media::playMedia(){
    emit Play();
}
void Media::stopMedia(){
    this->player->stop();
}
void Media::run(){


    this->player->setAudioOutput(this->audioOutput);
    this->audioOutput->setVolume(70);
    this->player->setSource(QUrl(this->URL));
    connect(this, &Media::Play,this,&Media::deal, Qt::AutoConnection);

}
Media::~Media(){
    delete player;
    delete audioOutput;
}
