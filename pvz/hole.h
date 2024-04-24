#ifndef HOLE_H
#define HOLE_H

#include <QObject>
#include<QLabel>
#include<QMovie>
#include<QTimer>
class Hole:public QLabel
{
    Q_OBJECT
public:
    Hole(QWidget *parent = nullptr):QLabel(parent){
        time1=new QTimer();
        time1->setInterval(3000);
        connect(time1,SIGNAL(timeout()),this,SLOT(destruct()));
        time1->setSingleShot(true);
        time1->start();
    }

    void view(QString url);

    void setX(int X);

    void setY(int Y);

    int getX();

    int getY();

    ~Hole();
private slots:
    void destruct();
signals:
    void des(int X,int Y);
private:
    int X;
    int Y;
    QTimer*time1;
};

#endif // HOLE_H
