#ifndef _BUILDINGOBSERVER_H_
#define _BUILDINGOBSERVER_H_

#include "observer.h"
#include <memory>
#include "Building.h"
#include "academic.h"
#include "residence.h"
#include "gym.h"
using namespace std;

class BuildingObserver: public Observer{
    vector<shared_ptr<Building>> buildings;

public:
    BuildingObserver();
    void setSrc(vector<shared_ptr<Building>> b);
    void notify(Entity entity) override;
};

#endif