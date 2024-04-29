#ifndef BOX_H
#define BOX_H

#include <X11/Xlib.h>
#include <vector>
#include <string>

extern const int BOX_WIDTH;
extern const int BOX_HEIGHT;

class Box {
    friend class Xwindow;
public:

    Box(const std::string& name, int index,const std::string& owner = "none",
        std::vector<std::string> currPlayer = {"none"}, int level = 0);

    std::string getName() const;
    std::string getLastPlayer() const;
    std::string getOwner() const;
    int getIndex() const;
    int getLevel() const;


private:
    std::string name;
    int index;
    std::string owner;
    std::vector<std::string> currPlayer;
    int level;
};

#endif
