#include "widget.h"
#include "ui_widget.h"
#include<QTimer>
#include<QDebug>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include<QRandomGenerator>
#include<QPushButton>
#include<cmath>
#include<QMessageBox>
#define PI 3.1415


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->button->setFlat(true);
    ui->button->setStyleSheet("QPushButton{border:none;background:transparent;}");
    ui->stackedWidget->setCurrentIndex(0);
    //qDebug()<<this->;



    //qDebug()<<qfsind(100.0);

    QPoint topleft(365,10);
    QPoint bottom(935,110);
    QPoint Topleft(365,210);
    QPoint Bottom(1135,710);
    rect.setTopLeft(topleft);
    rect.setBottomRight(bottom);
    rect1.setTopLeft(Topleft);
    rect1.setBottomRight(Bottom);

    initPlants();
    initZombies();
    initBullet();

    initChoose();

//        QAudioOutput*AA=new QAudioOutput();
//        QMediaPlayer*PP=new QMediaPlayer();
//        Media*k=new Media();
//        k->rec(AA,PP,"qrc:/music/menu1.ogg",true);


    connect(ui->button,&QPushButton::clicked,[=](){
        sunNum=150;
        ui->stackedWidget->setCurrentIndex(1);
        ui->sun->setText(QString::number(sunNum));
        connect(this,&Widget::Car,[=](int yy){
            for(int i=0;i<car.size();i++){
                if((car[i]->y()-210)/100==yy){
                    carMove[yy]=true;
                }
            }
        });
        //emit menu();



        initmap();
        initCHOOSE();
        initCar();
        initShovel();

        //QThreadPool::globalInstance()->start(k);
        backMusic=new MusicPlayer;

        backMusic->start();


        for(int i=0;i<plants.size();i++){
            plants[i]->inCD();
        }

        id1=startTimer(5000);
        id2=startTimer(1400);
        id3=startTimer(30,Qt::PreciseTimer);
        id4=startTimer(50,Qt::PreciseTimer);
        id5=startTimer(1000,Qt::PreciseTimer);
        id6=startTimer(15,Qt::PreciseTimer);
        id7=startTimer(10000);
    });



    //    connect(this,&Widget::menu,k,&Media::playMedia, Qt::AutoConnection);

    // connect(this,&Widget::stopMEDIA,k,&Media::stopMedia, Qt::AutoConnection);

    connect(this,&Widget::gameOver,[=](bool flag){
        po=new QLabel(this);

        po->move(100,20);
        //qDebug()<<"失败";
        view(po,":/new/play/play/fail.png",false,-1);
        killTimer(id1);
        killTimer(id2);
        killTimer(id3);
        killTimer(id4);
        killTimer(id5);
        killTimer(id6);
        killTimer(id7);
        QTimer*a=new QTimer();
        connect(a,SIGNAL(timeout()),this,SLOT(backToMenu()), Qt::AutoConnection);
        a->setSingleShot(true);
        a->start(5000);

        // emit stopMEDIA();
        this->backMusic->exit();
        this->backMusic->wait();
        delete backMusic;

    });


}
void Widget:: backToMenu(){
    ui->stackedWidget->setCurrentIndex(0);
    int index;

    delete shovel;
    ////   index=diezombie.size();
    ////    for(int i=0;i<index;i++){
    ////        GifPlayer*q=diezombie.back();
    ////        diezombie.pop_back();
    ////        q->deleteLater();
    ////    }
    index=Sun1.size();
    for(int i=0;i<index;i++){
        Sun*q=Sun1.back();
        Sun1.pop_back();

        q->deleteLater();
    }

    index=Sun2.size();
    for(int i=0;i<index;i++){
        Sun*q=Sun2.back();
        Sun2.pop_back();
        q->deleteLater();
    }
    index=holes.size();
    for(int i=0;i<index;i++){
        Hole*q=holes.back();
        holes.pop_back();
        q->deleteLater();
    }

    ////    index=plants.size();
    ////    for(int i=0;i<index;i++){
    ////        Plant*q=plants.back();
    ////        plants.pop_back();
    ////         q->deleteLater();
    ////    }

    //    index=zombies.size();
    //    for(int i=0;i<index;i++){
    //        Zombies*q=zombies.back();
    //        zombies.pop_back();
    //         q->deleteLater();
    //    }

    ////    index=bullet.size();
    ////    for(int i=0;i<index;i++){
    ////        Bullet*q=bullet.back();
    ////        bullet.pop_back();
    ////         q->deleteLater();
    ////    }

    index=bullets.size();
    for(int i=0;i<index;i++){
        Bullet*q=bullets.back();
        bullets.pop_back();
        q->deleteLater();
    }


    index=zombie.size();
    for(int i=0;i<index;i++){
        Zombies*q=zombie.back();
        zombie.pop_back();
        q->deleteLater();
    }

    index=plant.size();
    for(int i=0;i<index;i++){
        Plant*q=plant.back();
        plant.pop_back();
        q->deleteLater();
    }

    index=ChoosePlant.size();
    for(int i=0;i<index;i++){
        ChoosePlant[i]->clear();
    }


    index=car.size();
    for(int i=0;i<index;i++){
        QLabel*q=car.back();
        car.pop_back();
        q->deleteLater();
    }
    po->deleteLater();

    emit stopMEDIA();
}
void Widget::timerEvent(QTimerEvent*t){
    int id=t->timerId();
    if(id==id1){
        //生成僵尸
        //qDebug()<<QThreadPool::globalInstance()->activeThreadCount();
        int y=QRandomGenerator::global()->bounded(0, 5);
        int kind=QRandomGenerator::global()->bounded(0, 3);
        //qDebug()<<y<<" "<<kind;
        Zombies*w=new Zombies(zombies[kind]);
        zombie.push_back(w);
        //setNum(y);
        w->setIfCome(false);
        w->sety(y);
        w->setIndex(zombie.size()-1);
        QLabel*a=new QLabel(this);
        a->resize(100,150);
        w->setLabel(a);
        w->setZombieMove(false);
        w->setZombieInt(0);
        GifPlayer*play;
        QLabel*p=new QLabel(this);
        play=new GifPlayer(w->getDieURL(),p);
        diezombie.push_back(play);
        connect(play,&GifPlayer::destruct,[=](int index){
            for(vector<GifPlayer*>::iterator it=diezombie.begin();it!=diezombie.end();++it){
                if((*it)->Index==index){
                    GifPlayer*p=*it;
                    diezombie.erase(it);
                    --it;
                    //delete p;
                    p->deleteLater();
                    break;
                    //qDebug()<<"播放完毕";
                }
            }

        });
        connect(this,&Widget::eatMUSIC,w,&Zombies::EATmusic, Qt::AutoConnection);
        connect(this,&Widget::stopEAT,w,&Zombies::stopEat, Qt::AutoConnection);

        a->move(this->width(),y*100+160);
        view(a,w->getURL(),false,-1);
    }
    else if(id==id3){
        //        if(CCP<=2){
        //            CCP++;
        //            if(CCP<=1){
        //                emit menu();
        //            }
        //        }
        //僵尸受到子弹攻击
        for(vector<Bullet*>::iterator it=bullets.begin();it!=bullets.end();++it){
            if(!(*it)->getPult()){
                QLabel*k=(*it)->getLabel();
                timevent(k,5,true);
            }else{
                //QLabel*k=(*it)->getLabel();
                int mind=114514;
                Zombies*q;
                for(int i=0;i<zombie.size();i++){
                    if(zombie[i]->getY()==(*it)->getY()){

                        if(mind>=zombie[i]->getLabel()->x()-(*it)->getStartPos().x()){
                            mind=zombie[i]->getLabel()->x()-(*it)->getStartPos().x();
                            q=zombie[i];
                        }
                    }
                }
                if(mind==114514){
                    (*it)->setBulletAttack(true);
                }

                else if((*it)->getLabel()->x()<q->getLabel()->x()){

                    (*it)->dx+=5;
                    emit CabageMove((*it)->getIndex(),180.0*(float)((*it)->getLabel()->x()-(*it)->getStartPos().x())/(float)(q->getLabel()->x()-(*it)->getStartPos().x()));

                }
                else if((*it)->getLabel()->x()>=q->getLabel()->x()){
                    (*it)->setBulletAttack(true);
                    q->be_attack(50);
                    emit MU((*it)->getPlantsNumber());
                    qDebug()<<q->getHP();
                }
                //  qDebug()<<(*it)->getLabel()->x()<<' '<<mind;

            }
        }
        for(int i=0;i<(int)bullets.size();i++){
            if(!bullets[i]->getPult()){
                for(int j=0;j<(int)zombie.size();j++){
                    if(bullets[i]->getLabel()->x()>=zombie[j]->getLabel()->x()&&bullets[i]->getLabel()->y()>=zombie[j]->getLabel()->y()&&bullets[i]->getLabel()->y()<=zombie[j]->getLabel()->y()+zombie[j]->getLabel()->height()&&bullets[i]->getLabel()->x()<zombie[j]->getLabel()->x()+zombie[j]->getLabel()->width()){
                        zombie[j]->be_attack(bullets[i]->getATK());
                        bullets[i]->setBulletAttack(true);
                        emit MU(bullets[i]->getPlantsNumber());
                        //QLabel*PO=new QLabel(this);

                        break;
                    }
                }
            }
        }

        int p=0;
        for(vector<Bullet*>::iterator it=bullets.begin();it!=bullets.end();++it,++p){
            if((*it)->getBulletAttack()==true){
               QLabel*hit=new QLabel(this);
                hit->move((*it)->getLabel()->pos());
                view(hit,":/plant/PeaBulletHit1.gif",true,-12);
                Bullet*bb=(*it);
                bullets.erase(it);
                --it;
                delete bb;
            }
        }
        renewBulletsIndex();
        zombiesDie();
        renewZombieIndex();

    }else if(id==id4){
        if(Sun1.size()>0){
            for(int i=0;i<Sun1.size();i++){
                Sun1[i]->move(Sun1[i]->x(),Sun1[i]->y()+1);
                update();
            }
        }
        if(zombie.size()>0){
            for(int i=0;i<(int)zombie.size();++i){

                for(int j=0;j<(int)plant.size();++j){
                    if(zombie[i]->getY()==plant[j]->getY()&&zombie[i])
                        if(plant[j]->getHP()>0&&zombie[i]->getLabel()->x()>=plant[j]->getLabel()->x()&&zombie[i]->getLabel()->x()<=plant[j]->getLabel()->x()+plant[j]->getLabel()->width()&&plant[j]->getLabel()->y()>zombie[i]->getLabel()->y()&&plant[j]->getLabel()->y()<zombie[i]->getLabel()->y()+zombie[i]->getLabel()->height()){

                            zombie[i]->setZombieMove(true);
                            break;
                        }
                }
                if(!zombie[i]->getZombiMove()){
                    QLabel*jk=zombie[i]->getLabel();
                    timevent(jk,1,false);
                    if(zombie[i]->getLabel()->x()<=330){
                        emit gameOver(false);
                    }
                    if(zombie[i]->getLabel()->x()<=365){
                        for(int p=0;p<(int)car.size();p++){
                            if((car[p]->y()-210)/100==zombie[i]->getY()&&carMove[(car[p]->y()-210)/100]==false){
                                emit Car(zombie[i]->getY());
                            }
                        }
                    }else if(zombie[i]->getLabel()->x()<=1135&&zombie[i]->getIfCome()==false){
                        //setNum(zombie[i]->getY());
                        zombie[i]->setIfCome(true);
                    }
                }
            }

            ///////查找是否有僵尸进入某植物的攻击范围内

            for(int i=0;i<plant.size();i++){
                if(plant[i]->getIsAtk()==1){
                    int count=0;
                    for(int j=0;j<zombie.size();j++){
                        if(plant[i]->getY()==zombie[j]->getY()&&searchZombies(zombie[j],plant[i])){
                            count++;
                        }
                    }
                    if(count>0&&!plant[i]->getIsShooting()){
                        //qDebug()<<"开始射击";
                        plant[i]->setIsShooting(true);
                        emit shooting(i);

                    }
                }else if(plant[i]->getIsAtk()==5){
                    int count1=0;
                    for(int j=0;j<zombie.size();j++){
                        if(plant[i]->getY()==zombie[j]->getY()&&searchZombies(zombie[j],plant[i])){
                            count1++;
                        }
                    }
                    if(count1>0&&!plant[i]->getIsShooting()){
                        // qDebug()<<"开始射击";
                        plant[i]->setIsShooting(true);
                        emit shooting(i);

                    }
                }
            }

            /////////
        }
    }else if(id==id5){
        //僵尸吃植物
        for(int i=0;i<zombie.size();i++){
            if(zombie[i]->getZombiMove()&&zombie[i]->getZombieInt()==0){

                zombie[i]->setZombieInt(zombie[i]->getZombieInt()+1);
                zombie[i]->getLabel()->move(zombie[i]->getLabel()->x()-20,zombie[i]->getLabel()->y());
                view(zombie[i]->getLabel(),zombie[i]->getEatURL(),false,-1);
                //emit eatMUSIC(i);

            }
            if(zombie[i]->getZombieInt()==1){
                for(int j=0;j<(int)plant.size();j++){
                    if(plant[j]->getHP()>0&&plant[j]->getY()==zombie[i]->getY()&&zombie[i]->getLabel()->x()>=plant[j]->getLabel()->x()&&zombie[i]->getLabel()->x()<=plant[j]->getLabel()->x()+plant[j]->getLabel()->width()){
                        emit eatMUSIC(i);


                        plant[j]->be_attack(zombie[i]->getATK());

                        //qDebug()<<"植物被攻击,剩余血量为:"<<plant[j]->getHP();
                        if(plant[j]->getHP()<=0){
                            emit stopEAT(i);
                            zombie[i]->setZombieMove(false);
                            zombie[i]->setZombieInt(zombie[i]->getZombieInt()-1);
                            view(zombie[i]->getLabel(),zombie[i]->getURL(),false,-1);

                            break;}
                    }
                }
            }
        }
        for(int i=0;i<zombie.size();i++){
            if(zombie[i]->getZombieInt()==1&&zombie[i]->getZombiMove()==true){
                int count=0;
                for(int j=0;j<plant.size();j++){
                    if(plant[j]->getY()==zombie[i]->getY()&&zombie[i]->getLabel()->x()>=plant[j]->getLabel()->x()&&zombie[i]->getLabel()->x()<=plant[j]->getLabel()->x()+plant[j]->getLabel()->width()){
                        count++;
                        //qDebug()<<plant[j]->getHP();
                    }
                }if(count==0){
                    zombie[i]->setZombieInt(zombie[i]->getZombieInt()-1);
                    zombie[i]->setZombieMove(false);
                    emit stopEAT(i);
                    //zombie[i]->stopEat();
                    view(zombie[i]->getLabel(),zombie[i]->getURL(),false,-1);
                }
            }
        }
        for(vector<Plant*>::iterator it=plant.begin();it!=plant.end();++it){
            if((*it)->getHP()<=0){
                Plant*a=*it;
                plant.erase(it);
                map[a->getX()][a->getY()]=false;
                delete a;

                --it;
            }
        }
        renewPlantIndex();
    }else if(id==id6){
        for(int i=0;i<car.size();i++){
            if(carMove[(car[i]->y()-210)/100]==true ){
                timevent(car[i],5,true);
                for(int j=0;j<zombie.size();j++){
                    if((car[i]->y()-210)/100==zombie[j]->getY()&&car[i]->x()+car[i]->width()>=zombie[j]->getLabel()->x()){
                        //qDebug()<<"僵尸被创";
                        zombie[j]->be_attack(2*zombie[j]->getHP());
                    }
                }
            }
        }
        zombiesDie();
        renewZombieIndex();
        for(vector<QLabel*>::iterator it=car.begin();it!=car.end();++it){
            if((*it)->x()+(*it)->width()>=this->width()){
                QLabel*a=*it;
                carMove[((*it)->y()-210)/100]=false;
                car.erase(it);
                delete a;
                --it;
            }
        }
    }
    else if(id==id7){
        Sun*aa=new Sun(50,this);
        Sun1.push_back(aa);
        aa->move(QRandomGenerator::global()->bounded(365, 500),0);
        viewSun(aa,":/new/play/play/sun.png");
        for(vector<Sun*>::iterator it=Sun1.begin();it!=Sun1.end();++it){
            if((*it)->y()>=this->height()){
                Sun*oo=*it;
                Sun1.erase(it);
                --it;
                oo->close();
                oo->deleteLater();
            }
        }
        connect(aa,&Sun::clicked,[=](){
            setSunNum(50,true);
            for(vector<Sun*>::iterator it=Sun1.begin();it!=Sun1.end();++it){
                if(*it==aa){
                    Sun*oo=*it;
                    Sun1.erase(it);
                    --it;
                    oo->close();
                    oo->deleteLater();
                    break;
                }
            }
        });
    }

}
void Widget::viewSun(Sun*a,QString urll){
    QMovie*movie=new QMovie(urll);
    a->setMovie(movie);
    //a->setScaledContents(true);
    movie->start();
    a->show();
}

