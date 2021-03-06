#include "pathfinder.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneWheelEvent>
#include <iostream>
#include <QKeyEvent>
#include <QDebug>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QGraphicsColorizeEffect>
#include <stdlib.h>
#include <limits>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    mapList=QStringList()<<"Maze 1 (Medium)"<<"Maze 2 (Big)"<<"Maze 3 (Insane)"<<"Map 1 (Small)"<<"Map 2 (Medium)" <<"Map 3 (Big)" <<"Map 4 (Bigger)";
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->mapSelect->addItems(mapList);
    
    hero = QPixmap{":/face-monkey.png"};
    hero = hero.scaledToHeight(SCALE);
    enemy = QPixmap{":/face-angry.png"};
    enemy = enemy.scaledToHeight(SCALE);
    health = QPixmap{":/emblem-generic.png"};
    health = health.scaledToHeight(SCALE);

    autoPlayEnabled = false;
    timer = new QTimer(this);
    transform = QTransform();
    speed = ui->speed->value();
    connect(timer, SIGNAL(timeout()), this, SLOT(moveOneStep()));

}

void MainWindow::on_playButton_clicked()
{
    int selectedMap = ui->mapSelect->currentIndex();
    QString mapPlay;
    switch(selectedMap){
        case 0: mapPlay = (QString)":/maze1.png";
        break;

        case 1: mapPlay = (QString)":/maze2.png";
        break;

        case 2: mapPlay = (QString)":/maze_3.jpg";
        break;

        case 3: mapPlay = (QString)":/world-map.jpeg";
        break;

        case 4: mapPlay = (QString)":/map3.jpg";
        break;

        case 5: mapPlay = (QString)":/map_4";
        break;

        case 6: mapPlay = (QString)":/map_2.jpg";
        break;

    }

    qDebug() << selectedMap << mapPlay;

    int nrOfHealth = ui->nrHealth->value();
    int nrOfEnemies = ui->nrEnemies->value();

    gameData = std::make_shared<Game>(mapPlay,nrOfEnemies,nrOfHealth);

    currentGame = gameData;

    float weight = (float) ui->heuristicWeight->value();
    pathFinder = std::make_shared<PathFinder>(weight,gameData);

    createMap();

    ui->stackedWidget->setCurrentIndex(1);
    ui->mapView->setScene(sceneMap);
    ui->mapView->fitInView( bounds, Qt::KeepAspectRatio );
    ui->mapView->setFocus();
}


