#ifndef PLANNERNODE_H
#define PLANNERNODE_H

#include "location.h"
#include "direction.h"
#include <memory>

class PlannerNode
{
public:
    PlannerNode(const Location &loc, float Gcost, float Fcost, std::shared_ptr<PlannerNode> parent);
    float getFcost() const;

    Location getLocation() const;
    Location getUpLocation();
    Location getDownLocation();
    Location getLeftLocation();
    Location getRightLocation();

    float getGcost() const;

    std::shared_ptr<PlannerNode> getParent() const;

    void setGcost(float value);

    void setFcost(float value);

    void setParent(const std::shared_ptr<PlannerNode> &value);

private:
    Location location;
    float Gcost;
    float Fcost;
    std::shared_ptr<PlannerNode> parent;
};

#endif // PLANNERNODE_H