void Widget::setSunNum(int b,bool flag){
    if(flag){
        this->sunNum+=b;
    }
    else{
        this->sunNum-=b;
    }
    ui->sun->setText(QString::number(this->sunNum));
}
void Widget::sound(QAudioOutput*a,QMediaPlayer*b,QString url){
    b->setAudioOutput(a);
    a->setVolume(70);
    b->setSource(QUrl(url));
}
void Widget::view(QLabel*a,QString url,bool isBoom,int index){
    QMovie*movie=new QMovie(url);
    a->setMovie(movie);
    //a->setScaledContents(true);

    if(isBoom==false&&index>=0){
       // connect(this,&Widget::CabageShot,plant[index],&Plant::shot1);
        connect(movie,&QMovie::frameChanged,this,[=](int frameNumber){
            if(plant[index]->getIsAtk()==5){
                if(frameNumber==movie->frameCount()-25){
                    emit CabageShot(index);
                }
            }
        });
        connect(this,&Widget::Cabage_huifu,[=](int Index){

            if(index==Index){
                //qDebug()<<"huifu";

                disconnect(movie,&QMovie::frameChanged,this,nullptr);
            }

        });
    }

    if(isBoom==true){
        if(index==-12){
            connect(movie,&QMovie::frameChanged,this,[=](int frameNumber){
                if(frameNumber==movie->frameCount()-1){
                    delete a;
                    disconnect(movie,&QMovie::frameChanged,this,nullptr);
                    //qDebug()<<"ransao";

                }
            });
        }

        else if(index>=0){
            //        a->setScaledContents(true);
            connect(movie,&QMovie::frameChanged,this,[=](int frameNumber){
                if(frameNumber==movie->frameCount()-1){
                    //qDebug()<<"boom";
                    if(plant[index]->getIsAtk()==3)
                        emit destruct(index);
                    else if(plant[index]->getIsAtk()==4){
                        emit destruct1(index);
                    }
                    disconnect(movie,&QMovie::frameChanged,this,nullptr);
                }
            });
        }
    }
    movie->start();
    a->show();
}