void MainWindow::createMap(){


    worldTiles = gameData->getWorldToDraw();
    enemies = gameData->getEnemies();
    healthPacks = gameData->getHealthPacks();

    rows = gameData->getRows();
    cols = gameData->getColms();

    std::vector<std::shared_ptr<Enemy>>::iterator p;
    for(p=enemies.begin();p!=enemies.end();p++)
    {
        backupTileValue.push_back(worldTiles.at(cols*(*p)->getYPos()+(*p)->getXPos())->getValue());
    }


    //create view for the play map

    sceneMap = new QGraphicsScene(0, 0, cols*SCALE, rows*SCALE, this);

    //draw map
    QColor colorMap = QColor();
    QPen outlinePen(Qt::NoPen);


    std::vector<std::shared_ptr<Tile>>::iterator i;
    for(i = worldTiles.begin(); i < worldTiles.end(); i++){

        float a = (*i)->getValue();           //check grayvalue for black -> black = not passable
        if(a>2)
            colorMap.setRgb(0,0,0);
        else
            colorMap.setGreen((int)(a*255));
        sceneMap->addRect((*i)->getXPos()*SCALE ,(*i)->getYPos()*SCALE, SCALE, SCALE, outlinePen, colorMap);
    }


    std::vector<std::shared_ptr<Enemy>>::iterator j;
    for(j = enemies.begin(); j != enemies.end(); j ++ ){

        //add enemy to scene @ his coordinates
        QGraphicsPixmapItem *item = sceneMap->addPixmap(enemy);
        item->setPos((*j)->getXPos()*SCALE, (*j)->getYPos()*SCALE);
    }

    std::vector<std::shared_ptr<Tile>>::iterator k;
    for(k = healthPacks.begin(); k != healthPacks.end(); k ++ ){

        //add health to scene @ his coordinates
        QGraphicsPixmapItem* item = sceneMap->addPixmap(health);
        item->setPos((*k)->getXPos()*SCALE, (*k)->getYPos()*SCALE);
    }

    //spawn protagonist and get coordinates
    heroObj = gameData->getHero();
    heroInitialLoc.setCol(heroObj->getXPos());
    heroInitialLoc.setRow(heroObj->getYPos());
    heroItem = sceneMap->addPixmap(hero);
    heroItem->setPos(heroObj->getXPos()*SCALE,heroObj->getYPos()*SCALE);
    heroEnergy = gameData->getHeroEnergy();
    heroHealth = gameData->getHeroHealth();
    //Install the eventfilter for detecting keypresses and zoom function
    sceneMap->installEventFilter(this);
    bounds = sceneMap->itemsBoundingRect();

    //reset the health and energy bar:
    ui->healthBar->setValue(heroHealth);
    ui->energyBar->setValue(heroEnergy);
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == sceneMap)
    {
        if(event->type() == QEvent::GraphicsSceneWheel)
        {
            QGraphicsSceneWheelEvent *ev = (QGraphicsSceneWheelEvent *)event;
            if(ev->delta() < 0 )
            {
                zoomOut();
            }
            else if(ev->delta() > 0)
            {
                zoomIn();
            }
            return true;
        }

        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = (QKeyEvent*)event;
            if (keyEvent->key() == Qt::Key_Up)
            {
                int currentX = heroObj->getXPos()*SCALE;
                int currentY = heroObj->getYPos()*SCALE;
                addOverlay(currentX,currentY);
                goUp();
                return true;
            }
            else if(keyEvent->key() == Qt::Key_Down)
            {
                int currentX = heroObj->getXPos()*SCALE;
                int currentY = heroObj->getYPos()*SCALE;
                addOverlay(currentX,currentY);
                goDown();
                return true;
            }
            else if(keyEvent->key() == Qt::Key_Left)
            {
                int currentX = heroObj->getXPos()*SCALE;
                int currentY = heroObj->getYPos()*SCALE;
                addOverlay(currentX,currentY);
                goLeft();
                return true;
            }
            else if(keyEvent->key() == Qt::Key_Right)
            {
                int currentX = heroObj->getXPos()*SCALE;
                int currentY = heroObj->getYPos()*SCALE;
                addOverlay(currentX,currentY);
                goRight();
                return true;
            }
            else
            {
                //qDebug() << "lineEdit -> Wrong KeyPess";
                return true;
            }
        }
        if(event->type() == QEvent::GraphicsSceneMousePress)
        {
            QGraphicsSceneMouseEvent *mouseEvent = (QGraphicsSceneMouseEvent *)event;
            int x = ((int)mouseEvent->scenePos().rx())/SCALE;
            int y = ((int)mouseEvent->scenePos().ry())/SCALE;
            Location heroLoc{heroObj->getYPos(),heroObj->getXPos()};
            Location destLoc{y,x};
            path = pathFinder->searchPath(heroLoc,destLoc);
            if(!path.empty())
                timer->start(1000/speed);
            else
                qDebug() << "path is not found";
            }
    }

    return false;

}


MainWindow::~MainWindow()
{
    //delete ui;
}


void MainWindow::zoomIn()
{
    bounds.setWidth(bounds.width()-500);
    bounds.setHeight(bounds.height()-500);
    ui->mapView->fitInView(bounds, Qt::KeepAspectRatio);
    ui->mapView->centerOn(0, 0);
    ui->mapView->setScene(sceneMap);
}

