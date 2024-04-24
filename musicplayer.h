#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include<QThread>
#include<QMediaPlayer>
#include<QAudioOutput>

class MusicPlayer:public QThread
{
    Q_OBJECT
public:
    MusicPlayer();

    ~MusicPlayer();
protected:
    void run() override;

private:
    QMediaPlayer*player;

    QAudioOutput*audioOutput;
};

#endif // MUSICPLAYER_H
