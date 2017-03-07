#include "game.h"
#include "world.h"
#include "location.h"
#include <iostream>

Game::Game(QString map ,int nrOfEnemies, int nrOfHealthPacks)
{
    if(map != ""){
        world = World();
        worldTiles = world.createWorld(map);
        enemies = world.getEnemies(nrOfEnemies);
        healthPacks = world.getHealthPacks(nrOfHealthPacks);
        hero = world.getProtagonist();
        hero->setEnergy(500);
        int col = getColms();
        if((worldTiles.at(hero->getYPos()*col+hero->getXPos()))->getValue() > 1)
        {
            Location loc = relocate(hero->getXPos(),hero->getYPos());
            hero->setXPos(loc.getCol());
            hero->setYPos(loc.getRow());
        }
        std::vector<std::shared_ptr<Enemy>>::iterator enemyIt;
        for(enemyIt = enemies.begin();enemyIt != enemies.end();enemyIt++)
        {
            if((worldTiles.at((*enemyIt)->getYPos()*col+(*enemyIt)->getXPos()))->getValue() > 1)
            {
                Location loc = relocate((*enemyIt)->getXPos(),(*enemyIt)->getYPos());
                (*enemyIt)->setXPos(loc.getCol());
                (*enemyIt)->setYPos(loc.getRow());
            }
        }
        std::vector<std::shared_ptr<Tile>>::iterator healthIt;
        for(healthIt = healthPacks.begin();healthIt != healthPacks.end();healthIt++)
        {
            if((worldTiles.at((*healthIt)->getYPos()*col+(*healthIt)->getXPos()))->getValue() > 1)
            {
                Location loc = relocate((*healthIt)->getXPos(),(*healthIt)->getYPos());
                (*healthIt)->setXPos(loc.getCol());
                (*healthIt)->setYPos(loc.getRow());
            }
        }
        std::cout << "create world" << std::endl;
    }
}



std::vector<std::shared_ptr<Tile>> Game::getWorldToDraw()
{
    return worldTiles;
}

std::vector<std::shared_ptr<Enemy>> Game::getEnemies()
{
    return enemies;
}

std::vector<std::shared_ptr<Tile>> Game::getHealthPacks()
{
    return healthPacks;
}

std::shared_ptr<Protagonist> Game::getHero()
{
    return hero;
}

float Game::getHeroEnergy()
{
    return hero->getEnergy();
}

float Game::getHeroHealth()
{
    return hero->getHealth();
}

int Game::getRows()
{
    return world.getRows();
}

int Game::getColms()
{
    return world.getCols();
}

float Game::getTileValue(Location &location)
{
    int rows = getRows();
    int cols = getColms();
    int locRow = location.getRow();
    int locCol = location.getCol();
    if((locRow < 0) || (locRow >= rows))
        return -1;
    if((locCol < 0) || (locCol >= cols))
        return -1;
    return (worldTiles.at(cols*locRow+locCol))->getValue();
}

Location Game::relocate(int posX, int posY)
{
        int col = getColms();
        int row = getRows();
        int dx,dy;
        bool passable=false;
        if(posX < col/2)
            dx=3;
        else
            dx=-3;
        if(posY < row/2)
            dy=3;
        else
            dy=-3;
        while(!passable)
        {
                posX+=dx;
                if((worldTiles.at(posY*col+posX))->getValue() < 2)
                {
                    passable = true;
                    continue;
                }
                posY+=dy;
                if((worldTiles.at(posY*col+posX))->getValue() < 2)
                {
                    passable = true;
                }
        }
        return Location(posY,posX);
}
