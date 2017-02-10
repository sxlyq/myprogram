#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <queue>
#include "plannernode.h"
#include "direction.h"

class Game;

class PathFinder
{
public:
    PathFinder(float weight, std::shared_ptr<Game>game_ptr);
    float getWeight() const;
    void setGame(std::shared_ptr<Game> game_ptr);
    float calculateFcost(float Gcost, const Location &currentLoc, const Location &destLoc);
    std::vector<Direction> searchPath(const Location &startLoc,const Location &destLoc);

    void setWeight(float value);

private:
    float weight;
    std::shared_ptr<Game> game;
};

bool compFinalCost(const std::shared_ptr<PlannerNode> &thisNode, const std::shared_ptr<PlannerNode> &otherNode);

#endif // PATHFINDER_H
