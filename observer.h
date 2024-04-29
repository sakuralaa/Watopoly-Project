#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "Building.h"
#include "player.h"
#include <variant>

using namespace std;
using Entity = variant<shared_ptr<Building>,shared_ptr<Player>>;
class Building;

class Observer {
 public:
  virtual void notify(Entity e) = 0;
  virtual ~Observer() = default;
};
#endif
