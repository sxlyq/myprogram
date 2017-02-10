#include "plannernode.h"

PlannerNode::PlannerNode(const Location &loc, float Gcost, float Fcost, std::shared_ptr<PlannerNode> parent)
    :location{loc},Gcost{Gcost},Fcost{Fcost},parent{parent}
{

}
float PlannerNode::getFcost() const
{
    return Fcost;
}
Location PlannerNode::getLocation() const
{
    return location;
}
Location PlannerNode::getUpLocation()
{
    return Location(location.getRow()-1,location.getCol());
}
Location PlannerNode::getDownLocation()
{
    return Location(location.getRow()+1,location.getCol());
}
Location PlannerNode::getLeftLocation()
{
    return Location(location.getRow(),location.getCol()-1);
}
Location PlannerNode::getRightLocation()
{
    return Location(location.getRow(),location.getCol()+1);
}
float PlannerNode::getGcost() const
{
    return Gcost;
}
std::shared_ptr<PlannerNode> PlannerNode::getParent() const
{
    return parent;
}
void PlannerNode::setGcost(float value)
{
    Gcost = value;
}
void PlannerNode::setFcost(float value)
{
    Fcost = value;
}
void PlannerNode::setParent(const std::shared_ptr<PlannerNode> &value)
{
    parent = value;
}