void MainWindow::zoomOut()
{
    bounds.setWidth(bounds.width()+50);
    bounds.setHeight(bounds.height()+50);
    ui->mapView->fitInView(bounds, Qt::KeepAspectRatio);
    ui->mapView->centerOn(0, 0);
    ui->mapView->setScene(sceneMap);
}

void MainWindow::goUp()
{
    if(heroObj->getYPos() > 0)
    {
        heroObj->setYPos(heroObj->getYPos() - 1);
    }

    heroItem->setPos(heroObj->getXPos()*SCALE,heroObj->getYPos()*SCALE);
    ui->mapView->update();
    Location tileLoc = Location{heroObj->getYPos(),heroObj->getXPos()};
    float tileWeight = gameData->getTileValue(tileLoc);
    updateEnergy(-tileWeight);
    checkFight();
    checkHealthPack();
}

void MainWindow::goLeft()
{
    if(heroObj->getXPos() > 0)
    {
        heroObj->setXPos(heroObj->getXPos() - 1);
    }
    heroItem->setPos(heroObj->getXPos()*SCALE,heroObj->getYPos()*SCALE);
    ui->mapView->update();
    Location tileLoc = Location{heroObj->getYPos(),heroObj->getXPos()};
    float tileWeight = gameData->getTileValue(tileLoc);
    updateEnergy(-tileWeight);
    checkFight();
    checkHealthPack();
}

void MainWindow::goRight()
{
    if(heroObj->getXPos() < cols)
    {
        heroObj->setXPos(heroObj->getXPos() + 1);
    }
    heroItem->setPos(heroObj->getXPos()*SCALE,heroObj->getYPos()*SCALE);
    ui->mapView->update();
    Location tileLoc = Location{heroObj->getYPos(),heroObj->getXPos()};
    float tileWeight = gameData->getTileValue(tileLoc);
    updateEnergy(-tileWeight);
    checkFight();
    checkHealthPack();

}

void MainWindow::goDown()
{
    if(heroObj->getYPos() < rows)
    {
        heroObj->setYPos(heroObj->getYPos() + 1);
    }
    heroItem->setPos(heroObj->getXPos()*SCALE,heroObj->getYPos()*SCALE);
    ui->mapView->update();
    Location tileLoc = Location{heroObj->getYPos(),heroObj->getXPos()};
    float tileWeight = gameData->getTileValue(tileLoc);
    updateEnergy(-tileWeight);
    checkFight();
    checkHealthPack();
}


void MainWindow::checkFight()
{
    bool beatEnemy = false;
    std::vector<std::shared_ptr<Enemy>>::iterator j;
    for(j = enemies.begin(); j != enemies.end(); j ++ ){

        if((*j)->getXPos() == heroObj->getXPos() && (*j)->getYPos() == heroObj->getYPos() )
        {
            float damage = -(*j)->getValue();
            (worldTiles.at((*j)->getYPos()*cols+(*j)->getXPos()))->setValue(std::numeric_limits<float>::infinity());

            //load and scale dead enemy icon
            QPixmap dead;
            dead.load(":/face-sick.png");
            dead=dead.scaledToHeight(SCALE);
            QGraphicsPixmapItem *deadEnemy = sceneMap->addPixmap(dead);
            deadEnemy->setPos(heroObj->getXPos()*SCALE,heroObj->getYPos()*SCALE);
            enemies.erase(j);
            updateHealth(damage);
            updateEnergy(500);
            beatEnemy = true;
            break;
        }
    }
    if(autoPlayEnabled && (!enemies.empty()) && beatEnemy && path.empty())
        strategy();
}

