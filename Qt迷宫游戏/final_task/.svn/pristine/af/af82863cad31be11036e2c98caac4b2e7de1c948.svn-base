#include "pathfinder.h"
#include "game.h"
#include <stdlib.h>
#include <algorithm>
#include <iostream>


PathFinder::PathFinder(float weight, std::shared_ptr<Game> game_ptr =nullptr)
    :weight{weight},game{game_ptr}
{
}
float PathFinder::getWeight() const
{
    return weight;
}

void PathFinder::setGame(std::shared_ptr<Game> game_ptr)
{
    game = game_ptr;
}

float PathFinder::calculateFcost(float Gcost, const Location &currentLoc, const Location &destLoc)
{
    int rowDistance = std::abs(currentLoc.getRow() - destLoc.getRow());
    int colDistance = std::abs(currentLoc.getCol() - destLoc.getCol());
    int distance = rowDistance + colDistance;
    return Gcost + distance*weight;
}

std::vector<Direction> PathFinder::searchPath(const Location &startLoc,const Location &destLoc)
{
    std::vector<std::shared_ptr<PlannerNode>> openList;
    std::vector<std::shared_ptr<PlannerNode>> closedList;
    std::vector<Direction> solution;
    if(game == nullptr){
        std::cout << "game is null" << std::endl;
        return solution;
    }
    float Gcost = 0;
    std::shared_ptr<PlannerNode> startNode = std::make_shared<PlannerNode>(startLoc,Gcost,calculateFcost(Gcost,startLoc,destLoc),nullptr);
    openList.push_back(startNode);
    while(!openList.empty()){
        std::sort(openList.begin(),openList.end(),compFinalCost);
        std::shared_ptr<PlannerNode> currentNode = openList.back();
        openList.pop_back();
        Gcost = currentNode->getGcost();
        closedList.push_back(currentNode);
        std::shared_ptr<PlannerNode> parent = currentNode->getParent();
        if(currentNode->getLocation() == destLoc){
            std::shared_ptr<PlannerNode> current = currentNode;
            while(parent != nullptr)
            {
                Location currentLoc = current->getLocation();
                Location parentLoc = parent->getLocation();
                if(currentLoc.getCol() == parentLoc.getCol())
                {
                    if(currentLoc.getRow()>parentLoc.getRow())
                        solution.push_back(Down);
                    else
                        solution.push_back(Up);
                }
                else
                {
                    if(currentLoc.getCol()>parentLoc.getCol())
                        solution.push_back(Right);
                    else
                        solution.push_back(Left);
                }
                current = parent;
                parent = parent->getParent();
            }
            break;
        }
        else
        {
            Location leftLoc = currentNode->getLeftLocation();
            Location rightLoc = currentNode->getRightLocation();
            Location upLoc = currentNode->getUpLocation();
            Location downLoc = currentNode->getDownLocation();
            Location parentLoc = Location{-1,-1};
            if(parent != nullptr)
                parentLoc = parent->getLocation();
            float cost;
            if(!(leftLoc == parentLoc))
            {
                cost = game->getTileValue(leftLoc);
                if(cost > 0 && cost < 2)
                {
                    auto closedNodeIt = std::find_if(closedList.begin(),closedList.end(),[&leftLoc](std::shared_ptr<PlannerNode> node){return node->getLocation() == leftLoc;});
                    if(closedNodeIt != closedList.end())
                    {
                        if(Gcost+cost < (*closedNodeIt)->getGcost())
                        {
                            (*closedNodeIt)->setGcost(Gcost+cost);
                            (*closedNodeIt)->setFcost(calculateFcost(Gcost+cost,leftLoc,destLoc));
                            (*closedNodeIt)->setParent(currentNode);
                            openList.push_back(*closedNodeIt);
                            closedList.erase(closedNodeIt);
                        }
                    }
                    else
                    {
                        auto openNodeIt = std::find_if(openList.begin(),openList.end(),[&leftLoc](std::shared_ptr<PlannerNode> node){return node->getLocation() == leftLoc;});
                        if(openNodeIt != openList.end())
                        {
                            if(Gcost+cost < (*openNodeIt)->getGcost())
                            {
                                (*openNodeIt)->setGcost(Gcost+cost);
                                (*openNodeIt)->setFcost(calculateFcost(Gcost+cost,leftLoc,destLoc));
                                (*openNodeIt)->setParent(currentNode);
                            }
                        }
                        else
                        {
                            std::shared_ptr<PlannerNode> leftNode = std::make_shared<PlannerNode>(leftLoc,Gcost+cost,calculateFcost(Gcost+cost,leftLoc,destLoc),currentNode);
                            openList.push_back(leftNode);
                        }
                    }
                }
            }
            if(!(rightLoc == parentLoc))
            {
                cost = game->getTileValue(rightLoc);
                if(cost > 0 && cost < 2)
                {
                    auto closedNodeIt = std::find_if(closedList.begin(),closedList.end(),[&rightLoc](std::shared_ptr<PlannerNode> node){return node->getLocation() == rightLoc;});
                    if(closedNodeIt != closedList.end())
                    {
                        if(Gcost+cost < (*closedNodeIt)->getGcost())
                        {
                            (*closedNodeIt)->setGcost(Gcost+cost);
                            (*closedNodeIt)->setFcost(calculateFcost(Gcost+cost,rightLoc,destLoc));
                            (*closedNodeIt)->setParent(currentNode);
                            openList.push_back(*closedNodeIt);
                            closedList.erase(closedNodeIt);
                        }
                    }
                    else
                    {
                        auto openNodeIt = std::find_if(openList.begin(),openList.end(),[&rightLoc](std::shared_ptr<PlannerNode> node){return node->getLocation() == rightLoc;});
                        if(openNodeIt != openList.end())
                        {
                            if(Gcost+cost < (*openNodeIt)->getGcost())
                            {
                                (*openNodeIt)->setGcost(Gcost+cost);
                                (*openNodeIt)->setFcost(calculateFcost(Gcost+cost,rightLoc,destLoc));
                                (*openNodeIt)->setParent(currentNode);
                            }
                        }
                        else
                        {
                            std::shared_ptr<PlannerNode> rightNode = std::make_shared<PlannerNode>(rightLoc,Gcost+cost,calculateFcost(Gcost+cost,rightLoc,destLoc),currentNode);
                            openList.push_back(rightNode);
                        }
                    }
                }
            }
            if(!(upLoc == parentLoc))
            {
                cost = game->getTileValue(upLoc);
                if(cost > 0 && cost < 2){
                    auto closedNodeIt = std::find_if(closedList.begin(),closedList.end(),[&upLoc](std::shared_ptr<PlannerNode> node){return node->getLocation() == upLoc;});
                    if(closedNodeIt != closedList.end())
                    {
                        if(Gcost+cost < (*closedNodeIt)->getGcost())
                        {
                            (*closedNodeIt)->setGcost(Gcost+cost);
                            (*closedNodeIt)->setFcost(calculateFcost(Gcost+cost,upLoc,destLoc));
                            (*closedNodeIt)->setParent(currentNode);
                            openList.push_back(*closedNodeIt);
                            closedList.erase(closedNodeIt);
                        }
                    }
                    else
                    {
                        auto openNodeIt = std::find_if(openList.begin(),openList.end(),[&upLoc](std::shared_ptr<PlannerNode> node){return node->getLocation() == upLoc;});
                        if(openNodeIt != openList.end())
                        {
                            if(Gcost+cost < (*openNodeIt)->getGcost())
                            {
                                (*openNodeIt)->setGcost(Gcost+cost);
                                (*openNodeIt)->setFcost(calculateFcost(Gcost+cost,rightLoc,destLoc));
                                (*openNodeIt)->setParent(currentNode);
                            }
                        }
                        else
                        {
                            std::shared_ptr<PlannerNode> upNode = std::make_shared<PlannerNode>(upLoc,Gcost+cost,calculateFcost(Gcost+cost,upLoc,destLoc),currentNode);
                            openList.push_back(upNode);
                        }
                    }
                }
            }
            if(!(downLoc == parentLoc))
            {
                cost = game->getTileValue(downLoc);
                if(cost > 0 && cost < 2){
                    auto closedNodeIt = std::find_if(closedList.begin(),closedList.end(),[&downLoc](std::shared_ptr<PlannerNode> node){return node->getLocation() == downLoc;});
                    if(closedNodeIt != closedList.end())
                    {
                        if(Gcost+cost < (*closedNodeIt)->getGcost())
                        {
                            (*closedNodeIt)->setGcost(Gcost+cost);
                            (*closedNodeIt)->setFcost(calculateFcost(Gcost+cost,downLoc,destLoc));
                            (*closedNodeIt)->setParent(currentNode);
                            openList.push_back(*closedNodeIt);
                            closedList.erase(closedNodeIt);
                        }
                    }
                    else
                    {
                        auto openNodeIt = std::find_if(openList.begin(),openList.end(),[&downLoc](std::shared_ptr<PlannerNode> node){return node->getLocation() == downLoc;});
                        if(openNodeIt != openList.end())
                        {
                            if(Gcost+cost < (*openNodeIt)->getGcost())
                            {
                                (*openNodeIt)->setGcost(Gcost+cost);
                                (*openNodeIt)->setFcost(calculateFcost(Gcost+cost,downLoc,destLoc));
                                (*openNodeIt)->setParent(currentNode);
                            }
                        }
                        else
                        {
                            std::shared_ptr<PlannerNode> downNode = std::make_shared<PlannerNode>(downLoc,Gcost+cost,calculateFcost(Gcost+cost,downLoc,destLoc),currentNode);
                            openList.push_back(downNode);
                        }
                    }
                }
            }
        }
    }

    return solution;
}

void PathFinder::setWeight(float value)
{
    weight = value;
}

bool compFinalCost(const std::shared_ptr<PlannerNode> &thisNode, const std::shared_ptr<PlannerNode> &otherNode)
{
    return thisNode->getFcost()>otherNode->getFcost();
}
