#include "buildingobserver.h"

BuildingObserver::BuildingObserver(){}

void BuildingObserver::setSrc(vector<shared_ptr<Building>> b){
    buildings = b;
}

void BuildingObserver::notify(Entity entity) {
    std::visit([this](auto&& arg) {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, std::shared_ptr<Building>>) {
        shared_ptr<Building> b = dynamic_pointer_cast<Building>(arg);
        if (b->getType() == academic) {
            auto academicBuilding = std::dynamic_pointer_cast<AcademicBuilding>(b);

            if (academicBuilding) {
                academicBuilding->currTuition = academicBuilding->tuitionWithImprovements[academicBuilding->level];
                bool allOwnedBySamePlayer = true;
                vector<std::shared_ptr<AcademicBuilding>> blockBuildings;

                for (int i : academicBuilding->monopolyBlockIndices) {
                    auto& buildingRef = buildings[i];
                    auto buildingAtI = std::dynamic_pointer_cast<AcademicBuilding>(buildingRef);
                    if (!buildingAtI) {
                        std::cout << "Dynamic cast failed for building at index " << i << std::endl;
                        continue;
                    }
                    if (buildingAtI) {
                        blockBuildings.push_back(buildingAtI);
                        if (b->getOwner() != buildingAtI->getOwner()) {
                            allOwnedBySamePlayer = false;
                            break;
                        }
                    } else {
                        cout << "Failed to cast building at index " << i << " to AcademicBuilding." << endl;
                    }
                }

                for (auto& building : blockBuildings) {
                    building->improvementEnabled = allOwnedBySamePlayer;
                    if (allOwnedBySamePlayer && building->getOwner() != "none") {
                        cout << "Building " << building->getIdx() << " is now able to be improved by " << building->getOwner() << endl;
                        if(building ->getLevel() == 0){
                            building->currTuition *= 2;
                        }
                    } else {
                        cout << "Improvement not enabled due to differnce in ownership" << endl;
                    }
                }
            } else {
                cout << "Debug: Failed to cast to AcademicBuilding." << endl;
            }
        }

        else if(b->getType() == residence) {
            auto residenceBuilding = std::dynamic_pointer_cast<Residence>(b);
            if (residenceBuilding) {
                int residenceCount = 0;
                vector<int> sameOwner;
                for (int i : residenceBuilding->otherBlockIndices) {
                    auto res = dynamic_pointer_cast<Residence>(buildings[i]);
                    if (res && res->getOwner() == b->getOwner()) {
                        ++residenceCount;
                        sameOwner.push_back(res->getIdx());
                    }
                }
                for(int j:sameOwner){
                    auto res = dynamic_pointer_cast<Residence>(buildings[j]);
                    res->currTuition = res->rentWithMutipleOwned[residenceCount - 1];
                    cout << "building " << j << "now has the rent of " << res->rentWithMutipleOwned[residenceCount - 1]<< endl;
                }
            } else {
                cout << "Debug: Failed to cast to Residence." << endl;
            }
        }

        else if(b->getType() == gym){
            auto gym = dynamic_pointer_cast<Gym>(b);
            bool result = true;
            if (gym) {
                for (int i : gym->otherBlockIndices) {
                    auto res = dynamic_pointer_cast<Gym>(buildings[i]);
                    result = result && res->owner == gym->owner;
                }
                for(int j:gym->otherBlockIndices){
                    auto res = dynamic_pointer_cast<Gym>(buildings[j]);
                    res->ownedTwo = result;
                }
            } else {
                cout << "Debug: Failed to cast to Residence." << endl;
            }
        }
    }
    }, entity);
}