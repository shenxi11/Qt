#ifndef SUN_H
#define SUN_H

#include <QObject>
#include<QMovie>
#include<QLabel>
#include<QMouseEvent>
class Sun : public QLabel{
    Q_OBJECT
public:
    Sun();
    Sun(int num,QWidget *parent = nullptr):QLabel(parent){
        this->num=num;
    }

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override ;
private:
    int num;
};
#endif // SUN_H