void MainWindow::checkHealthPack()
{
    bool getHealth = false;
    std::vector<std::shared_ptr<Tile>>::iterator j;
    for(j = healthPacks.begin(); j != healthPacks.end(); j ++ ){

        if((*j)->getXPos() == heroObj->getXPos() && (*j)->getYPos() == heroObj->getYPos() )
        {
            //load and scale empty health pack icon
            QPixmap emptyHealthPack;
            emptyHealthPack.load(":/help-browser.png");
            emptyHealthPack=emptyHealthPack.scaledToHeight(SCALE);
            QGraphicsPixmapItem *emptyHealthItem = sceneMap->addPixmap(emptyHealthPack);
            emptyHealthItem->setPos(heroObj->getXPos()*SCALE,heroObj->getYPos()*SCALE);
            updateHealth((*j)->getValue());
            healthPacks.erase(j);
            getHealth = true;
            break;
        }
    }
    if(autoPlayEnabled && (!enemies.empty()) && getHealth && path.empty())
        strategy();
}

void MainWindow::updateHealth(float extraHealth)
{
    heroHealth = heroHealth + extraHealth;
    if(heroHealth < 0)
    {
        timer->stop();
        ui->healthBar->setValue(0);
        ui->healthBar->update();
        ui->stackedWidget->setCurrentIndex(2);
        ui->resultLabel->setText("You Lose :(");
        ui->reasonLabel->setText("Out of Health");
    }
    else if(heroHealth > 100)
    {
        heroHealth = 100;
        ui->healthBar->setValue(100);
        ui->healthBar->update();
    }
    else
    {
        if(enemies.size() == 0){
            ui->stackedWidget->setCurrentIndex(2);
            ui->resultLabel->setText("You WIN :)");
            ui->reasonLabel->setText("Defeated All Enemies!");
        }
        ui->healthBar->setValue((int)heroHealth);
        ui->healthBar->update();
    }

}

void MainWindow::updateEnergy(float energy)
{
    heroEnergy = heroEnergy + energy;
    if(heroEnergy < 0)
    {
        timer->stop();
        ui->energyBar->setValue(0);
        ui->energyBar->update();
        ui->stackedWidget->setCurrentIndex(2);
        ui->resultLabel->setText("You Lose :(");
        ui->reasonLabel->setText("Out of Energy");
    }
    else if(heroEnergy > 500)
    {
        heroEnergy = 500;
        ui->energyBar->setValue(500);
        ui->energyBar->update();
    }
    else
    {
        ui->energyBar->setValue((int)heroEnergy);
        ui->energyBar->update();
    }

}


void MainWindow::on_actionBack_to_main_triggered()
{
    autoPlayEnabled = false;
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::addOverlay(int x, int y)
{
    QGraphicsItem *item = sceneMap->itemAt(x,y,transform);
    if(item->graphicsEffect() == 0)
    {
        QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);
        effect->setColor(QColor(100,100,100,128));
        item->setGraphicsEffect(effect);
    }
}

void MainWindow::on_actionZoom_in_triggered()
{
    zoomIn();
}



void MainWindow::on_actionZoom_out_triggered()
{
    zoomOut();
}

void MainWindow::moveOneStep()
{
    Direction direction = path.back();
    path.pop_back();
    if(path.empty())
        timer->stop();
    int currentX = heroObj->getXPos()*SCALE;
    int currentY = heroObj->getYPos()*SCALE;
    switch(direction)
    {
    case Left:
        addOverlay(currentX, currentY);
        goLeft();
        break;
    case Right:
        addOverlay(currentX, currentY);
        goRight();
        break;
    case Up:
        addOverlay(currentX, currentY);
        goUp();
        break;
    case Down:
        addOverlay(currentX, currentY);
        goDown();
        break;
    case None:
        break;
    }
}

void MainWindow::strategy()
{
    if(heroHealth > 0)
    {
        std::shared_ptr<Enemy> nearestEnemy = findNearestEnemy();
        Location heroLoc{heroObj->getYPos(),heroObj->getXPos()};
        if(heroHealth > nearestEnemy->getValue() || healthPacks.empty())
        {
            Location enemyLoc{nearestEnemy->getYPos(),nearestEnemy->getXPos()};
            path = pathFinder->searchPath(heroLoc,enemyLoc);
        }
        else
        {
            std::shared_ptr<Tile> nearestPack = findNearestHealthpack();
            Location healthLoc{nearestPack->getYPos(),nearestPack->getXPos()};
            path = pathFinder->searchPath(heroLoc,healthLoc);
        }
        if(!path.empty())
            timer->start(1000/speed);
        else
            qDebug() << "path is not found";
    }
}

