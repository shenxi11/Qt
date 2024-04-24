#include "musicplayer.h"

MusicPlayer::MusicPlayer()
{

}
void MusicPlayer::run(){
    player=new QMediaPlayer;
    audioOutput=new QAudioOutput;
    this->player->setAudioOutput(this->audioOutput);
    this->audioOutput->setVolume(70);
    this->player->setSource(QUrl("qrc:/music/menu1.ogg"));
    this->player->setLoops(-1);
    this->player->play();
}
MusicPlayer::~MusicPlayer(){
    delete this->player;
    delete this->audioOutput;
}