bool Widget::searchZombies(Zombies*zz,Plant*pp){
    if(zz->getLabel()->x()>=pp->getLabel()->x()&&min(1135,pp->getLabel()->x()+pp->getLabel()->width()+85*pp->getATKarea())>=zz->getLabel()->x()){
        return true;
    }
    return false;
}
void Widget::timevent(QLabel*&b,double a,bool flag) {
    int X=0;
    if(flag)
        X =b->x() + a;
    else
        X=b->x()-a;
    b->move(X,b->y());
    update();
}
void Widget::initBullet(){
    QFile file(":/pvz/bullet.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file";
        return;
    }QTextStream in(&file);
    // 逐行读取文件
    for (int i = 0; i < 4; ++i) {
        if (in.atEnd()) {
            qDebug() << "File has fewer than 2 lines";
            break;
        }

        // 读取一行
        QString line = in.readLine();

        // 将一行中的数字拆分为字符串列表
        QStringList numbers = line.split(' ');


        // 检查是否有足够的数字
        if (numbers.size() >= 3) {
            Bullet*bullets=new Bullet(numbers[0].toInt(),numbers[1].toInt(),numbers[2].toInt());
            bullet.push_back(bullets);
        } else {
            qDebug() << "Not enough numbers in line " << i + 1;
        }
    }

    // 关闭文件
    file.close();
}

