#ifndef SHOVEL_H
#define SHOVEL_H

#include <QObject>
#include<QLabel>
#include<QPoint>
#include<QMouseEvent>
#include<QMovie>
class Shovel:public QLabel
{
    Q_OBJECT
public:
    Shovel(QPoint pos,QWidget *parent = nullptr);

    void view(QString url);
signals:
        void clearPlants(QPoint point);

protected:
    void mousePressEvent(QMouseEvent *event) override ;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint startPos;

    bool moveAble=false;
};

#endif // SHOVEL_H
