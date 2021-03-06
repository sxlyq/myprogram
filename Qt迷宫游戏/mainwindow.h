#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <vector>
#include <memory>
#include <QVBoxLayout>
#include <queue>
#include <QTimer>
#include "world.h"
#include "location.h"
#include "game.h"
#include "direction.h"
#include "pathfinder.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void goUp();
    void goLeft();
    void goDown();
    void goRight();


private slots:
    void on_playButton_clicked();
    void on_main_menu_clicked();
    void on_actionBack_to_main_triggered();
    void on_actionZoom_in_triggered();
    void on_actionZoom_out_triggered();
    void on_actionAuto_play_triggered();
    void on_actionStop_auto_play_triggered();
    void on_new_map_clicked();
    void on_replay_clicked();
    void moveOneStep();
    void on_speed_valueChanged(int value);
    void on_heuristicWeight_editingFinished();

private:
    QStringList mapList;
    std::shared_ptr<Game> gameData;
    std::shared_ptr<Game> currentGame;
    std::shared_ptr<Ui::MainWindow> ui;
    QGraphicsScene *sceneMap;
    const int SCALE = 20;
    int rows;
    int cols;
    int xPosHero = 0;
    int yPosHero = 0;
    bool autoPlayEnabled;
    int speed;
    QPixmap hero ;
    QPixmap enemy;
    QPixmap health;
    QGraphicsPixmapItem *heroItem ;
    std::shared_ptr<Protagonist> heroObj ;
    QRectF bounds ;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Tile>> healthPacks;
    std::vector<std::shared_ptr<Tile>> worldTiles;
    float heroHealth;
    float heroEnergy;
    std::vector<Direction> path;
    std::shared_ptr<PathFinder> pathFinder;
    QTimer *timer;
    QTransform transform;

    Location heroInitialLoc=Location{0,0};
    std::vector<float> backupTileValue;

protected:
     bool eventFilter(QObject *obj, QEvent *event);
     void zoomOut();
     void zoomIn();
     void checkFight();
     void checkHealthPack();
     std::shared_ptr<Enemy> findNearestEnemy();
     std::shared_ptr<Tile> findNearestHealthpack();
     void updateEnergy(float energy);
     void updateHealth(float enemyHealth);
     void addOverlay(int x, int y);
     void strategy();
     void createMap();
};

#endif // MAINWINDOW_H
    
