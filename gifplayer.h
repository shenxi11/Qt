#ifndef GIFPLAYER_H
#define GIFPLAYER_H

#include <QObject>
#include<QMovie>
#include<QLabel>
class GifPlayer : public QObject{
    Q_OBJECT
public:
    GifPlayer();

    GifPlayer(QString gifPath, QLabel *label);

    void start();

    void LabelMove(int x,int y);

    int getWidth();

    QLabel*getLabel();


    int Index;

    ~GifPlayer();

    void setDieURL(QString dieURL);
signals:
    void destruct(int index);

private slots:
    void onFinished();

private:
    QMovie *movie;
    QLabel *label;

};


#endif // GIFPLAYER_H
