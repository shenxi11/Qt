#ifndef CAUCLATE_H
#define CAUCLATE_H

#include <QObject>
#include<QRunnable>
#include<QThread>
class Cauclate:public QThread
{
    Q_OBJECT
public:
    Cauclate();

    float qfsind(float x);

protected:
    void run()override;

public slots:
    void rec(float x);

    void SIN(float x);
signals:
    void MOVE(float x);

    void cau(float x);

private:
    const float hollyst = 0.017453292519943295769236907684886;

    bool isPlant;


};

#endif // CAUCLATE_H
