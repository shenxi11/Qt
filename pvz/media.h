#ifndef MEDIA_H
#define MEDIA_H

#include<QMediaPlayer>
#include<QRunnable>
#include<QThread>
#include<QAudioOutput>
class Media:public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit Media(QObject *parent = nullptr);

    ~Media();

    void rec(QAudioOutput*a,QMediaPlayer*b,QString url,bool flag);



    void playMedia();

    void stopMedia();

private slots:
    void deal();
protected:
       void run()override;

signals:
    void Play();

private:
    QAudioOutput*audioOutput;

    QMediaPlayer*player;

    QString URL;

    //是否循环播放
    bool flag;
};

#endif // MEDIA_H
