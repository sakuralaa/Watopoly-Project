#ifndef XWINDOW_H
#define XWINDOW_H

#include <X11/Xlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <variant>
#include <unordered_map>
#include "box.h"
#include "observer.h"

using namespace std;

extern std::vector<std::string> names;

class Xwindow : public Observer{
    Display *d;
    Window w;
    int s, width, height;
    GC gc;
    unsigned long colours[10];  // To hold color values.
    // Removed theGrid as it's not directly used in this modified version.
    std::vector<Box> boxes;
    unordered_map<string, int> playerInfo;
    std::unordered_map<std::string, int> playerColors; 

public:
    Xwindow(int width=1000, int height=750);  // Constructor; displays the window.
    virtual ~Xwindow();  // Destructor; destroys the window.

    enum {White, Black, Red, Green, Blue, Yellow, Orange, Purple, Gray, Pink};

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void fillRectangle(int x, int y, int width, int height, int colour=Black);
    void drawString(int x, int y, std::string msg);
    void drawBox(int idx);
    void drawBoard();
    void loadBoxes();
    void loadPlayers();
    void drawPlayerInfo();
    void waitForCloseEvent();
    void clearArea(int x, int y, int width, int height);


    void notify(Entity e) override;
    
};

#endif // XWINDOW_H

