#ifndef WORLD_H
#define WORLD_H

#include "world_global.h"
#include <vector>
#include <memory>
#include <QObject>

class Tile
{
public:
    Tile(int xPosition, int yPosition, float tileWeight);
    virtual ~Tile() {};
    float getValue() const {return value;};
    void setValue(float newValue) {value = newValue;};
    int getXPos() const {return xPos;};
    int getYPos() const {return yPos;};
    void setXPos(int newPos) {xPos = newPos;};
    void setYPos(int newPos) {yPos = newPos;}
    bool operator== (const Tile & other) const
        {return (getXPos() == other.getXPos()) && (getYPos() == other.getYPos());};

protected:
    int xPos;
    int yPos;
    float value;
};

class Enemy : public Tile
{
public:
    Enemy(int xPosition, int yPosition, float strength);
    bool getDefeated() const {return defeated;}
    void setDefeated(bool value) {defeated = value;};

private:
    bool defeated;
};

class Protagonist: public QObject, public Tile
{
    Q_OBJECT
public:
    Protagonist();
    void setXPos(int newPos) {xPos = newPos; emit posChanged(xPos, yPos);};
    void setYPos(int newPos) {yPos = newPos; emit posChanged(xPos, yPos);};
    void setPos(int newX, int newY) {xPos = newX; yPos = newY; emit posChanged(xPos, yPos);};
    float getHealth() const {return health;};
    void setHealth(float value) {health = value;};

    float getEnergy() const {return energy;}
    void setEnergy(float value) {energy = value;};

signals:
    void posChanged(int x, int y);

private:
    float health;
    float energy;
};

class WORLDSHARED_EXPORT World
{
public:
    World() = default;
    std::vector<std::shared_ptr<Tile>> createWorld(QString filename);
    std::vector<std::shared_ptr<Enemy>> getEnemies(unsigned int nrOfEnemies);
    std::vector<std::shared_ptr<Tile>> getHealthPacks(unsigned int nrOfPacks);
    std::shared_ptr<Protagonist> getProtagonist();
    int getRows() const {return rows;};
    int getCols() const {return cols;};

private:
    int rows, cols;
};


#endif // WORLD_H