std::shared_ptr<Enemy> MainWindow::findNearestEnemy()
{
    int currentX = heroObj->getXPos();
    int currentY = heroObj->getYPos();
    std::shared_ptr<Enemy> nearestEnemy = enemies.at(0);
    int nearestDistance = abs(nearestEnemy->getXPos()-currentX)+abs(nearestEnemy->getYPos()-currentY);
    for(unsigned i=1;i<enemies.size();i++)
    {
        std::shared_ptr<Enemy> enemy = enemies.at(i);
        int distance = abs(enemy->getXPos()-currentX)+abs(enemy->getYPos()-currentY);
        if(distance < nearestDistance)
        {
            nearestDistance = distance;
            nearestEnemy = enemy;
        }
    }
    return nearestEnemy;
}
std::shared_ptr<Tile> MainWindow::findNearestHealthpack()
{
    int currentX = heroObj->getXPos();
    int currentY = heroObj->getYPos();
    std::shared_ptr<Tile> nearestHealthpack = healthPacks.at(0);
    int nearestDistance = abs(nearestHealthpack->getXPos()-currentX)+abs(nearestHealthpack->getYPos()-currentY);
    for(unsigned i=1;i<healthPacks.size();i++)
    {
        std::shared_ptr<Tile> healthpack = healthPacks.at(i);
        int distance = abs(healthpack->getXPos()-currentX)+abs(healthpack->getYPos()-currentY);
        if(distance < nearestDistance)
        {
            nearestDistance = distance;
            nearestHealthpack = healthpack;
        }
    }
    return nearestHealthpack;
}

void MainWindow::on_main_menu_clicked()
{
    autoPlayEnabled = false;
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionAuto_play_triggered()
{
    autoPlayEnabled = true;
    strategy();
}

void MainWindow::on_actionStop_auto_play_triggered()
{
    autoPlayEnabled = false;
}

void MainWindow::on_new_map_clicked()
{
    autoPlayEnabled = false;
    on_playButton_clicked();
}

void MainWindow::on_replay_clicked()
{
    autoPlayEnabled = false;
    sceneMap->clear();


    /*enemies = gameData->getEnemies();
    worldTiles = gameData->getWorldToDraw();
    heroObj = gameData->getHero();*/
    ui->mapView->viewport()->update();
    float weight = (float) ui->heuristicWeight->value();

gameData = currentGame;
    pathFinder = std::make_shared<PathFinder>(weight,gameData);

    createMap();

    /*std::vector<std::shared_ptr<Enemy>>::iterator j;
    int i=0;
    for(j=enemies.begin();j!=enemies.end();j++)
    {
        (worldTiles.at(cols*(*j)->getYPos()+(*j)->getXPos()))->setValue(backupTileValue.at(i));
        i++;
    }
    //spawn protagonist and get coordinates
    heroObj->setXPos(heroInitialLoc.getCol());
    heroObj->setYPos(heroInitialLoc.getRow());*/
    //heroItem->setPos(heroObj->getXPos()*SCALE,heroObj->getYPos()*SCALE);
    //heroEnergy = 500;
    //heroHealth = 100;
    //createMap();
    ui->stackedWidget->setCurrentIndex(1);
    ui->mapView->update();
    ui->mapView->fitInView( bounds, Qt::KeepAspectRatio );
    ui->mapView->setFocus();
}

void MainWindow::on_speed_valueChanged(int value)
{
    speed = value;
}

void MainWindow::on_heuristicWeight_editingFinished()
{
    float weight = ui->heuristicWeight->text().toFloat();
    pathFinder->setWeight(weight);
}