void Widget::initPlants(){
    emit menu();
    QFile file(":/pvz/plants.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file";
        return;
    }QTextStream in(&file);
    // 逐行读取文件
    for (int i = 0; i < 6; ++i) {
        if (in.atEnd()) {
            qDebug() << "File has fewer than 2 lines";
            break;
        }

        // 读取一行
        QString line = in.readLine();

        // 将一行中的数字拆分为字符串列表
        QStringList numbers = line.split(' ');


        // 检查是否有足够的数字
        if (numbers.size() >= 11) {
            Plant*plant1=new Plant(numbers[0].toInt(),numbers[1].toInt(),numbers[2].toInt(),numbers[3].toInt(),numbers[4].toInt(),numbers[5],numbers[6],numbers[7],numbers[8].toInt(),numbers[9].toInt(),numbers[10]);
            plants.push_back(plant1);

        } else {
            qDebug() << "Not enough numbers in line " << i + 1;
        }
    }

    // 关闭文件
    file.close();
}
void Widget::initZombies(){
    QFile file(":/pvz/zombies.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file";
        return;
    }QTextStream in(&file);
    // 逐行读取文件
    for (int i = 0; i < 3; ++i) {
        if (in.atEnd()) {
            qDebug() << "File has fewer than 2 lines";
            break;
        }

        // 读取一行
        QString line = in.readLine();

        // 将一行中的数字拆分为字符串列表
        QStringList numbers = line.split(' ');


        // 检查是否有足够的数字
        if (numbers.size() >= 5) {
            Zombies*zombies1=new Zombies(numbers[0].toInt(),numbers[1].toInt(),numbers[2],numbers[3],numbers[4]);
            zombies.push_back(zombies1);
        } else {
            qDebug() << "Not enough numbers in line " << i + 1;
        }
    }

    // 关闭文件
    file.close();
}
void Widget::initmap(){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            map[i][j]=false;
        }
    }
}
void Widget::initChoose(){
    //    for(int i=0;i<plants.size();i++){
    //        QLabel*q=new QLabel(this);
    //        q->resize(ui->label_4->size());
    //        q->move(ui->label_4->x()+i*ui->label_4->width(),ui->label_4->y());
    //        view(q,plants[i]->getGraychooseUrl());
    //        ChoosePlant.push_back(q);
    //    }


    for(int i=0;i<plants.size();i++){
        QPoint po(ui->label_4->x()+i*ui->label_4->width(),ui->label_4->y());
        choosePlant*qq=new choosePlant(i,po,this);
        qq->resize(ui->label_4->size());
        //        qq->move(ui->label_4->x()+i*ui->label_4->width(),ui->label_4->y());
        qq->moveBack();
        //qq->view(plants[i]->getGraychooseUrl());
        ChoosePlant.push_back(qq);
        connect(plants[i],&Plant::huifu,[=](int index){
            qq->setIfInCD(false);
            qq->view(plants[i]->getChooseURL());
        });
        connect(qq,&choosePlant::makePlants,[=](QPoint pos){
            int cc=0;
            //qDebug()<<"进入";
            if(rect1.contains(pos)){
                //qDebug()<<"生";
                int x=(pos.x()-355)/85;
                int y=(pos.y()-200)/100;
                // qDebug()<<x<<' '<<y;
                //
                if(!map[x][y]&&plants[qq->getNum()]->getSunCost()<=this->sunNum&&plants[qq->getNum()]->getIfCD()){
                    // qDebug()<<"生成"<<qq->getNum();
                    QLabel*q=new QLabel(this);
                    q->move(x*85+365,y*100+210);

                    Plant*a=new Plant(plants[qq->getNum()]);
                    setSunNum(plants[qq->getNum()]->getSunCost(),false);

                    plant.push_back(a);
                    a->setLabel(q);
                    plant.back()->setXY(x,y);
                    map[x][y]=true;
                    a->setIndex(plant.size()-1);
                    if(plants[qq->getNum()]->getIsAtk()==3){
                        view(q,plants[qq->getNum()]->getURL(),true,a->getIndex());
                    }else{
                        view(q,plants[qq->getNum()]->getURL(),true,a->getIndex());
                    }

                    cc++;


                    if(a->getIsAtk()==1){

                        connect(this,&Widget::MU,a,&Plant::hit_music, Qt::AutoConnection);
                        connect(this,&Widget::shooting,a,&Plant::beginShoot, Qt::AutoConnection);
                        connect(this,&Widget::stopShooting,a,&Plant::stopShot, Qt::AutoConnection);
                        connect(a,&Plant::Shot,[=](){
                            a->setBullet(bullet[a->getNumber()-1]);
                            QLabel*h=new QLabel(this);
                            Bullet*b=new Bullet(a->getBullet());
                            b->setLabel(h);
                            b->setATK(a->getATK());
                            bullets.push_back(b);
                            b->setNumber(bullets.size()-1);
                            b->setPlantsNumber(a->getIndex());
                            //                            connect(this,&Widget::MU,b,&Bullet::hit_music, Qt::AutoConnection);
                            b->setBulletAttack(false);
                            h->move(a->getX()*85+465,a->getY()*100+230);
                            view(h,a->getBulletURL(),false,-1);

                        });
                    }

                    if(plants[qq->getNum()]->getIsAtk()==0){

                        connect(a,&Plant::MakeSun,[=](){
                            Sun*aa=new Sun(a->getATK(),this);
                            Sun2.push_back(aa);
                            int dx=QRandomGenerator::global()->bounded(0,50);
                            int dy=QRandomGenerator::global()->bounded(20,50);
                            aa->move(a->getLabel()->x()+dx,a->getLabel()->y()+dy);
                            viewSun(aa,":/new/play/play/sun.png");
                            connect(aa,&Sun::clicked,[=](){
                                setSunNum(50,true);
                                for(vector<Sun*>::iterator it=Sun2.begin();it!=Sun2.end();++it){
                                    if(*it==aa){
                                        Sun*oo=*it;
                                        Sun2.erase(it);
                                        --it;
                                        oo->close();
                                        oo->deleteLater();
                                        break;
                                    }
                                }
                            });


                        });
                    }

                    if(a->getIsAtk()==4){
                        a->setBoomURL(":/plant/Boom2.gif");
                        connect(a,&Plant::readyBoom,[=](){
                            view(a->getLabel(),":/plant/BeginBoom.gif",true,a->getIndex());
                        });
                        connect(this,&Widget::destruct1,this,[=](int index){
                            if(a->getIndex()==index){
                                //qDebug()<<"BBB";
                                for(vector<Plant*>::iterator it=plant.begin();it!=plant.end();++it){
                                    if(*it==a){
                                        plant.erase(it);
                                        Hole*Q=new Hole(this);
                                        Q->view(":/plant/tu.png");
                                        Q->setX(a->getX());
                                        Q->setY(a->getY());
                                        holes.push_back(Q);

                                        connect(Q,&Hole::des,[=](int X,int Y){
                                            map[X][Y]=false;
                                            for(vector<Hole*>::iterator it=holes.begin();it!=holes.end();++it){
                                                if((*it)->getX()==X&&(*it)->getY()==Y){
                                                    Hole*H=*it;
                                                    holes.erase(it);
                                                    --it;
                                                    delete H;
                                                    break;
                                                }
                                            }
                                        });
                                        Q->move(a->getLabel()->pos());
                                        QLabel*P=new QLabel(this);
                                        view(P,a->getBoomURL(),true,-12);

                                        P->move(a->getLabel()->x()-0.5*P->width()+40,40+a->getLabel()->y()-(P->height()-a->getLabel()->height()));
                                        for(int i=0;i<zombie.size();i++){
                                            if(abs(zombie[i]->getLabel()->x()-a->getLabel()->x())<=700){
                                                zombie[i]->be_attack(114514);
                                                diezombie[i]->setDieURL(":/pvz/zombie/BoomDie1.gif");
                                            }
                                        }

                                        zombiesDie();
                                        --it;
                                        for(int i=0;i<plant.size();i++){
                                            if(plant[i]->getIsAtk()==5){
                                                plant[i]->setIsShooting(false);
                                                emit stopShooting(i);
                                                emit Cabage_huifu(i);
                                                disconnect(this,&Widget::CabageShot,plant[i],&Plant::shot1);
                                            }
                                        }
                                        a->deleteLater();
                                    }
                                }
                            }
                        });
                    }
                    if(a->getIsAtk()==5){
                        connect(this,&Widget::MU,a,&Plant::hit_music, Qt::AutoConnection);
                        connect(this,&Widget::shooting,a,&Plant::beginShoot, Qt::AutoConnection);
                        connect(this,&Widget::stopShooting,a,&Plant::stopShot, Qt::AutoConnection);
                        connect(a,&Plant::attack,this,[=](){
                            a->getLabel()->move(x*85+365,y*100+210-29);
                            a->getLabel()->resize(85,109);
                            view(a->getLabel(),":/plant/Cabbagepitcher_Attack.gif",false,a->getIndex());

                        });
                        connect(a,&Plant::stopAttack,this,[=](){
                            //qDebug()<<"stopshoot";
                            a->getLabel()->resize(85,80);
                            a->getLabel()->move(x*85+365,y*100+210);
                            view(a->getLabel(),a->getURL(),false,-1);


                        });
                       connect(this,&Widget::CabageShot,a,&Plant::shot1);
                        connect(a,&Plant::Shot,[=](){

                            a->setBullet(bullet[a->getNumber()-1]);
                            QLabel*h=new QLabel(this);
                            Bullet*b=new Bullet(a->getBullet());
                            b->setLabel(h);
                            b->setATK(a->getATK());
                            bullets.push_back(b);
                            b->setNumber(bullets.size()-1);
                            b->setPlantsNumber(a->getIndex());
                            //                            connect(this,&Widget::MU,b,&Bullet::hit_music, Qt::AutoConnection);
                            b->setBulletAttack(false);
                            b->setPult(true);
                            b->setY(a->getY());
                            h->move(a->getLabel()->x()+50,a->getLabel()->y());
                            b->setStartPos(h->pos());
                            view(h,a->getBulletURL(),false,-1);
                            connect(this,&Widget::CabageMove,b,&Bullet::Bullet_MOve);

                            connect(b,&Bullet::MoveTo,[=](float x){
                                b->getLabel()->move(b->getStartPos().x()+b->dx,b->getStartPos().y()-100*x);
                                //qDebug()<<x;
                            });
                            //                            connect(a,&Plant::MoveTo,b,[=](float x){
                            //                                b->getLabel()->move(b->getStartPos().x()+b->dx,b->getStartPos().y()-100*x);
                            //                                update();
                            //                            });
                        });
                    }
                    plants[qq->getNum()]->shotMode();
                    if(a->getIsAtk()==3){
                        a->setBoomURL(":/plant/JalapenoAttack.gif");
                        connect(this,&Widget::destruct,this,[=](int index){

                            if(a->getIndex()==index){

                                for(vector<Plant*>::iterator it=plant.begin();it!=plant.end();++it){
                                    if(*it==a){
                                        plant.erase(it);
                                        int y0=a->getLabel()->y();
                                        QLabel*P=new QLabel(this);
                                        P->move(365,y0);
                                        view(P,a->getBoomURL(),true,-12);
                                        for(int i=0;i<zombie.size();i++){
                                            if(zombie[i]->getY()==a->getY()){
                                                zombie[i]->be_attack(114514);
                                                diezombie[i]->setDieURL(":/pvz/zombie/BoomDie1.gif");
                                            }
                                        }
                                        for(int i=0;i<plant.size();i++){
                                            if(plant[i]->getIsAtk()==5&&plant[i]->getY()==(*it)->getY()){
                                                plant[i]->setIsShooting(false);
                                                emit stopShooting(i);
                                                emit Cabage_huifu(i);
                                                disconnect(this,&Widget::CabageShot,plant[i],&Plant::shot1);
                                            }
                                        }
                                        zombiesDie();
                                        map[a->getX()][a->getY()]=false;
                                        --it;
                                        a->deleteLater();

                                        //m->deleteLater();


                                        break;
                                    }
                                }


                                //disconnect(mo,&QMovie::frameChanged,this,nullptr);
                                //mo->deleteLater();

                                renewPlantIndex();
                            }

                        });
                    }

                    plants[qq->getNum()]->setCD();
                    plants[qq->getNum()]->inCD();
                    qq->inCD();
                    view(qq,plants[qq->getNum()]->getGraychooseUrl(),false,-1);

                }

            }
            qq->moveBack();
            //            if(cc>0){

            //            }
            //qDebug()<<plant.size();
        });
    }

}
void Widget::renewZombieIndex(){
    for(int i=0;i<zombie.size();i++){
        zombie[i]->setIndex(i);
    }
}
void Widget::renewPlantIndex(){
    for(int i=0;i<plant.size();i++){
        plant[i]->setIndex(i);
    }
}
void Widget::renewBulletsIndex(){
    for(int i=0;i<bullets.size();i++){
        bullets[i]->setNumber(i);
    }
}
void Widget::zombiesDie(){
    int o=0;
    for(vector<Zombies*>::iterator it=zombie.begin();it!=zombie.end();++it,++o){
        if((*it)->getHP()<=0){
            for(int i=0;i<plant.size();i++){
                if((plant[i]->getIsAtk()==1||plant[i]->getIsAtk()==5)&&plant[i]->getY()==(*it)->getY()){
                    int count=0;
                    for(int j=0;j<zombie.size();j++){
                        if(j!=o&&zombie[j]->getY()==(*it)->getY()&&searchZombies(zombie[j],plant[i])){
                            count++;
                        }
                    }

                    if(count==0){

                        plant[i]->setIsShooting(false);
                        emit stopShooting(i);
                        emit Cabage_huifu(i);
                        if(plant[i]->getIsAtk()==5)
                            disconnect(this,&Widget::CabageShot,plant[i],&Plant::shot1);
                    }
                }

            }
            //emit stopEAT(o);
            Zombies*p=*it;
            diezombie[o]->Index=o;
            diezombie[o]->LabelMove((*it)->getLabel()->x()-(diezombie[o]->getWidth()-(*it)->getLabel()->width()),(*it)->getLabel()->y());
            diezombie[o]->start();
            zombie.erase(it);
            delete p;
            --it;

        }
    }
}
void Widget::initCHOOSE(){
    for(int i=0;i<plants.size();i++){
        ChoosePlant[i]->view(plants[i]->getGraychooseUrl());
    }
}


void Widget::initCar(){
    for(int i=0;i<5;i++){
        QLabel*a=new QLabel(this);
        a->move(242,210+i*100);
        car.push_back(a);
        carMove[i]=false;
        view(a,":/new/play/play/Car.png",false,-1);
    }
}
void Widget::initShovel(){

    QPoint pos(ui->label_7->pos().x()+10,ui->label_7->pos().y()+10);
    this->shovel=new Shovel(pos,this);
    this->shovel->view(":/new/play/play/shovel.png");
    this->shovel->move(pos);
    connect(shovel,&Shovel::clearPlants,[=](QPoint point){
        QPoint pos(point.x(),point.y()+shovel->height());
        if(rect1.contains(pos)){
            //qDebug()<<"生";
            int X=(pos.x()-355)/85;
            int Y=(pos.y()-200)/100;
            //qDebug()<<X<<' '<<Y;
            if(map[X][Y]==true){
                for(vector<Plant*>::iterator it=plant.begin();it!=plant.end();++it){
                    if((*it)->getX()==X&&(*it)->getY()==Y){
                        Plant*g=*it;
                        plant.erase(it);
                        --it;
                        map[X][Y]=false;
                        delete g;
                        break;
                    }
                }
            }
        }

    });

}



Widget::~Widget()
{
    delete ui;
}


